#pragma once
#include <Interfaces/IProduct.hpp>
#include <Products/ProductsList.hpp>
#include <MagicEnum/magic_enum.hpp>
//#include <Products/BasicProduct.hpp>


namespace warehouse {

class ProductFactory {
public:
    warehouseInterface::IProductPtr createProduct(const std::string& className, const std::string& name, const float size) const {
        if (className == "IndustrialServerRack") {
            return std::make_unique<IndustrialServerRack>(name, size);
        } else if (className == "GlassWare") {
            return std::make_unique<GlassWare>(name, size);
        } else if (className == "ExplosiveBarrel") {
            return std::make_unique<ExplosiveBarrel>(name, size);
        } else if (className == "ElectronicParts") {
            return std::make_unique<ElectronicParts>(name, size);
        } else if (className == "AstronautsIceCream") {
            return std::make_unique<AstronautsIceCream>(name, size);
        } else if (className == "AcetoneBarrel") {
            return std::make_unique<AcetoneBarrel>(name, size);
        } else if (className == "TV") {
            return std::make_unique<TV>(name, size);
        } else {
            throw std::runtime_error("Unknown product class: " + className);
        }
    }
};

}  // namespace warehouse