#pragma once

#include "cash_register.h"

class CashRegister;

class ICashWorker
{
public:
    virtual void AssignCashRegister(CashRegister *cashRegister) = 0;
    virtual CashRegister *GetCashRegister() = 0;
    virtual CashRegister *FreeCashRegister() = 0;
};