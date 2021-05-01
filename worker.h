#pragma once

#include "cash_worker.h"
#include "cash_register.h"
#include "person.h"

class Worker : public virtual ICashWorker, public virtual Person
{
public:
    Worker(std::string name = "", std::string address = "", std::string phone = "", int id = -1, CashRegister *cashRegister = nullptr);

    void AssignCashRegister(CashRegister *cashRegister_);
    CashRegister *AssignedCashRegister();
    CashRegister *FreeCashRegister();

private:
    CashRegister *cashRegister;
};