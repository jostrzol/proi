#include "worker.h"

Worker::Worker(std::string name, std::string address, std::string phone, int id, CashRegister *cashRegister)
    : Person(name, address, phone, id), cashRegister(cashRegister)
{
    if (cashRegister != nullptr)
        cashRegister->AssignWorker(this);
}

void Worker::AssignCashRegister(CashRegister *cashRegister_)
{
    cashRegister = cashRegister_;
    cashRegister->AssignWorker(this);
}

CashRegister *Worker::AssignedCashRegister() { return cashRegister; }

CashRegister *Worker::FreeCashRegister()
{
    cashRegister->FreeWorker();
    CashRegister *tmp = cashRegister;
    cashRegister = nullptr;
    return tmp;
}
