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
    // Return buyer's products
    virtual const IProduct::ProductMap &GetProducts() const = 0;
    // Make buyer pay and return true on success
    virtual bool Pay(PriceT price) = 0;
    // Return buyer's preferred purchase confirmation type
    virtual PurchaseConfirmationType GetPCType() const = 0;

    // Join queue to cash register cr
    virtual void JoinQueue(CashRegister &cr) = 0;
    // Get the cash register of the queue in which th buyer is standing or nullptr
    virtual CashRegister *GetCashRegister() = 0;
    // Deassign buyer's queue
    virtual CashRegister *DeassignCashRegister() = 0;
};