#include "worker.h"
#include "shop.h"

Worker::Worker(Shop &shop, int id, std::string name, std::string address, std::string phone)
    : Entity(id), Person(id, name, address, phone), cashRegister(nullptr), shop(shop)
{
    return;
}

void Worker::AssignCashRegister(CashRegister *cashRegister_)
{
    cashRegister = cashRegister_;
    cashRegister->AssignWorker(this);
}

void Worker::SetBusy(bool val)
{
    busy = val;
};

bool Worker::GetBusy()
{
    return busy;
};

CashRegister *Worker::GetCashRegister() { return cashRegister; }

CashRegister *Worker::FreeCashRegister()
{
    if (cashRegister != nullptr)
        cashRegister->FreeWorker();
    CashRegister *tmp = cashRegister;
    cashRegister = nullptr;
    return tmp;
}

Shop &Worker::GetShop() const
{
    return shop;
}
