#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include "entity.h"
#include "units.h"

class Item : public Entity
{
private:
    std::string name;
    PriceT unitPrice;
    double tax;
    UnitT unit;

public:
    Item(std::string name, PriceT pricePerUnit, UnitT unit, double tax = 0, int id = -1);

    bool operator==(const Item &other) const;

    friend std::hash<Item>;
    friend std::ostream &operator<<(std::ostream &os, const Item &item);

    std::string Name() const;
    UnitT Unit() const;

    PriceT UnitPriceNetto() const;
    PriceT UnitPriceBrutto() const;
    PriceT UnitTax() const;

    PriceT PriceNetto(const double &amount);
    PriceT PriceBrutto(const double &amount);
    PriceT Tax(const double &amount);
};

namespace std
{
    template <>
    struct hash<Item>
    {
        std::size_t operator()(const Item &k) const;
    };
}

#endif