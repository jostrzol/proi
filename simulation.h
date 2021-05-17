#pragma once

#include <chrono>
#include <random>
#include <unordered_set>
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
        std::chrono::milliseconds VirtualTickDuration{std::chrono::minutes(15)};
        int CustomerMoneyMax{5000'00};
        int CustomerMoneyMin{500'00};
        double CustomerGetItemMean{6};
        double CustomerGetItemSD{1};
        double GenerateCustomerScale{3};
        std::size_t OpenNewCashRegisterQueueCap{5};
    };

private:
    typedef std::string (Simulation::*CustomerActionFunc)(Customer &);
    typedef std::string (Simulation::*WorkerActionFunc)(Worker &);
    typedef std::string (Simulation::*ShopActionFunc)(Shop &);
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
    typedef Actions<ShopActionFunc, ActHash<ShopActionFunc>, ActEqualTo<ShopActionFunc>> ShopActions;

public:
    Simulation();

    // runs until enter is pressed
    void Run();
    // runs for nTurns turns
    void Run(std::size_t nTurns);

    // Reads names from a file to use them to generate people
    void ReadNames(std::istream &file);
    // Reads addresses from a file to use them to generate people
    void ReadAddresses(std::istream &file);

    // Adds n cash registers
    std::vector<CashRegister *> AddCashRegisters(int n);
    // Adds n randomly generated workers
    std::vector<Worker *> AddWorkers(int n);
    // Adds n randomly generated customers
    std::vector<Customer *> AddCustomers(int n);
    // Returns randomly generated person
    Person GeneratePerson();
    // Makes person's data possible to generate again
    void RecyclePerson(const Person &person);
    // Assigns randomly generated info to shop
    void GenerateShopInfo();

    // Read items from the .csv file in format:
    // ItemID,ItemName,ItemCategory,ItemUnit,ItemUnitPrice,ItemUnitTax,ItemAmount
    void ReadItems(std::istream &file);

    CustomerActions &GetCustomerActions();
    WorkerActions &GetWorkerActions();
    WorkerActions &GetCashWorkerActions();
    // Actions<IHelperWorker> &GetHelperWorkerActions();
    ShopActions &GetShopActions();

    Shop &GetShop();

    Settings GetSettings();
    void SetSettings(Settings &val);

    void SetLogfile(std::ostream *file);
    std::ostream *GetLogfile();

    std::string namePlaceholder = "unknown";
    std::string addressPlaceholder = "unknown";

private:
    void turn();

    Shop shop;
    Settings settings;

    std::string actIdle(Customer &);
    std::string actGetItem(Customer &cust);
    std::string actJoinQueue(Customer &cust);
    std::string actLeaveShop(Customer &cust);
    std::string actChooseRole(Worker &work);

    std::string actServeNext(Worker &work);

    std::string actGenerateCustomers(Shop &shop);

    CustomerActions customerActions{
        {&Simulation::actGetItem, 10},
        {&Simulation::actJoinQueue, 2},
        {&Simulation::actLeaveShop, 1},
        {&Simulation::actIdle, 4},
    };
    WorkerActions workerActions{{&Simulation::actChooseRole, 1}};
    WorkerActions cashWorkerActions{{&Simulation::actServeNext, 1}};
    // WorkerActions helperWorkerActions;
    ShopActions shopActions{{&Simulation::actGenerateCustomers, 1}};

    std::unordered_set<std::string> names;
    std::unordered_set<std::string> addresses;
    std::unordered_set<int> phonesTaken;

    // Generates random name which isn't already taken, or namePlaceholder if no new names are available
    std::string randomName();
    // Generates random address which isn't already taken, or addressPlaceholder if no new addresses are available
    std::string randomAddress();
    // Generates random phone number which isn't already taken
    std::string randomPhone();
    // Generates random amount of money for a new customer
    PriceT randomMoney();

    std::ostream *logfile = nullptr;

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

// find the first non-negative, continuous range of int-keyed map keys that is free
template <class Map>
int FindFreeIDs(Map &map, std::size_t size)
{
    int i = 0;
    while (true)
    {
        bool free = true;
        int j = i + size - 1;
        for (; j >= i; j--)
        {
            if (map.find(j) != map.end())
            {
                free = false;
                break;
            }
        }
        if (!free)
        {
            i = j + 1;
        }
        else
        {
            return i;
        }
    }
};