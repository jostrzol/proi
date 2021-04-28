#pragma once

#include "units.h"
#include "entity.h"
#include "string"

class IProduct : public virtual Entity
{
public:
    virtual std::string Name() const = 0;
    virtual UnitT Unit() const = 0;
    virtual PriceT PriceNetto(double amount) const = 0;
    virtual PriceT Tax(double amount) const = 0;

    virtual PriceT PriceBrutto(double amount) const;
};