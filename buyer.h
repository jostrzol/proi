#pragma once

#include "product.h"
#include "contractor.h"

enum PurchaseConfirmationType
{
    PCReceipt,
    PCInvoice
};

class IBuyer : public virtual IContractor
{
public:
    virtual const IProduct::ProductMap &Products() const = 0;
    virtual bool Pay(PriceT price) = 0;
    virtual PurchaseConfirmationType PCType() const = 0;
};