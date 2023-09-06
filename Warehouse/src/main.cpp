#include <Warehouse/Warehouse.h>

#include <Products/ProductsList.hpp>
#include <iostream>

int main([[maybe_unused]] int argc, [[maybe_unused]] char const *argv[])
{
    warehouse::TV t("Samsung UltraWide", 2);
    std::cout << t.serialize() << std::endl;
    return 0;
}
