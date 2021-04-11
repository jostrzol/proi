#include <iostream>
#include <cmath>
#include "item.h"

Item::Item(std::string name, PriceT pricePerUnit, UnitT unit)
    : name(name), unitPrice(pricePerUnit), unit(unit) {}

std::ostream &operator<<(std::ostream &os, const Item &item)
{
    os << item.name << "[" << item.unitPrice << " per " << item.unit << "]";
    return os;
};

PriceT Item::Price(const double &amount)
{
    return round(amount * unitPrice);
}

std::string Item::Name() const { return name; }
PriceT Item::UnitPrice() const { return unitPrice; }
UnitT Item::Unit() const { return unit; }
