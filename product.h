#pragma once

#include "units.h"
#include "entity.h"
#include "string"

class IProduct : public virtual Entity
{
private:
    struct PtrHash
    {
        std::size_t operator()(const IProduct *product) const;
    };
    struct PtrEqualTo
    {
        bool operator()(const IProduct *first, const IProduct *second) const;
    };

public:
    virtual std::string Name() const = 0;
    virtual UnitT Unit() const = 0;
    virtual PriceT PriceNetto(double amount) const = 0;
    virtual PriceT Tax(double amount) const = 0;

    virtual PriceT PriceBrutto(double amount) const;

    typedef std::unordered_map<const IProduct *, double, PtrHash, PtrEqualTo> ProductMap;
};