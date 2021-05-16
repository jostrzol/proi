#include <iostream>
#include <cmath>
#include "item.h"

Item::Item(int id, std::string name, PriceT pricePerUnit, UnitT unit, double unitTax, std::string category)
    : Entity(id), name(name), unitPriceNetto(pricePerUnit), unit(unit), unitTax(unitTax), category(category) {}

std::ostream &operator<<(std::ostream &os, const Item &item)
{
    os << item.name << " [" << item.UnitPriceBrutto() << " per " << item.unit << "]";
    return os;
}

PriceT Item::PriceNetto(double amount) const
{
    return UnitPriceNetto() * amount;
}

PriceT Item::PriceBrutto(double amount) const
{
    return UnitPriceBrutto() * amount;
}

PriceT Item::Tax(double amount) const
{
    return UnitTax() * amount;
}

std::string Item::GetCategory() const
{
    return category;
}

void Item::SetCategory(std::string val)
{
    category = val;
}

std::string Item::GetName() const { return name; }

void Item::SetName(std::string val) { name = val; }

PriceT Item::UnitPriceNetto() const { return unitPriceNetto; }

void Item::SetUnitPriceNetto(PriceT val) { unitPriceNetto = val; }

PriceT Item::UnitPriceBrutto() const { return UnitPriceNetto() + UnitTax(); }

PriceT Item::UnitTax() const { return unitPriceNetto * unitTax; }

void Item::SetUnitTax(double val) { unitTax = val; }

UnitT Item::GetUnit() const { return unit; }

void Item::SetUnit(UnitT val) { unit = val; }