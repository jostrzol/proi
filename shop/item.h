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

    // Returns the item's name
    std::string GetName() const;
    // Sets the item's name
    void SetName(std::string val);

    // Returns the item's unit
    UnitT GetUnit() const;
    // Sets the item's unit
    void SetUnit(UnitT val);

    // Returns the item's unit price netto
    PriceT UnitPriceNetto() const;
    // Sets the item's unit price netto
    void SetUnitPriceNetto(PriceT val);

    // Returns the item's unit tax
    double UnitTax() const;
    // Sets the item's unit tax
    void SetUnitTax(double val);

    // Returns the item's unit price brutto
    PriceT UnitPriceBrutto() const;

    // Returns the item's price netto for the given amount
    PriceT PriceNetto(double amount) const;
    // Returns the item's price brutto for the given amount
    PriceT PriceBrutto(double amount) const;
    // Returns the item's tax for the given amount
    PriceT Tax(double amount) const;

    // Returns the category of the item
    std::string GetCategory() const;
    // Sets the category of the item
    void SetCategory(std::string val);
};