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
    typedef std::unordered_map<int, std::pair<Item, double>> ItemMap;
    typedef std::unordered_map<std::string, std::vector<Item *>> ItemCategoryMap;
    typedef std::unordered_map<int, Worker> WorkerMap;
    typedef std::unordered_map<int, Worker *> WorkerAssignmentMap;
    typedef std::unordered_map<int, CashRegister> CashRegisterMap;
    typedef std::unordered_map<int, CashRegister *> CashRegisterStatusMap;
    typedef std::unordered_map<int, Customer> CustomerMap;

public:
    Shop(int id = -1, std::string name = "", std::string address = "", std::string phone = "");

    ItemMap &GetItems();
    Item &AddItem(int id, std::string name = "", PriceT pricePerUnit = 0, UnitT unit = pcs, double unitTax = 0, std::string category = "", double amount = 0);
    void RemoveItem(int id);
    void SetItemAmount(int id, double amount);
    std::pair<Item *, double> GetItem(int id);
    std::vector<Item *> &GetItemsCategory(std::string category);

    WorkerMap &GetWorkers();
    Worker &AddWorker(int id, std::string name = "", std::string address = "", std::string phone = "");
    void RemoveWorker(Worker &worker);
    bool WorkerIsAssigned(int id);

    CashRegisterMap &GetCashRegisters();
    CashRegister &AddCashRegister(int id);
    void RemoveCashRegister(int id);
    CashRegisterStatusMap &GetOpenCashRegisters();
    CashRegisterStatusMap &GetCloseCashRegisters();

    CustomerMap &GetCustomers();
    Customer &AddCustomer(int id, std::string name = "", std::string address = "", std::string phone = "", PriceT money = 0);
    void RemoveCustomer(int id);

    WorkerAssignmentMap &GetCashWorkers();
    void AssignWorkerToCashRegister(Worker &worker, CashRegister &cr);

    WorkerAssignmentMap &GetHelperWorkers();
    void AssignWorkerToHelping(Worker &worker);

    void DeassignWorker(Worker &worker);

    PriceT GetMoney() const;
    void SetMoney(PriceT val);

    Person *GetManager();
    void SetManager(Person *manager_);

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
    ItemCategoryMap itemsCategory;
    WorkerMap workers;
    CustomerMap customers;
    CashRegisterMap cashRegisters;
    CashRegisterStatusMap openCashRegisters;
    CashRegisterStatusMap closeCashRegisters;

    WorkerAssignmentMap cashWorkers;
    WorkerAssignmentMap helperWorkers;

    PriceT money;
    Person *manager;

    std::chrono::minutes openTime = std::chrono::hours(8);
    std::chrono::minutes closeTime = std::chrono::hours(20);
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

struct ErrorIDTaken : std::invalid_argument
{
    ErrorIDTaken(int id);
    int id;
};

struct ErrorItemNotFound : std::out_of_range
{
    ErrorItemNotFound(int id);
    int id;
};