#include <iostream>
#include <cmath>
#include "item.h"

Item::Item(std::string name, PriceT pricePerUnit, UnitT unit)
    : name(name), pricePerUnit(pricePerUnit), unit(unit) {}

PriceT Item::Price(const double &amount)
{
    return round(amount * pricePerUnit);
}

std::string Item::Name() { return name; }
PriceT Item::PricePerUnit() { return pricePerUnit; }
UnitT Item::Unit() { return unit; }
