#include "worker.h"

Worker::Worker(std::string name, std::string address, std::string phone, int id)
    : Person(name, address, phone, id), cashRegister(nullptr) {}

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
