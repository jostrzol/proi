#include <sstream>

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

template <class T>
std::string Worker::Answer(const T &q)
{
    return "I haven't been trained to answer this question.\n";
}

std::string Worker::Answer(const QuestionItemPrice &q)
{
    std::stringstream msg;
    msg << "This item's price is " << shop.GetItem(q.itemId).first->UnitPriceBrutto();
    msg << "per " << shop.GetItem(q.itemId).first->GetUnit() << ".\n";
    return msg.str();
}

std::string Worker::Answer(const QuestionItemName &q)
{
    std::stringstream msg;
    msg << "This item's name is " << shop.GetItem(q.itemId).first->GetName() << ".\n";
    return msg.str();
}

std::string Worker::Answer(const QuestionManager &q)
{
    std::stringstream msg;
    msg << "The shop's manager is worker no. " << shop.GetManager()->GetID();
    msg << ", " << shop.GetManager()->GetName() << ".\n";
    return msg.str();
}
