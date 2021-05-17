#include <sstream>

#include "shop.h"

std::size_t Shop::ItemHash::operator()(const Item &item) const
{
    return std::hash<Entity>()(item);
}

Shop::Shop(int id, std::string name, std::string address, std::string phone)
    : Entity(id), manager(nullptr), name(name), address(address), phone(phone) {}

Shop::ItemMap &Shop::GetItems() { return items; }

Item &Shop::AddItem(int id, std::string name, PriceT pricePerUnit, UnitT unit, double unitTax, std::string category, double amount)
{
    std::pair<Item, double> pair = {{id, name, pricePerUnit, unit, unitTax}, 0};
    auto emplaced = items.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(id),
        std::forward_as_tuple(
            std::piecewise_construct,
            std::forward_as_tuple(id, name, pricePerUnit, unit, unitTax, category),
            std::forward_as_tuple(amount)));
    if (!emplaced.second)
        throw ErrorIDTaken(id);
    auto &item = emplaced.first->second.first;
    itemsCategory[category].push_back(&item);
    return item;
}

std::pair<Item *, double> Shop::GetItem(int id)
{
    auto it = items.find(id);
    if (it == items.end())
        throw ErrorItemNotFound(id);
    auto &pair = it->second;
    return std::make_pair(&pair.first, pair.second);
}

std::vector<Item *> &Shop::GetItemsCategory(std::string category)
{
    return itemsCategory[category];
}

void Shop::SetItemAmount(int id, double amount)
{
    auto it = items.find(id);
    if (it == items.end())
        throw ErrorItemNotFound(id);
    auto &pair = it->second;
    pair.second = amount;
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

bool Shop::WorkerIsAssigned(int id)
{
    if (cashWorkers.find(id) != cashWorkers.end())
        return true;
    if (helperWorkers.find(id) != helperWorkers.end())
        return true;
    return false;
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
    auto &cr = emplaced.first->second;
    closeCashRegisters[id] = &cr;
    return cr;
}

void Shop::RemoveCashRegister(int id)
{
    cashRegisters.erase(id);
    closeCashRegisters.erase(id);
    openCashRegisters.erase(id);
}

Shop::CashRegisterStatusMap &Shop::GetOpenCashRegisters()
{
    return openCashRegisters;
}

Shop::CashRegisterStatusMap &Shop::GetCloseCashRegisters()
{
    return closeCashRegisters;
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
    openCashRegisters[cr.GetID()] = &cr;
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
    auto cr = worker.FreeCashRegister();
    if (cr != nullptr)
    {
        openCashRegisters.erase(cr->GetID());
        closeCashRegisters[cr->GetID()] = cr;
    }
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

Person *Shop::GetManager()
{
    return manager;
}

void Shop::SetManager(Person *manager_)
{
    manager = manager_;
}

std::chrono::minutes Shop::GetOpenTime() const
{
    return openTime;
}

void Shop::SetOpenTime(std::chrono::minutes val)
{
    if (val > closeTime || val > std::chrono::hours(24))
        return;
    openTime = val;
}

std::chrono::minutes Shop::GetCloseTime() const
{
    return closeTime;
}

void Shop::SetCloseTime(std::chrono::minutes val)
{
    if (val < openTime || val > std::chrono::hours(24))
        return;
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
