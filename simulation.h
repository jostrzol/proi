#pragma once

#include <chrono>
#include <random>
#include "shop/shop.h"

static std::random_device rd;
static std::mt19937 gen(rd());

template <class ActionFunc, class KeyHasher = std::hash<ActionFunc>, class KeyEqualTo = std::equal_to<ActionFunc>>
class Actions
{
public:
    Actions();
    Actions(std::initializer_list<std::pair<ActionFunc, std::size_t>> actions_);

    void SetActionWeight(const ActionFunc &action, std::size_t weight);
    void RemoveAction(const ActionFunc &action);

    ActionFunc Choose();

private:
    std::unordered_map<ActionFunc, std::size_t, KeyHasher, KeyEqualTo> actions;
};

class Simulation
{
public:
    struct Settings
    {
        std::chrono::milliseconds TickDuration{std::chrono::seconds(5)};
        int CustomerGetItemExpCoefficient{1};
        int CustomerGetItemScale{5};
        int CustomerGetItemOffset{1};
        std::size_t OpenNewCashRegisterQueueCap{5};
    };

private:
    typedef std::string (Simulation::*CustomerActionFunc)(Customer &);
    typedef std::string (Simulation::*WorkerActionFunc)(Worker &);
    template <class Action>
    struct ActHash
    {
        std::size_t operator()(const Action &act) const;
    };
    template <class Action>
    struct ActEqualTo
    {
        bool operator()(const Action &first, const Action &second) const;
    };
    typedef Actions<CustomerActionFunc, ActHash<CustomerActionFunc>, ActEqualTo<CustomerActionFunc>> CustomerActions;
    typedef Actions<WorkerActionFunc, ActHash<WorkerActionFunc>, ActEqualTo<WorkerActionFunc>> WorkerActions;

public:
    Simulation(std::size_t nCustomers,
               std::size_t nCashRegisters,
               std::size_t nWorkers);

    void Run(std::size_t nTurns);

    // Reads names from a file and assigns them to people in the shop in order:
    // Customers -> Workers -> Manager
    // Ends on end of new names
    void ReadNames(std::istream &file);
    // Reads addresses from a file and assigns them to people in the shop in order:
    // Shop -> Customers -> Workers -> Manager
    // Ends on end of new addresses
    void ReadAddresses(std::istream &file);
    // Generates random phone numbers and assigns them to people in the shop
    void RandomizePhones();
    // Read items from the .csv file in format:
    // ItemID,ItemName,ItemCategory,ItemUnit,ItemUnitPrice,ItemUnitTax,ItemAmount
    void ReadItems(std::istream &file);

    CustomerActions &GetCustomerActions();
    WorkerActions &GetWorkerActions();
    WorkerActions &GetCashWorkerActions();
    // Actions<IHelperWorker> &GetHelperWorkerActions();

    Shop &GetShop();

    Settings &GetSettings();
    void SetSettings(Settings &val);

private:
    Shop shop;
    Settings settings;

    std::string actGetItem(Customer &cust);
    std::string actJoinQueue(Customer &cust);
    std::string actLeaveShop(Customer &cust);
    std::string act(Customer &cust);

    std::string actChooseRole(Worker &work);

    std::string actServeNext(Worker &work);

    CustomerActions customerActions{
        {&Simulation::actGetItem, 10},
        {&Simulation::actJoinQueue, 2},
        {&Simulation::actLeaveShop, 1},
    };
    WorkerActions workerActions{{&Simulation::actChooseRole, 1}};
    WorkerActions cashWorkerActions{{&Simulation::actServeNext, 1}};
    // Actions<IHelperWorker> helperWorkerActions;

    void turn();

    std::chrono::steady_clock clock;
};

template <class Action>
std::size_t Simulation::ActHash<Action>::operator()(const Action &act) const
{
    return std::hash<void *>()((void *)(act));
}

template <class Action>
bool Simulation::ActEqualTo<Action>::operator()(const Action &first, const Action &second) const
{
    return std::equal_to<void *>()((void *)(first), (void *)(second));
}

#pragma region Actions

template <class ActionFunc, class KeyHasher, class KeyEqualTo>
Actions<ActionFunc, KeyHasher, KeyEqualTo>::Actions()
{
}

template <class ActionFunc, class KeyHasher, class KeyEqualTo>
Actions<ActionFunc, KeyHasher, KeyEqualTo>::Actions(std::initializer_list<std::pair<ActionFunc, std::size_t>> actions_)
{
    for (auto pair : actions_)
    {
        actions[pair.first] = pair.second;
    }
}

template <class ActionFunc, class KeyHasher, class KeyEqualTo>
void Actions<ActionFunc, KeyHasher, KeyEqualTo>::SetActionWeight(const ActionFunc &action, std::size_t weight)
{
    actions[action] = weight;
}

template <class ActionFunc, class KeyHasher, class KeyEqualTo>
void Actions<ActionFunc, KeyHasher, KeyEqualTo>::RemoveAction(const ActionFunc &action)
{
    actions.erase(action);
}

template <class ActionFunc, class KeyHasher, class KeyEqualTo>
ActionFunc Actions<ActionFunc, KeyHasher, KeyEqualTo>::Choose()
{
    std::vector<std::size_t> weights(actions.size());
    std::vector<ActionFunc> actionVector(actions.size());

    static auto GetAction = [](std::pair<ActionFunc, std::size_t> pair)
    { return pair.first; };
    static auto GetWeight = [](std::pair<ActionFunc, std::size_t> pair)
    { return pair.second; };
    std::transform(actions.begin(), actions.end(), std::back_inserter(actionVector), GetAction);
    std::transform(actions.begin(), actions.end(), std::back_inserter(weights), GetWeight);

    std::discrete_distribution<std::size_t> d(weights.begin(), weights.end());
    return actionVector[d(gen)];
}

#pragma endregion Actions

#pragma region CSV

template <class T>
bool ReadCSVLine(std::istream &is, T &arg)
{
    if (!(is >> arg))
        return false;
    return true;
}

template <class T, class... ArgsT>
bool ReadCSVLine(std::istream &is, T &arg, ArgsT &...args)
{
    std::string field;
    if (std::getline(is, field, ','))
    {
        std::stringstream ss(field);
        if (!(ss >> arg))
            return false;
        return ReadCSVLine(is, args...);
    }
    is >> arg;
    return false;
}

struct ErrorCSV : public std::logic_error
{
    using std::logic_error::logic_error;
};

struct ErrorInvalidCSVHeader : ErrorCSV
{
    ErrorInvalidCSVHeader(std::string header);
    std::string header;
};

struct ErrorMalformedCSVLine : ErrorCSV
{
    ErrorMalformedCSVLine(std::string line);
    std::string line;
};

#pragma endregion CSV