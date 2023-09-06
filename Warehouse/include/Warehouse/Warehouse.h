#include <Interfaces/IWarehouse.hpp>
#include <Departments/DepartmentsList.hpp>
#include <Factory/ProductFactory.hpp>

namespace warehouse
{
class Warehouse : public warehouseInterface::IWarehouse{
    private:
        std::vector<warehouseInterface::IDepartmentPtr> _departments{};
    public:
        void addDepartment(warehouseInterface::IDepartmentPtr);
        warehouseInterface::DeliveryReportJson newDelivery(std::vector<warehouseInterface::IProductPtr>);
        warehouseInterface::Order newOrder(const warehouseInterface::OrderJson &);
        warehouseInterface::OccupancyReportJson getOccupancyReport() const;
        warehouseInterface::WarehouseStateJson saveWarehouseState() const;
        bool loadWarehouseState(const warehouseInterface::WarehouseStateJson &);
};

}  // namespace warehouse