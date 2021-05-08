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
    double unitTax;

public:
    Item(int id = -1, std::string name = "", PriceT pricePerUnit = 0, UnitT unit = pcs, double unitTax = 0);

    friend std::ostream &operator<<(std::ostream &os, const Item &item);

    std::string GetName() const;
    void SetName(std::string val);

    UnitT GetUnit() const;
    void SetUnit(UnitT val);

    PriceT UnitPriceNetto() const;
    void SetUnitPriceNetto(PriceT val);

    PriceT UnitTax() const;
    void SetUnitTax(double val);

    PriceT UnitPriceBrutto() const;

    PriceT PriceNetto(double amount) const;
    PriceT PriceBrutto(double amount) const;
    PriceT Tax(double amount) const;
};