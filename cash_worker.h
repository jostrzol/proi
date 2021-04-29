#pragma once

#include "cash_register.h"
#include "entity.h"

class ICashWorker : public virtual Entity
{
    virtual void ServeNext() = 0;

    virtual void AssignCashRegister(const CashRegister &cashRegister) = 0;
    virtual const CashRegister &FreeCashRegister() = 0;
};