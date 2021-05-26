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
    std::stringstream msg;
    msg << "	I haven't been trained to answer this question.\n";
    return msg.str();
}

std::string Worker::Answer(const QuestionItemPrice &q)
{
    std::stringstream msg;
    msg << "	This item's price is " << q.item.UnitPriceBrutto();
    msg << " per " << q.item.GetUnit() << " (including ";
    msg << q.item.GetUnitTaxPercentage() << "% tax).\n";
    return msg.str();
}

std::string Worker::Answer(const QuestionItemName &q)
{
    std::stringstream msg;
    msg << "	This item's name is " << shop.GetItem(q.itemId).first->GetName() << ".\n";
    return msg.str();
}

std::string Worker::Answer(const QuestionItemCategory &q)
{
    std::stringstream msg;
    msg << "	This item's category is " << shop.GetItem(q.itemId).first->GetCategory() << ".\n";
    return msg.str();
}

std::string Worker::Answer(const QuestionManager &)
{
    std::stringstream msg;
    msg << "	The shop's manager's name is " << shop.GetManager()->GetName() << ".\n";
    return msg.str();
}

std::string Worker::Answer(const QuestionWorkerInfo &)
{
    std::stringstream msg;
    msg << "	My name is " << GetName() << " and my worker id is " << GetID() << ".\n";
    return msg.str();
};

std::string Worker::Answer(const QuestionShopPhoneNumber &)
{
    std::stringstream msg;
    msg << "	This shop's phone number is as follows: " << shop.GetPhone() << ".\n";
    return msg.str();
};
