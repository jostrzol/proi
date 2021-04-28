#include <iostream>
#include <cmath>
#include "item.h"

Item::Item(std::string name, PriceT pricePerUnit, UnitT unit, double tax, int id)
    : Entity(id), name(name), unitPriceNetto(pricePerUnit), unit(unit), tax(tax) {}

std::ostream &operator<<(std::ostream &os, const Item &item)
{
    os << item.name << " [" << item.UnitPriceBrutto() << " per " << item.unit << "]";
    return os;
}

PriceT Item::PriceNetto(const double &amount)
{
    return UnitPriceNetto() * amount;
}

PriceT Item::PriceBrutto(const double &amount)
{
    return UnitPriceBrutto() * amount;
}

PriceT Item::Tax(const double &amount)
{
    return UnitTax() * amount;
}

std::string Item::Name() const { return name; }

void Item::SetName(std::string val) { name = val; }

PriceT Item::UnitPriceNetto() const { return unitPriceNetto; }

void Item::SetUnitPriceNetto(PriceT val) { unitPriceNetto = val; }

PriceT Item::UnitPriceBrutto() const { return UnitPriceNetto() + UnitTax(); }

PriceT Item::UnitTax() const { return unitPriceNetto * tax; }

void Item::SetTax(double val) { tax = val; }

UnitT Item::Unit() const { return unit; }

void Item::SetUnit(UnitT val) { unit = val; }