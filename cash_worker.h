#pragma once

#include "cash_register.h"

class CashRegister;

class ICashWorker : public virtual Entity
{
public:
    virtual bool ServeNext();

    virtual void AssignCashRegister(CashRegister *cashRegister) = 0;
    virtual CashRegister *AssignedCashRegister() = 0;
    virtual CashRegister *FreeCashRegister() = 0;
};