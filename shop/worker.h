#pragma once

#include "cash_worker.h"
#include "cash_register.h"
#include "person.h"

class Shop;

class Worker : public virtual ICashWorker, public virtual Person
{
public:
    Worker(Shop &shop, int id = -1, std::string name = "", std::string address = "", std::string phone = "");

    void AssignCashRegister(CashRegister *cashRegister_);
    CashRegister *GetCashRegister();
    CashRegister *FreeCashRegister();

    // Returns the worker's shop
    Shop &GetShop() const;

private:
    CashRegister *cashRegister;
    Shop &shop;
};
