#include <iostream>
#include <cmath>
#include "item.h"

Item::Item(std::string name, PriceT pricePerUnit, UnitT unit)
    : name(name), unitPrice(pricePerUnit), unit(unit) {}

bool Item::operator==(const Item &other) const
{
    return name == other.name && unit == other.unit && unitPrice == other.unitPrice;
}

std::ostream &operator<<(std::ostream &os, const Item &item)
{
    os << item.name << " [" << item.unitPrice << " per " << item.unit << "]";
    return os;
}

PriceT Item::Price(const double &amount)
{
    return unitPrice * amount;
}

std::string Item::Name() const { return name; }
PriceT Item::UnitPrice() const { return unitPrice; }
UnitT Item::Unit() const { return unit; }

std::size_t std::hash<Item>::operator()(const Item &item) const
{
    std::size_t h = 17;

    h = h * 31 + hash<string>()(item.name);
    h = h * 31 + hash<int>()(item.unit);
    h = h * 31 + hash<int>()(int(item.unitPrice));

    return h;
}
