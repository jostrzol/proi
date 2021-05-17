#pragma once

#include "product.h"
#include "contractor.h"

enum PurchaseConfirmationType
{
    PCReceipt,
    PCInvoice
};

class CashRegister;

class IBuyer : public virtual IContractor, public virtual Entity
{
public:
    virtual const IProduct::ProductMap &GetProducts() const = 0;
    virtual bool Pay(PriceT price) = 0;
    virtual PurchaseConfirmationType GetPCType() const = 0;

    virtual void JoinQueue(CashRegister &cr) = 0;
    virtual CashRegister *GetCashRegister() = 0;
    virtual CashRegister *DeassignCashRegister() = 0;
};