#pragma once
#include <PicoJson/picojson.h>
#include <MagicEnum/magic_enum.hpp>
#include <Interfaces/IProduct.hpp>


namespace warehouse{
    warehouseInterface::ProductLabelFlags combineFlags(warehouseInterface::ProductLabelFlags flag1, warehouseInterface::ProductLabelFlags flag2);
    warehouseInterface::ProductLabelFlags combineFlags2(warehouseInterface::ProductLabelFlags flag1, warehouseInterface::ProductLabelFlags flag2, warehouseInterface::ProductLabelFlags flag3, warehouseInterface::ProductLabelFlags flag4);
    warehouseInterface::ProductLabelFlags combineFlags3(warehouseInterface::ProductLabelFlags flag1, warehouseInterface::ProductLabelFlags flag2, warehouseInterface::ProductLabelFlags flag3);

class IndustrialServerRack : public warehouseInterface::IProduct
{
public:
    IndustrialServerRack(const std::string& name, const float size) : name_(name), size_(size) {}
    
    std::string name() const override { return name_; }

    std::string className() const {
        return "IndustrialServerRack";
    }

    float itemSize() const override { return size_; }

    warehouseInterface::ProductLabelFlags itemFlags() const override
    {
        return combineFlags2(
            warehouseInterface::ProductLabelFlags::upWard,
            warehouseInterface::ProductLabelFlags::keepDry,
            warehouseInterface::ProductLabelFlags::handleWithCare,
            warehouseInterface::ProductLabelFlags::esdSensitive
        );
    }

    picojson::object asJson() const override
    {
        picojson::object json;
        json["class"] = picojson::value("IndustrialServerRack");
        json["name"] = picojson::value(name_);
        json["size"] = picojson::value(size_);

        picojson::array flagsArray;
        flagsArray.push_back(picojson::value("upWard"));
        flagsArray.push_back(picojson::value("keepDry"));
        flagsArray.push_back(picojson::value("handleWithCare"));
        flagsArray.push_back(picojson::value("esdSensitive"));

        json["flags"] = picojson::value(flagsArray);

        return json;
    }

    warehouseInterface::ProductDescriptionJson serialize() const override
    {
        return picojson::value(asJson()).serialize();
    }

private:
    std::string name_;
    float size_;
};

class GlassWare : public warehouseInterface::IProduct
{
public:
    GlassWare(const std::string& name, const float size) : name_(name), size_(size) {}

    std::string name() const override { return name_; }

    std::string className() const {
        return "GlassWare";
    }

    float itemSize() const override { return size_; }

    warehouseInterface::ProductLabelFlags itemFlags() const override
    {
        return combineFlags(
            warehouseInterface::ProductLabelFlags::fragile,
            warehouseInterface::ProductLabelFlags::upWard
        );
    }

    picojson::object asJson() const override
    {
        picojson::object json;
        json["class"] = picojson::value("GlassWare");
        json["name"] = picojson::value(name_);
        json["size"] = picojson::value(size_);

        picojson::array flagsArray;
        flagsArray.push_back(picojson::value("fragile"));
        flagsArray.push_back(picojson::value("upWard"));

        json["flags"] = picojson::value(flagsArray);

        return json;
    }

    warehouseInterface::ProductDescriptionJson serialize() const override
    {
        return picojson::value(asJson()).serialize();
    }

private:
    std::string name_;
    float size_;
};

class ExplosiveBarrel : public warehouseInterface::IProduct
{
public:
    ExplosiveBarrel(const std::string& name, const float size) : name_(name), size_(size) {}

    std::string name() const override { return name_; }

    std::string className() const {
        return "ExplosiveBarrel";
    }

    float itemSize() const override { return size_; }

    warehouseInterface::ProductLabelFlags itemFlags() const override
    {
        return combineFlags(
            warehouseInterface::ProductLabelFlags::explosives,
            warehouseInterface::ProductLabelFlags::handleWithCare
        );
    }

    picojson::object asJson() const override
    {
        picojson::object json;
        json["class"] = picojson::value("ExplosiveBarrel");
        json["name"] = picojson::value(name_);
        json["size"] = picojson::value(size_);

        picojson::array flagsArray;
        flagsArray.push_back(picojson::value("explosives"));
        flagsArray.push_back(picojson::value("handleWithCare"));

        json["flags"] = picojson::value(flagsArray);

        return json;
    }

    warehouseInterface::ProductDescriptionJson serialize() const override
    {
        return picojson::value(asJson()).serialize();
    }

private:
    std::string name_;
    float size_;
};

class ElectronicParts : public warehouseInterface::IProduct
{
public:
    ElectronicParts(const std::string& name, const float size) : name_(name), size_(size) {}

    std::string name() const override { return name_; }

    std::string className() const {
        return "ElectronicParts";
    }

    float itemSize() const override { return size_; }

    warehouseInterface::ProductLabelFlags itemFlags() const override
    {
        return combineFlags(
            warehouseInterface::ProductLabelFlags::esdSensitive,
            warehouseInterface::ProductLabelFlags::keepDry
        );
    }

