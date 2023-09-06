#include <Warehouse/Warehouse.h>

void warehouse::Warehouse::addDepartment(
    warehouseInterface::IDepartmentPtr department) {
  _departments.push_back(std::move(department));
}

warehouseInterface::DeliveryReportJson warehouse::Warehouse::newDelivery(
    std::vector<warehouseInterface::IProductPtr> productsIn) {
  using namespace magic_enum::bitwise_operators;
  picojson::object tmp;
  picojson::array Arr;
  for (auto &item : productsIn) {
    tmp["assignedDepartment"] = picojson::value("None");
    tmp["errorLog"] = picojson::value(
        "Warehouse cannot store this product. Lack of space in departments.");
    tmp["productName"] = picojson::value(item->name());
    tmp["status"] = picojson::value("Fail");
    if ((warehouseInterface::ProductLabelFlags::explosives &
         item->itemFlags()) ==
            warehouseInterface::ProductLabelFlags::explosives ||
        (warehouseInterface::ProductLabelFlags::fireHazardous &
         item->itemFlags()) ==
            warehouseInterface::ProductLabelFlags::fireHazardous) {
      for (auto &j : _departments) {
        if (j->departmentName() == "HazardousDepartment") {
          if (j->addItem(std::move(item))) {
            tmp["assignedDepartment"] = picojson::value("HazardousDepartment");
            tmp["errorLog"] = picojson::value("");
            tmp["status"] = picojson::value("Success");
          }
          break;
        }
        if (j == _departments.back())
          tmp["errorLog"] = picojson::value(
              "Warehouse cannot store this product. Lack of required "
              "department.");
      }
      Arr.push_back(picojson::value(tmp));
      continue;
    }
    if ((warehouseInterface::ProductLabelFlags::esdSensitive &
         item->itemFlags()) ==
        warehouseInterface::ProductLabelFlags::esdSensitive) {
      if (item->itemSize() > 5.0) {
        for (auto &j : _departments) {
          if (j->departmentName() == "OverSizeElectronicDepartment") {
            if (j->addItem(std::move(item))) {
              tmp["assignedDepartment"] =
                  picojson::value("OverSizeElectronicDepartment");
              tmp["errorLog"] = picojson::value("");
              tmp["status"] = picojson::value("Success");
            }
            break;
          }
          if (j == _departments.back())
            tmp["errorLog"] = picojson::value(
                "Warehouse cannot store this product. Lack of required "
                "department.");
        }
      } else {
        for (auto &j : _departments) {
          if (j->departmentName() == "SmallElectronicDepartment") {
            if (j->addItem(std::move(item))) {
              tmp["assignedDepartment"] =
                  picojson::value("SmallElectronicDepartment");
              tmp["errorLog"] = picojson::value("");
              tmp["status"] = picojson::value("Success");
            }
            break;
          }
          if (j == _departments.back())
            tmp["errorLog"] = picojson::value(
                "Warehouse cannot store this product. Lack of required "
                "department.");
        }
      }
      Arr.push_back(picojson::value(tmp));
      continue;
    }
    if ((warehouseInterface::ProductLabelFlags::keepFrozen &
         item->itemFlags()) ==
        warehouseInterface::ProductLabelFlags::keepFrozen) {
      for (auto &j : _departments) {
        if (j->departmentName() == "ColdRoomDepartment") {
          if (j->addItem(std::move(item))) {
            tmp["assignedDepartment"] = picojson::value("ColdRoomDepartment");
            tmp["errorLog"] = picojson::value("");
            tmp["status"] = picojson::value("Success");
          }
          break;
        }
        if (j == _departments.back())
          tmp["errorLog"] = picojson::value(
              "Warehouse cannot store this product. Lack of required "
              "department.");
      }
      Arr.push_back(picojson::value(tmp));
      continue;
    }
    if ((warehouseInterface::ProductLabelFlags::fragile & item->itemFlags()) ==
            warehouseInterface::ProductLabelFlags::fragile ||
        (warehouseInterface::ProductLabelFlags::handleWithCare &
         item->itemFlags()) ==
            warehouseInterface::ProductLabelFlags::handleWithCare ||
        (warehouseInterface::ProductLabelFlags::upWard & item->itemFlags()) ==
            warehouseInterface::ProductLabelFlags::upWard) {
      for (auto &j : _departments) {
        if (j->departmentName() == "SpecialDepartment") {
          if (j->addItem(std::move(item))) {
            tmp["assignedDepartment"] = picojson::value("SpecialDepartment");
            tmp["errorLog"] = picojson::value("");
            tmp["status"] = picojson::value("Success");
          }
          break;
        }
        if (j == _departments.back())
          tmp["errorLog"] = picojson::value(
              "Warehouse cannot store this product. Lack of required "
              "department.");
      }
      Arr.push_back(picojson::value(tmp));
      continue;
    }
    for (auto &j : _departments) {
      if (!(j->addItem(std::move(item)))) {
        tmp["assignedDepartment"] = picojson::value(j->departmentName());
        tmp["errorLog"] = picojson::value("");
        tmp["status"] = picojson::value("Success");
        break;
      }
      if (j == _departments.back())
        tmp["errorLog"] = picojson::value(
            "Warehouse cannot store this product. Lack of required "
            "department.");
    }
    Arr.push_back(picojson::value(tmp));
  }
  tmp.erase(tmp.begin(), tmp.end());
  tmp["deliveryReport"] = picojson::value(Arr);
  return picojson::value(tmp).serialize();
}

