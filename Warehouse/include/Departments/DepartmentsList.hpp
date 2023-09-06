#pragma once
#include <Interfaces/IDepartment.hpp>
#include <Interfaces/IProduct.hpp>
#include <Products/ProductsList.hpp>
#include <iostream>

namespace warehouse{
    class ColdRoomDepartment : public warehouseInterface::IDepartment {
private:
    float maxOccupancy_;
    float maxItemSize_;
    float occupancy_;
    std::vector<warehouseInterface::IProductPtr> items_;

public:
    explicit ColdRoomDepartment(float maxOccupancy)
            : maxOccupancy_(maxOccupancy), maxItemSize_(std::numeric_limits<float>::max()), occupancy_(0.0f), items_() {}

    bool addItem(warehouseInterface::IProductPtr item) override {
        if (item->itemSize() <= maxItemSize_ && occupancy_ + item->itemSize() <= maxOccupancy_) {
            items_.push_back(std::move(item));
            occupancy_ += items_.back()->itemSize(); // Update the occupancy with the size of the added item
            return true;
        }
        return false;
    }

    warehouseInterface::IProductPtr getItem(const warehouseInterface::ProductDescriptionJson& productDesc) override {
        picojson::value jsonValue;
        std::string err = picojson::parse(jsonValue, productDesc);
        picojson::object json = jsonValue.get<picojson::object>();

        bool hasName = json.count("name") > 0;
        bool hasClass = json.count("class") > 0;

        for (auto it = items_.begin(); it != items_.end(); ++it) {
            //std::cout << "Checking name: " << (*it)->name() << std::endl;
            if (hasName && (*it)->name() == json["name"].get<std::string>()) {
                //std::cout << "Name match found: " << (*it)->name() << std::endl;
                auto result = std::move(*it);
                occupancy_ -= result->itemSize();
                items_.erase(it);
                return result;
            }
        }
       
        for (auto it = items_.begin(); it != items_.end(); ++it) {
            picojson::value itemJson;
            std::string itemJsonStr = (*it)->serialize();
            std::string err = picojson::parse(itemJson, itemJsonStr);
            picojson::object json2 = itemJson.get<picojson::object>();

            if (hasClass && json2["class"].get<std::string>() == json["class"].get<std::string>()) {
                auto result = std::move(*it);
                occupancy_ -= result->itemSize();
                items_.erase(it);
                return result;
            }
        }
        
        return nullptr; // Return nullptr if item is not found
    }

    

    float getOccupancy() const override {
        return occupancy_;
    }

    float getMaxOccupancy() const override {
        return maxOccupancy_;
    }

    float getMaxItemSize() const override {
        return maxItemSize_;
    }

    warehouseInterface::ProductLabelFlags getSupportedFlags() const override {
        return combineFlags(
            warehouseInterface::ProductLabelFlags::keepFrozen,
            warehouseInterface::ProductLabelFlags::keepDry);
    }

    picojson::object asJson() const override {
        picojson::object departmentJson;
        departmentJson["class"] = picojson::value(departmentName());
        departmentJson["occupancy"] = picojson::value(static_cast<double>(occupancy_));
        departmentJson["maxOccupancy"] = picojson::value(static_cast<double>(maxOccupancy_));
        departmentJson["items"] = picojson::value(serializedItems());

        picojson::value departmentValue(departmentJson);
        return departmentValue.get<picojson::object>();
    }

    warehouseInterface::DepartmentStateJson serialize() const override {
        picojson::object departmentJson = asJson();
        return picojson::value(departmentJson).serialize();
    }

    picojson::array serializedItems() const override {
        picojson::array itemsJson;
        for (const auto& item : items_) {
            picojson::value itemValue;
            picojson::parse(itemValue, item->serialize());
            itemsJson.push_back(itemValue);
        }
        return itemsJson;
    }

