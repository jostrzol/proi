#pragma once

#include <chrono>
#include <random>
#include <unordered_set>

#include "shop/shop.h"

static std::random_device rd;
static std::mt19937 gen;

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
    Simulation(Shop & shop);

    // runs until enter is pressed
    void Run();
    // runs for nTurns turns
    void Run(std::size_t nTurns);

    Shop &GetShop();

    Settings GetSettings();
    void SetSettings(Settings &val);

    void SetLogfile(std::ostream *file);
    std::ostream *GetLogfile();

private:
    void turn();

    Shop shop;
    Settings settings;

    // present customer actions
    std::string actIdle(Customer &);
    std::string actGetItem(Customer &cust);
    std::string actJoinQueue(Customer &cust);
    std::string actLeaveShop(Customer &cust);

    // absent customer actions
    std::string actDecideEnterShop(Customer &cust);

    // worker actions
    std::string actChooseRole(Worker &work);

    // cash worker actions
    std::string actServeNext(Worker &work);

    CustomerActions customerActions{
        {&Simulation::actGetItem, 10},
        {&Simulation::actJoinQueue, 2},
        {&Simulation::actLeaveShop, 1},
        {&Simulation::actIdle, 4},
    };
    CustomerActions absentCustomerActions{{&Simulation::actDecideEnterShop, 1}};
    WorkerActions workerActions{{&Simulation::actChooseRole, 1}};
    WorkerActions cashWorkerActions{{&Simulation::actServeNext, 1}};
    // WorkerActions helperWorkerActions;

    std::ostream *logfile = nullptr;
    void print(std::string msg);

    std::chrono::steady_clock clock;
};

#pragma region Actions

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
