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
    virtual const IProduct::ProductMap &GetProducts() const = 0;
    virtual bool Pay(PriceT price) = 0;
    virtual PurchaseConfirmationType GetPCType() const = 0;
};