    std::string departmentName() const override {
        return "ColdRoomDepartment";
    }
};

class SmallElectronicDepartment : public warehouseInterface::IDepartment {
private:
    float maxOccupancy_;
    float maxItemSize_;
    float occupancy_;
    std::vector<warehouseInterface::IProductPtr> items_;

public:
     explicit SmallElectronicDepartment(float maxOccupancy)
        : maxOccupancy_(maxOccupancy), maxItemSize_(5.0), occupancy_(0.0f), items_() {}
        
    bool addItem(warehouseInterface::IProductPtr item) override {
        if (item->itemSize() <= maxItemSize_ && occupancy_ + item->itemSize() <= maxOccupancy_) {
            items_.push_back(std::move(item));
            occupancy_ += items_.back()->itemSize(); // Update the occupancy with the size of the added item
            return true;
        }
        return false;
    }

    warehouseInterface::IProductPtr getItem(const warehouseInterface::ProductDescriptionJson& productDesc) override {
        picojson::value jsonValue;
        std::string err = picojson::parse(jsonValue, productDesc);
        picojson::object json = jsonValue.get<picojson::object>();

        bool hasName = json.count("name") > 0;
        bool hasClass = json.count("class") > 0;

        for (auto it = items_.begin(); it != items_.end(); ++it) {
            //std::cout << "Checking name: " << (*it)->name() << std::endl;
            if (hasName && (*it)->name() == json["name"].get<std::string>()) {
                //std::cout << "Name match found: " << (*it)->name() << std::endl;
                auto result = std::move(*it);
                occupancy_ -= result->itemSize();
                items_.erase(it);
                return result;
            }
        }
       
        for (auto it = items_.begin(); it != items_.end(); ++it) {
            picojson::value itemJson;
            std::string itemJsonStr = (*it)->serialize();
            std::string err = picojson::parse(itemJson, itemJsonStr);
            picojson::object json2 = itemJson.get<picojson::object>();

            if (hasClass && json2["class"].get<std::string>() == json["class"].get<std::string>()) {
                auto result = std::move(*it);
                occupancy_ -= result->itemSize();
                items_.erase(it);
                return result;
            }
        }
        
        return nullptr; // Return nullptr if item is not found
    }

    float getOccupancy() const override {
        return occupancy_;
    }

    float getMaxOccupancy() const override {
        return maxOccupancy_;
    }

    float getMaxItemSize() const override {
        return maxItemSize_;
    }

    warehouseInterface::ProductLabelFlags getSupportedFlags() const override {
        return combineFlags(
            warehouseInterface::ProductLabelFlags::esdSensitive,
            warehouseInterface::ProductLabelFlags::keepDry);
    }

    picojson::object asJson() const override {
        picojson::object departmentJson;
        departmentJson["class"] = picojson::value(departmentName());
        departmentJson["occupancy"] = picojson::value(static_cast<double>(occupancy_));
        departmentJson["maxOccupancy"] = picojson::value(static_cast<double>(maxOccupancy_));
        departmentJson["maxItemSize"] = picojson::value(static_cast<double>(maxItemSize_));
        departmentJson["items"] = picojson::value(serializedItems());
        return departmentJson;
    }

    warehouseInterface::DepartmentStateJson serialize() const override {
        picojson::object departmentJson = asJson();
        return picojson::value(departmentJson).serialize();
    }

    picojson::array serializedItems() const override {
        picojson::array itemsJson;
        for (const auto& item : items_) {
            picojson::value itemValue;
            picojson::parse(itemValue, item->serialize());
            itemsJson.push_back(itemValue);
        }
        return itemsJson;
    }

    std::string departmentName() const override {
        return "SmallElectronicDepartment";
    }
};

class OverSizeElectronicDepartment : public warehouseInterface::IDepartment {
private:
    float maxOccupancy_;
    float maxItemSize_;
    float occupancy_;
    std::vector<warehouseInterface::IProductPtr> items_;

public:
    explicit OverSizeElectronicDepartment(float maxOccupancy)
        : maxOccupancy_(maxOccupancy), maxItemSize_(std::numeric_limits<float>::max()), occupancy_(0.0f), items_() {}