    picojson::object asJson() const override
    {
        picojson::object json;
        json["class"] = picojson::value("ElectronicParts");
        json["name"] = picojson::value(name_);
        json["size"] = picojson::value(size_);

        picojson::array flagsArray;
        flagsArray.push_back(picojson::value("keepDry"));
        flagsArray.push_back(picojson::value("esdSensitive"));

        json["flags"] = picojson::value(flagsArray);

        return json;
    }

    warehouseInterface::ProductDescriptionJson serialize() const override
    {
        return picojson::value(asJson()).serialize();
    }

private:
    std::string name_;
    float size_;
};

class AstronautsIceCream : public warehouseInterface::IProduct
{
public:
    AstronautsIceCream(const std::string& name, const float size) : name_(name), size_(size) {}

    std::string name() const override { return name_; }

    std::string className() const {
        return "AstronautsIceCream";
    }

    float itemSize() const override { return size_; }

    warehouseInterface::ProductLabelFlags itemFlags() const override
    {
        return combineFlags(
            warehouseInterface::ProductLabelFlags::keepFrozen,
            warehouseInterface::ProductLabelFlags::keepDry
        );
    }

    picojson::object asJson() const override
    {
        picojson::object json;
        json["class"] = picojson::value("AstronautsIceCream");
        json["name"] = picojson::value(name_);
        json["size"] = picojson::value(size_);

        picojson::array flagsArray;
        flagsArray.push_back(picojson::value("keepFrozen"));
        flagsArray.push_back(picojson::value("keepDry"));

        // Sort the flags array
        std::sort(flagsArray.begin(), flagsArray.end(), [](const picojson::value& a, const picojson::value& b) {
            return a.serialize() < b.serialize();
        });

        json["flags"] = picojson::value(flagsArray);

        return json;
    }

    warehouseInterface::ProductDescriptionJson serialize() const override
    {
        return picojson::value(asJson()).serialize();
    }

private:
    std::string name_;
    float size_;
};

class AcetoneBarrel : public warehouseInterface::IProduct
{
public:
    AcetoneBarrel(const std::string& name, const float size) : name_(name), size_(size) {}

    std::string name() const override { return name_; }

    std::string className() const {
        return "AcetoneBarrel";
    }

    float itemSize() const override { return size_; }

    warehouseInterface::ProductLabelFlags itemFlags() const override
    {
        return combineFlags(
            warehouseInterface::ProductLabelFlags::fireHazardous,
            warehouseInterface::ProductLabelFlags::esdSensitive
        );
    }

    picojson::object asJson() const override
    {
        picojson::object json;
        json["class"] = picojson::value("AcetoneBarrel");
        json["name"] = picojson::value(name_);
        json["size"] = picojson::value(size_);

        picojson::array flagsArray;
        flagsArray.push_back(picojson::value("fireHazardous"));
        flagsArray.push_back(picojson::value("esdSensitive"));
        json["flags"] = picojson::value(flagsArray);

        return json;
    }

    warehouseInterface::ProductDescriptionJson serialize() const override
    {
        return picojson::value(asJson()).serialize();
    }

private:
    std::string name_;
    float size_;
};

class TV : public warehouseInterface::IProduct
{
public:
    TV(const std::string& name, const float size) : name_(name), size_(size) {}

    std::string name() const override { return name_; }

    std::string className() const {
        return "TV";
    }

    float itemSize() const override { return size_; }

    warehouseInterface::ProductLabelFlags itemFlags() const override
    {
        return combineFlags(
            warehouseInterface::ProductLabelFlags::fragile,
            warehouseInterface::ProductLabelFlags::keepDry
        );
    }

    picojson::object asJson() const override
    {
        picojson::object json;
        json["class"] = picojson::value("TV");
        json["name"] = picojson::value(name_);
        json["size"] = picojson::value(size_);

        picojson::array flagsArray;
        flagsArray.push_back(picojson::value("fragile"));
        flagsArray.push_back(picojson::value("keepDry"));
        json["flags"] = picojson::value(flagsArray);

        return json;
    }

    warehouseInterface::ProductDescriptionJson serialize() const override
    {
        return picojson::value(asJson()).serialize();
    }

private:
    std::string name_;
    float size_;
};

warehouseInterface::ProductLabelFlags combineFlags(warehouseInterface::ProductLabelFlags flag1, warehouseInterface::ProductLabelFlags flag2)
{
    return static_cast<warehouseInterface::ProductLabelFlags>(
        static_cast<int>(flag1) | static_cast<int>(flag2)
    );
}
warehouseInterface::ProductLabelFlags combineFlags2(warehouseInterface::ProductLabelFlags flag1, warehouseInterface::ProductLabelFlags flag2, warehouseInterface::ProductLabelFlags flag3, warehouseInterface::ProductLabelFlags flag4)
{
    return static_cast<warehouseInterface::ProductLabelFlags>(
        static_cast<int>(flag1) | static_cast<int>(flag2) | static_cast<int>(flag3) | static_cast<int>(flag4)
    );
}
 warehouseInterface::ProductLabelFlags combineFlags3(warehouseInterface::ProductLabelFlags flag1, warehouseInterface::ProductLabelFlags flag2, warehouseInterface::ProductLabelFlags flag3){
    return static_cast<warehouseInterface::ProductLabelFlags>(
        static_cast<int>(flag1) | static_cast<int>(flag2) | static_cast<int>(flag3)
    );
 }
}