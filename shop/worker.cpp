#include "worker.h"

Worker::Worker(int id, std::string name, std::string address, std::string phone)
    : Person(id, name, address, phone), cashRegister(nullptr) {}

void Worker::AssignCashRegister(CashRegister *cashRegister_)
{
    cashRegister = cashRegister_;
    cashRegister->AssignWorker(this);
}

CashRegister *Worker::GetCashRegister() { return cashRegister; }

CashRegister *Worker::FreeCashRegister()
{
    cashRegister->FreeWorker();
    CashRegister *tmp = cashRegister;
    cashRegister = nullptr;
    return tmp;
}
