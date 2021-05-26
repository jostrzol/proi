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
    typedef std::unordered_map<int, Customer *> CustomerStatusMap;

public:
    Shop(int id = -1, std::string name = "", std::string address = "", std::string phone = "");

    // Returns the shop's items
    ItemMap &GetItems();
    // Adds a new item to the shop
    Item &AddItem(int id, std::string name = "", PriceT pricePerUnit = 0, UnitT unit = pcs, double unitTaxPercentage = 0, std::string category = "", double amount = 0);
    // Removes an new item to the shop
    void RemoveItem(int id);
    // Sets the amount of item in the shop
    void SetItemAmount(int id, double amount);
    // Returns an item and its amount given its ID
    std::pair<Item *, double> GetItem(int id);
    // Removes <amount> of item with the given id and returns the amount removed
    // Will remove less if there isn't enough of the given item in shop
    double TakeItem(int id, double amount);
    // Deopsits the <amount> of item with the given id and returns true on success
    bool DepositItem(int id, double amount);
    // Returns items with the given category in shop
    std::vector<Item *> &GetItemsCategory(std::string category);

    // Returns shop's workers
    WorkerMap &GetWorkers();
    // Adds a new worker to the shop
    Worker &AddWorker(int id, std::string name = "", std::string address = "", std::string phone = "");
    // Removes a worker from the shop
    void RemoveWorker(Worker &worker);
    // Checks if the worker is assigned to work
    bool WorkerIsAssigned(int id);

    // Returns the shop's cash registers
    CashRegisterMap &GetCashRegisters();
    // Adds a new cash register to the shop
    CashRegister &AddCashRegister(int id);
    // Removes a cash register from the shop
    void RemoveCashRegister(int id);
    // Returns opened cash registers
    CashRegisterStatusMap &GetOpenCashRegisters();
    // Returns closed cash registers
    CashRegisterStatusMap &GetCloseCashRegisters();

    // Returns the shop's customers
    CustomerMap &GetCustomers();
    // Adds a new customer to the shop
    Customer &AddCustomer(int id, std::string name = "", std::string address = "", std::string phone = "", PriceT money = 0);
    // Removes a customer from the shop
    void RemoveCustomer(int id);

    // Returns the shop's cash workers
    WorkerAssignmentMap &GetCashWorkers();
    // Assigns a worker to a cash register
    void AssignWorkerToCashRegister(Worker &worker, CashRegister &cr);

    // Returns the shop's helper workers
    WorkerAssignmentMap &GetHelperWorkers();
    // Assigns a worker to helping the customers
    void AssignWorkerToHelping(Worker &worker);

    // Deassigns a worker completely from any work
    void DeassignWorker(Worker &worker);

    // Returns the shop's money
    PriceT GetMoney() const;
    // Sets the shop's money
    void SetMoney(PriceT val);

    // Returns the shop's manager
    Person *GetManager();
    // Sets the shop's manager
    void SetManager(Person *manager_);

    // Returns the shop's opening time
    std::chrono::minutes GetOpenTime() const;
    // Sets the shop's opening time
    void SetOpenTime(std::chrono::minutes val);
    // Returns the shop's closing time
    std::chrono::minutes GetCloseTime() const;
    // Sets the shop's closing time
    void SetCloseTime(std::chrono::minutes val);

    // Returns the shop's working time in format <OpeningTime> - <ClosingTime>
    std::string GetWorkingTime() const;

    std::string GetName() const;
    void SetName(std::string val);
    std::string GetAddress() const;
    void SetAddress(std::string val);
    std::string GetPhone() const;
    void SetPhone(std::string val);

    // Opens the shop
    void Open();
    // Closes the shop
    void Close();
    // Checks if the shop is opened
    bool IsOpen();

    // Returns details about the shop and its objects
    std::string Details();

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

    std::string name;
    std::string address;
    std::string phone;

    bool isOpen = false;
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
