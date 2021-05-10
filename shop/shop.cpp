#include <sstream>

#include "shop.h"

std::size_t Shop::ItemHash::operator()(const Item &item) const
{
    return std::hash<Entity>()(item);
}

Shop::Shop(int id, std::string name, std::string address, std::string phone)
    : Entity(id), name(name), address(address), phone(phone) {}

Shop::ItemMap &Shop::GetItems() { return items; }

Item &Shop::AddItem(int id, std::string name, PriceT pricePerUnit, UnitT unit, double unitTax)
{
    std::pair<Item, double> pair = {{id, name, pricePerUnit, unit, unitTax}, 0};
    auto emplaced = items.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(id),
        std::forward_as_tuple(
            std::piecewise_construct,
            std::forward_as_tuple(id, name, pricePerUnit, unit, unitTax),
            std::forward_as_tuple(0)));
    if (!emplaced.second)
        throw ErrorIDTaken(id);
    return emplaced.first->second.first;
}

std::pair<Item *, double> Shop::GetItem(int id)
{
    auto it = items.find(id);
    if (it == items.end())
        throw ErrorItemNotFound(id);
    auto &pair = it->second;
    return std::make_pair(&pair.first, pair.second);
}

void Shop::SetItemAmount(int id, double amount)
{
    auto it = items.find(id);
    if (it == items.end())
        throw ErrorItemNotFound(id);
    auto &pair = it->second;
    items[id].second = amount;
}

void Shop::RemoveItem(int id)
{
    items.erase(id);
}

Shop::WorkerMap &Shop::GetWorkers()
{
    return workers;
}

Worker &Shop::AddWorker(int id, std::string name, std::string address, std::string phone)
{
    auto emplaced = workers.emplace(std::piecewise_construct,
                                    std::forward_as_tuple(id),
                                    forward_as_tuple(*this, id, name, address, phone));
    if (!emplaced.second)
        throw ErrorIDTaken(id);
    return emplaced.first->second;
}

void Shop::RemoveWorker(Worker &worker)
{
    workers.erase(worker.GetID());
    DeassignWorker(worker);
}

Shop::CashRegisterMap &Shop::GetCashRegisters()
{
    return cashRegisters;
}

CashRegister &Shop::AddCashRegister(int id)
{
    auto emplaced = cashRegisters.emplace(std::piecewise_construct,
                                          std::forward_as_tuple(id),
                                          std::forward_as_tuple(*this, id));
    if (!emplaced.second)
        throw ErrorIDTaken(id);
    return emplaced.first->second;
}

void Shop::RemoveCashRegister(int id)
{
    cashRegisters.erase(id);
}

Shop::CustomerMap &Shop::GetCustomers()
{
    return customers;
}

Customer &Shop::AddCustomer(int id, std::string name, std::string address, std::string phone, PriceT money)
{
    auto emplaced = customers.emplace(std::piecewise_construct,
                                      std::forward_as_tuple(id),
                                      std::forward_as_tuple(*this, id, name, address, phone, money));
    if (!emplaced.second)
        throw ErrorIDTaken(id);
    return emplaced.first->second;
}

void Shop::RemoveCustomer(int id)
{
    customers.erase(id);
}

Shop::WorkerAssignmentMap &Shop::GetCashWorkers()
{
    return cashWorkers;
}

void Shop::AssignWorkerToCashRegister(Worker &worker, CashRegister &cr)
{
    if (worker.GetShop() != *this)
        throw ErrorWorkerNotInShop(worker);
    DeassignWorker(worker);
    worker.AssignCashRegister(&cr);
    cashWorkers[worker.GetID()] = &worker;
}

Shop::WorkerAssignmentMap &Shop::GetHelperWorkers()
{
    return helperWorkers;
}

void Shop::AssignWorkerToHelping(Worker &worker)
{
    if (worker.GetShop() != *this)
        throw ErrorWorkerNotInShop(worker);
    DeassignWorker(worker);
    helperWorkers[worker.GetID()] = &worker;
}

void Shop::DeassignWorker(Worker &worker)
{
    if (worker.GetShop() != *this)
        throw ErrorWorkerNotInShop(worker);
    worker.FreeCashRegister();
    helperWorkers.erase(worker.GetID());
    cashWorkers.erase(worker.GetID());
}

PriceT Shop::GetMoney() const
{
    return money;
}

void Shop::SetMoney(PriceT val)
{
    money = val;
}

const Person *Shop::GetManager()
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

ErrorIDTaken::ErrorIDTaken(int id)
    : std::invalid_argument("ID was already taken"), id(id) {}

ErrorItemNotFound::ErrorItemNotFound(int id)
    : std::out_of_range("No item with given ID found"), id(id) {}
