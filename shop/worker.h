#pragma once

#include "cash_worker.h"
#include "cash_register.h"
#include "person.h"
#include "helper_worker.h"
#include "customer.h"

class Shop;

class Worker : public virtual ICashWorker, public virtual Person, public virtual IHelperWorker
{
public:
    Worker(Shop &shop, int id = -1, std::string name = "", std::string address = "", std::string phone = "");

    void AssignCashRegister(CashRegister *cashRegister_);
    CashRegister *GetCashRegister();
    CashRegister *FreeCashRegister();

    void SetBusy(bool val);
    bool GetBusy();

    // Returns the worker's shop
    Shop &GetShop() const;

    // Answer unknown question
    template <class T>
    std::string Answer(const T &q);
    // Answer unknown question
    std::string Answer(const QuestionItemPrice &q);
    // Answet question about item name
    std::string Answer(const QuestionItemName &q);
    // Answet question about item category
    std::string Answer(const QuestionItemCategory &q);
    // Answet question about shop manager
    std::string Answer(const QuestionManager &);
    // Answet question about self
    std::string Answer(const QuestionWorkerInfo &);
    // Answet question about shop phone number
    std::string Answer(const QuestionShopPhoneNumber &);

private:
    CashRegister *cashRegister;
    Shop &shop;
    bool busy;
};
