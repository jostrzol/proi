#pragma once

#include "product.h"

class IBuyer : public virtual Entity
{
    virtual const IProduct::ProductMap &Products() const = 0;
    virtual void Pay(PriceT price) = 0;
};