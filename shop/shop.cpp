#include <sstream>

#include "shop.h"

std::size_t Shop::ItemHash::operator()(const Item &item) const
{
    return std::hash<Entity>()(item);
}

Shop::Shop(int id, std::string name, std::string address, std::string phone)
    : Entity(id), name(name), address(address), phone(phone) {}

const Shop::ItemMap &Shop::GetItems() const { return items; }

void Shop::SetItemAmount(const Item &item, double amount)
{
    if (amount == 0)
        items.erase(item);
    else
        items[item] = amount;
}

void Shop::RemoveItem(const Item &item)
{
    items.erase(item);
}

const Shop::WorkerMap &Shop::GetWorkers() const
{
    return workers;
}

void Shop::AddWorker(Worker &worker)
{
    workers[worker.GetID()] = &worker;
}

void Shop::RemoveWorker(int id)
{
    workers.erase(id);
    DeassignWorker(id);
}

const Shop::CashRegisterMap &Shop::GetCashRegisters() const
{
    return cashRegisters;
}

void Shop::AddCashRegister(CashRegister &cashRegister)
{
    cashRegisters[cashRegister.GetID()] = &cashRegister;
}

void Shop::RemoveCashRegister(int id)
{
    cashRegisters.erase(id);
}

const Shop::CustomerMap &Shop::GetCustomers() const
{
    return customers;
}

void Shop::AddCustomer(Customer &customer)
{
    customers[customer.GetID()] = &customer;
}

void Shop::RemoveCustomer(int id)
{
    customers.erase(id);
}

const Shop::WorkerMap &Shop::GetCashWorkers() const
{
    return cashWorkers;
}

void Shop::AssignWorkerToCashRegister(Worker &worker, CashRegister &cr)
{
    if (workers.find(worker.GetID()) == workers.end())
        throw ErrorWorkerNotInShop(worker);
    DeassignWorker(worker.GetID());
    worker.AssignCashRegister(&cr);
    cashWorkers[worker.GetID()] = &worker;
}

const Shop::WorkerMap &Shop::GetHelperWorkers() const
{
    return helperWorkers;
}

void Shop::AssignWorkerToHelping(Worker &worker)
{
    if (workers.find(worker.GetID()) == workers.end())
        throw ErrorWorkerNotInShop(worker);
    DeassignWorker(worker.GetID());
    helperWorkers[worker.GetID()] = &worker;
}

void Shop::DeassignWorker(int id)
{
    helperWorkers.erase(id);
    cashWorkers.erase(id);
}

PriceT Shop::GetMoney() const
{
    return money;
}

void Shop::SetMoney(PriceT val)
{
    money = val;
}

const Person *Shop::GetManager() const
{
    return manager;
}

void Shop::SetManager(const Person *manager_)
{
    manager = manager_;
}

std::chrono::minutes Shop::GetOpenTime() const
{
    return openTime;
}

void Shop::SetOpenTime(std::chrono::minutes val)
{
    openTime = val;
}

std::chrono::minutes Shop::GetCloseTime() const
{
    return closeTime;
}

void Shop::SetCloseTime(std::chrono::minutes val)
{
    closeTime = val;
}

std::string Shop::GetWorkingTime() const
{
    std::stringstream ss;
    ss << minutesToDaytime(openTime) << " - " << minutesToDaytime(closeTime);
    return ss.str();
}

std::string Shop::GetName() const
{
    return name;
}

void Shop::SetName(std::string val)
{
    name = val;
}

std::string Shop::GetAddress() const
{
    return address;
}

void Shop::SetAddress(std::string val)
{
    address = val;
}

std::string Shop::GetPhone() const
{
    return phone;
}

void Shop::SetPhone(std::string val)
{
    phone = val;
}

std::string Shop::minutesToDaytime(std::chrono::minutes minutes)
{
    std::stringstream ss;
    auto hours = std::chrono::duration_cast<std::chrono::hours>(minutes);
    ss << hours.count() << ":" << (minutes - hours).count();
    return ss.str();
}

ErrorWorkerNotInShop::ErrorWorkerNotInShop(Worker &worker)
    : std::invalid_argument("Worker not in shop"), worker(worker) {}
