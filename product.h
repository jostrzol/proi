#pragma once

#include <string>
#include <unordered_map>

#include "units.h"
#include "entity.h"

class IProduct : public virtual Entity
{

public:
    virtual std::string GetName() const = 0;
    virtual UnitT GetUnit() const = 0;
    virtual PriceT PriceNetto(double amount) const = 0;
    virtual PriceT Tax(double amount) const = 0;

    virtual PriceT PriceBrutto(double amount) const;

    typedef std::unordered_map<const IProduct *, double, Entity::PtrHash, Entity::PtrEqualTo> ProductMap;
};