    bool addItem(warehouseInterface::IProductPtr item) override {
        if (item->itemSize() <= maxItemSize_ && occupancy_ + item->itemSize() <= maxOccupancy_) {
            items_.push_back(std::move(item));
            occupancy_ += items_.back()->itemSize(); // Update the occupancy with the size of the added item
            return true;
        }
        return false;
    }

    warehouseInterface::IProductPtr getItem(const warehouseInterface::ProductDescriptionJson& productDesc) override {
        picojson::value jsonValue;
        std::string err = picojson::parse(jsonValue, productDesc);
        picojson::object json = jsonValue.get<picojson::object>();

        bool hasName = json.count("name") > 0;
        bool hasClass = json.count("class") > 0;

        for (auto it = items_.begin(); it != items_.end(); ++it) {
            //std::cout << "Checking name: " << (*it)->name() << std::endl;
            if (hasName && (*it)->name() == json["name"].get<std::string>()) {
                //std::cout << "Name match found: " << (*it)->name() << std::endl;
                auto result = std::move(*it);
                occupancy_ -= result->itemSize();
                items_.erase(it);
                return result;
            }
        }
       
        for (auto it = items_.begin(); it != items_.end(); ++it) {
            picojson::value itemJson;
            std::string itemJsonStr = (*it)->serialize();
            std::string err = picojson::parse(itemJson, itemJsonStr);
            picojson::object json2 = itemJson.get<picojson::object>();

            if (hasClass && json2["class"].get<std::string>() == json["class"].get<std::string>()) {
                auto result = std::move(*it);
                occupancy_ -= result->itemSize();
                items_.erase(it);
                return result;
            }
        }
        
        return nullptr; // Return nullptr if item is not found
    }

    float getOccupancy() const override {
        return occupancy_;
    }

    float getMaxOccupancy() const override {
        return maxOccupancy_;
    }

    float getMaxItemSize() const override {
        return maxItemSize_;
    }

    warehouseInterface::ProductLabelFlags getSupportedFlags() const override {
        return combineFlags(
            warehouseInterface::ProductLabelFlags::esdSensitive,
            warehouseInterface::ProductLabelFlags::keepDry);
    }

    picojson::object asJson() const override {
        picojson::object departmentJson;
        departmentJson["class"] = picojson::value(departmentName());
        departmentJson["occupancy"] = picojson::value(static_cast<double>(occupancy_));
        departmentJson["maxOccupancy"] = picojson::value(static_cast<double>(maxOccupancy_));
        departmentJson["maxItemSize"] = picojson::value(static_cast<double>(maxItemSize_));
        departmentJson["items"] = picojson::value(serializedItems());
        return departmentJson;
    }

    warehouseInterface::DepartmentStateJson serialize() const override {
        picojson::object departmentJson = asJson();
        return picojson::value(departmentJson).serialize();
    }

    picojson::array serializedItems() const override {
        picojson::array itemsJson;
        for (const auto& item : items_) {
            picojson::value itemValue;
            picojson::parse(itemValue, item->serialize());
            itemsJson.push_back(itemValue);
        }
        return itemsJson;
    }

    std::string departmentName() const override {
        return "OverSizeElectronicDepartment";
    }
};

class HazardousDepartment : public warehouseInterface::IDepartment {
private:
    float maxOccupancy_;
    float maxItemSize_;
    float occupancy_;
    std::vector<warehouseInterface::IProductPtr> items_;

public:
    explicit HazardousDepartment(float maxOccupancy)
        : maxOccupancy_(maxOccupancy), maxItemSize_(std::numeric_limits<float>::max()), occupancy_(0.0f), items_() {}

    bool addItem(warehouseInterface::IProductPtr item) override {
        if (item->itemSize() <= maxItemSize_ && occupancy_ + item->itemSize() <= maxOccupancy_) {
            items_.push_back(std::move(item));
            occupancy_ += items_.back()->itemSize(); // Update the occupancy with the size of the added item
            return true;
        }
        return false;
    }

