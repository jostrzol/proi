#include <iostream>
#include <cmath>
#include "item.h"

Item::Item(std::string name, PriceT pricePerUnit, UnitT unit)
    : name(name), unitPrice(pricePerUnit), unit(unit) {}

PriceT Item::Price(const double &amount)
{
    return round(amount * unitPrice);
}

std::string Item::Name() { return name; }
PriceT Item::UnitPrice() { return unitPrice; }
UnitT Item::Unit() { return unit; }
