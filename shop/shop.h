#pragma once

#include <unordered_map>
#include <chrono>
#include <exception>

#include "contractor.h"
#include "worker.h"
#include "item.h"
#include "customer.h"

class Shop : public virtual IContractor, public virtual Entity
{
private:
    struct ItemHash
    {
        std::size_t operator()(const Item &item) const;
    };
    typedef std::unordered_map<Item, double, ItemHash> ItemMap;
    typedef std::unordered_map<int, Worker *> WorkerMap;
    typedef std::unordered_map<int, CashRegister *> CashRegisterMap;
    typedef std::unordered_map<int, Customer *> CustomerMap;

public:
    Shop(int id = -1, std::string name = "", std::string address = "", std::string phone = "");

    const ItemMap &GetItems() const;
    void SetItemAmount(const Item &item, double amount);
    void RemoveItem(const Item &item);

    const WorkerMap &GetWorkers() const;
    void AddWorker(Worker &worker);
    void RemoveWorker(int id);

    const CashRegisterMap &GetCashRegisters() const;
    void AddCashRegister(CashRegister &cashRegister);
    void RemoveCashRegister(int id);

    const CustomerMap &GetCustomers() const;
    void AddCustomer(Customer &customer);
    void RemoveCustomer(int id);

    const WorkerMap &GetCashWorkers() const;
    void AssignWorkerToCashRegister(Worker &worker, CashRegister &cr);

    const WorkerMap &GetHelperWorkers() const;
    void AssignWorkerToHelping(Worker &worker);

    void DeassignWorker(int id);

    PriceT GetMoney() const;
    void SetMoney(PriceT val);

    const Person *GetManager() const;
    void SetManager(const Person *manager_);

    std::chrono::minutes GetOpenTime() const;
    void SetOpenTime(std::chrono::minutes val);
    std::chrono::minutes GetCloseTime() const;
    void SetCloseTime(std::chrono::minutes val);

    std::string GetWorkingTime() const;

    std::string GetName() const;
    void SetName(std::string val);
    std::string GetAddress() const;
    void SetAddress(std::string val);
    std::string GetPhone() const;
    void SetPhone(std::string val);

private:
    ItemMap items;
    WorkerMap workers;
    CustomerMap customers;
    CashRegisterMap cashRegisters;

    WorkerMap cashWorkers;
    WorkerMap helperWorkers;

    PriceT money;
    const Person *manager;

    std::chrono::minutes openTime;
    std::chrono::minutes closeTime;
    static std::string minutesToDaytime(std::chrono::minutes minutes);

    std::string name;
    std::string address;
    std::string phone;
};

struct ErrorWorkerNotInShop : std::invalid_argument
{
    ErrorWorkerNotInShop(Worker &worker);
    Worker &worker;
};