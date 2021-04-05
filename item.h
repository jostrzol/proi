#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "units.h"

class Item
{
private:
    std::string name;
    PriceT pricePerUnit;
    UnitT unit;

public:
    Item(std::string name, PriceT pricePerUnit, UnitT unit);

    std::string Name();
    PriceT PricePerUnit();
    UnitT Unit();

    PriceT Price(const double &amount);
    friend std::hash<Item>;
};

#endif