    warehouseInterface::IProductPtr getItem(const warehouseInterface::ProductDescriptionJson& productDesc) override {
        picojson::value jsonValue;
        std::string err = picojson::parse(jsonValue, productDesc);
        picojson::object json = jsonValue.get<picojson::object>();

        bool hasName = json.count("name") > 0;
        bool hasClass = json.count("class") > 0;

        if(hasName && hasClass) {
            for (auto it = items_.begin(); it != items_.begin()+1; ++it) {
            picojson::value itemJson;
            std::string itemJsonStr = (*it)->serialize();
            std::string err = picojson::parse(itemJson, itemJsonStr);
            picojson::object json2 = itemJson.get<picojson::object>();

            if ((*it)->name() == json["name"].get<std::string>() && json2["class"].get<std::string>() == json["class"].get<std::string>()) {
                auto result = std::move(*it);
                occupancy_ -= result->itemSize();
                items_.erase(it);
                return result;
            }
        }
        return nullptr; // Return nullptr if item is not found
        }
        
        else{
            for (auto it = items_.begin(); it != items_.begin()+1; ++it) {
                //std::cout << "Checking name: " << (*it)->name() << std::endl;
                if (hasName && (*it)->name() == json["name"].get<std::string>()) {
                    //std::cout << "Name match found: " << (*it)->name() << std::endl;
                    auto result = std::move(*it);
                    occupancy_ -= result->itemSize();
                    items_.erase(it);
                    return result;
                }
            }
        
            for (auto it = items_.begin(); it != items_.begin()+1; ++it) {
                picojson::value itemJson;
                std::string itemJsonStr = (*it)->serialize();
                std::string err = picojson::parse(itemJson, itemJsonStr);
                picojson::object json2 = itemJson.get<picojson::object>();

                if (hasClass && json2["class"].get<std::string>() == json["class"].get<std::string>()) {
                    auto result = std::move(*it);
                    occupancy_ -= result->itemSize();
                    items_.erase(it);
                    return result;
                }
            }
            return nullptr; // Return nullptr if item is not found
        }
        
        
        
    }

    float getOccupancy() const override {
        return occupancy_;
    }

    float getMaxOccupancy() const override {
        return maxOccupancy_;
    }

    float getMaxItemSize() const override {
        return maxItemSize_;
    }

    warehouseInterface::ProductLabelFlags getSupportedFlags() const override {
        return combineFlags3(
            warehouseInterface::ProductLabelFlags::fireHazardous,
            warehouseInterface::ProductLabelFlags::explosives,
            warehouseInterface::ProductLabelFlags::keepDry
        );
    }

    picojson::object asJson() const override {
        picojson::object departmentJson;
        departmentJson["class"] = picojson::value(departmentName());
        departmentJson["occupancy"] = picojson::value(static_cast<double>(occupancy_));
        departmentJson["maxOccupancy"] = picojson::value(static_cast<double>(maxOccupancy_));
        departmentJson["items"] = picojson::value(serializedItems());
        return departmentJson;
    }

    warehouseInterface::DepartmentStateJson serialize() const override {
        picojson::object departmentJson = asJson();
        return picojson::value(departmentJson).serialize();
    }

    picojson::array serializedItems() const override {
        picojson::array itemsJson;
        for (const auto& item : items_) {
            picojson::value itemValue;
            picojson::parse(itemValue, item->serialize());
            itemsJson.push_back(itemValue);
        }
        return itemsJson;
    }

    std::string departmentName() const override {
        return "HazardousDepartment";
    }
};

class SpecialDepartment : public warehouseInterface::IDepartment {
private:
    float maxOccupancy_;
    float maxItemSize_;
    float occupancy_;
    std::vector<warehouseInterface::IProductPtr> items_;

public:
    explicit SpecialDepartment(float maxOccupancy)
        : maxOccupancy_(maxOccupancy), maxItemSize_(std::numeric_limits<float>::max()), occupancy_(0.0), items_() {}

