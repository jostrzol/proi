#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include "units.h"

class Item
{
private:
    std::string name;
    PriceT unitPrice;
    UnitT unit;

public:
    Item(std::string name, PriceT pricePerUnit, UnitT unit);

    friend std::ostream &operator<<(std::ostream &os, const Item &item);

    std::string Name() const;
    PriceT UnitPrice() const;
    UnitT Unit() const;

    PriceT Price(const double &amount);
    friend std::hash<Item>;
};

#endif