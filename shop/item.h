#pragma once
#include <string>
#include <iostream>
#include "product.h"
#include "units.h"

class Item : public virtual IProduct
{
private:
    std::string name;
    PriceT unitPriceNetto;
    UnitT unit;
    double unitTax;
    std::string category;

public:
    Item(int id = -1, std::string name = "", PriceT pricePerUnit = 0, UnitT unit = pcs, double unitTax = 0, std::string category = "");

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

    std::string GetCategory() const;
    void SetCategory(std::string val);
};