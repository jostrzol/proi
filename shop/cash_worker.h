#pragma once

class CashRegister;

class ICashWorker
{
public:
    virtual void AssignCashRegister(CashRegister *cashRegister) = 0;
    virtual CashRegister *GetCashRegister() = 0;
    virtual CashRegister *FreeCashRegister() = 0;

    virtual ~ICashWorker() = 0;
};
inline ICashWorker::~ICashWorker() = default;