    bool addItem(warehouseInterface::IProductPtr item) override {
        if (item->itemSize() <= maxItemSize_ && occupancy_ + item->itemSize() <= maxOccupancy_) {
            items_.push_back(std::move(item));
            occupancy_ += items_.back()->itemSize(); // Update the occupancy with the size of the added item
            return true;
        }
        return false;
    }

    warehouseInterface::IProductPtr getItem(const warehouseInterface::ProductDescriptionJson& productDesc) override {
        picojson::value jsonValue;
        std::string err = picojson::parse(jsonValue, productDesc);
        picojson::object json = jsonValue.get<picojson::object>();

        bool hasName = json.count("name") > 0;
        bool hasClass = json.count("class") > 0;

        if(hasName && hasClass) {
            for (auto it = items_.end()-1; it != items_.end()-2; --it) {
            picojson::value itemJson;
            std::string itemJsonStr = (*it)->serialize();
            std::string err = picojson::parse(itemJson, itemJsonStr);
            picojson::object json2 = itemJson.get<picojson::object>();

            if ((*it)->name() == json["name"].get<std::string>() && json2["class"].get<std::string>() == json["class"].get<std::string>()) {
                auto result = std::move(*it);
                occupancy_ -= result->itemSize();
                items_.erase(it);
                return result;
            }
        }
        return nullptr; // Return nullptr if item is not found
        }
        
        else{
            for (auto it = items_.end()-1; it != items_.end()-2; --it) {
                //std::cout << "Checking name: " << (*it)->name() << std::endl;
                if (hasName && (*it)->name() == json["name"].get<std::string>()) {
                    //std::cout << "Name match found: " << (*it)->name() << std::endl;
                    auto result = std::move(*it);
                    occupancy_ -= result->itemSize();
                    items_.erase(it);
                    return result;
                }
            }
        
            for (auto it = items_.end()-1; it != items_.end()-2; --it) {
                picojson::value itemJson;
                std::string itemJsonStr = (*it)->serialize();
                std::string err = picojson::parse(itemJson, itemJsonStr);
                picojson::object json2 = itemJson.get<picojson::object>();

                if (hasClass && json2["class"].get<std::string>() == json["class"].get<std::string>()) {
                    auto result = std::move(*it);
                    occupancy_ -= result->itemSize();
                    items_.erase(it);
                    return result;
                }
            }
            return nullptr; // Return nullptr if item is not found
        }
        
        
        
    }

    float getOccupancy() const override {
        return occupancy_;
    }

    float getMaxOccupancy() const override {
        return maxOccupancy_;
    }

    float getMaxItemSize() const override {
        return maxItemSize_;
    }

    warehouseInterface::ProductLabelFlags getSupportedFlags() const override {
        return combineFlags2(
            warehouseInterface::ProductLabelFlags::fragile,
            warehouseInterface::ProductLabelFlags::upWard,
            warehouseInterface::ProductLabelFlags::keepDry,
            warehouseInterface::ProductLabelFlags::handleWithCare
        );
    }

    picojson::object asJson() const override {
        picojson::object departmentJson;
        departmentJson["class"] = picojson::value(departmentName());
        departmentJson["occupancy"] = picojson::value(static_cast<double>(occupancy_));
        departmentJson["maxOccupancy"] = picojson::value(static_cast<double>(maxOccupancy_));
        departmentJson["items"] = picojson::value(serializedItems());
        return departmentJson;
    }

    warehouseInterface::DepartmentStateJson serialize() const override {
        picojson::object departmentJson = asJson();
        return picojson::value(departmentJson).serialize();
    }

    picojson::array serializedItems() const override {
        picojson::array itemsJson;
        for (const auto& item : items_) {
            picojson::value itemValue;
            picojson::parse(itemValue, item->serialize());
            itemsJson.push_back(itemValue);
        }
        return itemsJson;
    }

    std::string departmentName() const override {
        return "SpecialDepartment";
    }
};
}// namespace warehouse