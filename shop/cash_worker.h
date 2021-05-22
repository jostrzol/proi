#pragma once

class CashRegister;

class ICashWorker
{
public:
    // Assigns this worker to cash register and the cash register to the worker
    virtual void AssignCashRegister(CashRegister *cashRegister) = 0;
    // Returns the cash register that this worker is managing
    virtual CashRegister *GetCashRegister() = 0;
    // Returns the cash register that this worker was managing and frees him and the cash register
    virtual CashRegister *FreeCashRegister() = 0;

    virtual ~ICashWorker() = 0;
};
inline ICashWorker::~ICashWorker() = default;