#pragma once
#include <string>
#include <iostream>
#include "product.h"
#include "units.h"

class Item : public IProduct
{
private:
    std::string name;
    PriceT unitPriceNetto;
    UnitT unit;
    double tax;

public:
    Item(std::string name, PriceT pricePerUnit, UnitT unit, double tax = 0, int id = -1);

    friend std::ostream &operator<<(std::ostream &os, const Item &item);

    std::string Name() const;
    void SetName(std::string val);

    UnitT Unit() const;
    void SetUnit(UnitT val);

    PriceT UnitPriceNetto() const;
    void SetUnitPriceNetto(PriceT val);

    PriceT UnitTax() const;
    void SetTax(double val);

    PriceT UnitPriceBrutto() const;

    PriceT PriceNetto(const double &amount);
    PriceT PriceBrutto(const double &amount);
    PriceT Tax(const double &amount);
};