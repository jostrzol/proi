#pragma once

#include <string>
#include <unordered_map>

#include "units.h"
#include "entity.h"

class IProduct : public virtual Entity
{

public:
    // Returns the product's name
    virtual std::string GetName() const = 0;
    // Returns the product's unit
    virtual UnitT GetUnit() const = 0;
    // Returns the product's price netto for the given amount
    virtual PriceT PriceNetto(double amount) const = 0;
    // Returns the product's tax for the given amount
    virtual PriceT Tax(double amount) const = 0;

    // Returns the product's price brutto for the given amount
    virtual PriceT PriceBrutto(double amount) const;

    typedef std::unordered_map<const IProduct *, double, Entity::PtrHash, Entity::PtrEqualTo> ProductMap;
};
