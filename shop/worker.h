#pragma once

#include "cash_worker.h"
#include "cash_register.h"
#include "person.h"

class Worker : public virtual ICashWorker, public virtual Person
{
public:
    Worker(int id = -1, std::string name = "", std::string address = "", std::string phone = "");

    void AssignCashRegister(CashRegister *cashRegister_);
    CashRegister *GetCashRegister();
    CashRegister *FreeCashRegister();

private:
    CashRegister *cashRegister;
};