warehouseInterface::Order warehouse::Warehouse::newOrder(
    const warehouseInterface::OrderJson &orderStr) {
  picojson::value v;
  picojson::object o;
  std::string tmp;
  picojson::parse(v, orderStr);
  warehouseInterface::Order order{
      std::vector<warehouseInterface::IProductPtr>(), orderStr};
  if (!(v.is<picojson::object>())) return order;
  o = v.get<picojson::object>();
  if (o.empty()) return order;
  if (o.begin()->first != "order") return order;
  if (!(o["order"].is<picojson::array>())) return order;
  picojson::array productArr = o["order"].get<picojson::array>();
  if (productArr.empty()) return order;
  for (auto &i : productArr) {
    tmp = i.serialize();
    order.products.push_back(nullptr);
    for (auto &j : _departments) {
      order.products.back() = j->getItem(tmp);
      if (order.products.back() != nullptr) break;
    }
    if (order.products.back() == nullptr) order.products.pop_back();
  }
  return order;
}

warehouseInterface::OccupancyReportJson
warehouse::Warehouse::getOccupancyReport() const {
  picojson::object tmp;
  picojson::array occupancyArr;
  for (auto &i : _departments) {
    tmp["departmentName"] = picojson::value(i->departmentName());
    tmp["maxOccupancy"] = picojson::value(i->getMaxOccupancy());
    tmp["occupancy"] = picojson::value(i->getOccupancy());
    occupancyArr.push_back(picojson::value(tmp));
  }
  tmp.erase(tmp.begin(), tmp.end());
  tmp["departmentsOccupancy"] = picojson::value(occupancyArr);
  return picojson::value(tmp).serialize();
}

warehouseInterface::WarehouseStateJson
warehouse::Warehouse::saveWarehouseState() const {
  picojson::object tmp;
  picojson::array departmentsArr;
  for (auto &i : _departments) {
    departmentsArr.push_back(picojson::value(i->asJson()));
  }
  tmp["warehouseState"] = picojson::value(departmentsArr);
  return picojson::value(tmp).serialize();
}

bool warehouse::Warehouse::loadWarehouseState(
    const warehouseInterface::WarehouseStateJson &inputStr) {
  picojson::value input;
  picojson::parse(input, inputStr);
  picojson::array depArr =
      input.get<picojson::object>()["warehouseState"].get<picojson::array>();
  picojson::array itemsArr;
  picojson::object department;
  picojson::object product;
  std::string departmentClass;
  warehouse::ProductFactory factory = warehouse::ProductFactory();
  for (auto &i : depArr) {
    department = i.get<picojson::object>();
    departmentClass = department["class"].get<std::string>();
    if (departmentClass == "ColdRoomDepartment") {
      addDepartment(std::make_unique<warehouse::ColdRoomDepartment>(
          static_cast<float>(department["maxOccupancy"].get<double>())));
    } else if (departmentClass == "SmallElectronicDepartment") {
      addDepartment(std::make_unique<warehouse::SmallElectronicDepartment>(
          static_cast<float>(department["maxOccupancy"].get<double>())));
    } else if (departmentClass == "OverSizeElectronicDepartment") {
      addDepartment(std::make_unique<warehouse::OverSizeElectronicDepartment>(
          static_cast<float>(department["maxOccupancy"].get<double>())));
    } else if (departmentClass == "HazardousDepartment") {
      addDepartment(std::make_unique<warehouse::HazardousDepartment>(
          static_cast<float>(department["maxOccupancy"].get<double>())));
    } else if (departmentClass == "SpecialDepartment") {
      addDepartment(std::make_unique<warehouse::SpecialDepartment>(
          static_cast<float>(department["maxOccupancy"].get<double>())));
    } else {
      return false;
    }
    itemsArr = department["items"].get<picojson::array>();
    for (auto &j : itemsArr) {
      product = j.get<picojson::object>();
      _departments.back()->addItem(factory.createProduct(
          product["class"].get<std::string>(),
          product["name"].get<std::string>(),
          static_cast<float>(product["size"].get<double>())));
    }
  }
  return true;
}