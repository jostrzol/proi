#pragma once

#include <chrono>
#include <random>

#include "actions.h"
#include "shop/shop.h"

#ifndef NDEBUG
#define DEFAULT_TICK_DURATION 5
#else
#define DEFAULT_TICK_DURATION std::chrono::seconds(7)
#endif

class Simulation
{
public:
    struct Settings
    {
        std::chrono::milliseconds TickDuration{DEFAULT_TICK_DURATION};
        std::chrono::minutes VirtualTickDuration{std::chrono::minutes(15)};
        double CustomerGetItemMean{6};
        double CustomerGetItemSD{1};
        double GenerateCustomerScale{3};
        PriceT EndDayCustomerMinExtraMoney{500'00};
        PriceT EndDayCustomerMaxExtraMoney{1500'00};
        unsigned int EndDayMinItemRestock{20};
        unsigned int EndDayMaxItemRestock{50};
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
    Simulation(std::mt19937 &gen, Shop &shop);

    // Runs the simulation until enter is pressed
    void Run();
    // Runs the simulation for nTurns number of turns
    void Run(std::size_t nTurns);

    // Returns the shop bound to this simulation
    Shop &GetShop();

    // Returns the Settings object of this simulation
    Settings GetSettings();
    // Apply the Setting object for this simulation
    void SetSettings(Settings &val);

    // Set a log file for this simulation or nullptr if none
    void SetLogfile(std::ostream *file);
    // Returns the log file of this simulation
    std::ostream *GetLogfile();

    // Return simulation details
    std::string Details();

private:
    // Plays one turn
    void turn();
    // Performs actions on the end of the day
    void endDay();

    std::chrono::minutes virtualTime;
    // Increments the simulation's virtual time and returns true if it is time for the shop to close
    // The amount of time being added by this method can be set using the Settings object of this simulation
    bool incrementTime();
    // Returns the current turn label
    std::string turnLabel();

    Shop &shop;
    Settings settings;

    /* - - - - - Present customer actions  - - - - - */

    // Does nothing
    std::string actIdle(Customer &);
    // Makes the customer get a random item from the shop
    std::string actGetItem(Customer &cust);
    // Makes the customer leave a random item in the shop
    std::string actLeaveItem(Customer &cust);
    // Makes the customer join a random open queue
    std::string actJoinQueue(Customer &cust);
    // Makes the customer leave the shop
    std::string actLeaveShop(Customer &cust);
    // Makes the customer ask a random question
    std::string actAskRandomQuestion(Customer &cust);

    /* - - - - - Absent customer actions - - - - - - */

    // Makes the customer enter the shop or not, at random
    std::string actDecideEnterShop(Customer &cust);

    /* - - - - - Worker actions  - - - - - - - - - - */

    // Makes the worker choose a role and assigns it to him
    std::string actChooseRole(Worker &work);

    /* - - - - - Cash worker actions - - - - - - - - */

    // Makes the worker serve the next customer in the queue if not empty
    std::string actServeNext(Worker &work);

    CustomerActions customerActions{
        gen,
        {
            {&Simulation::actGetItem, 10},
            {&Simulation::actLeaveItem, 1},
            {&Simulation::actJoinQueue, 2},
            {&Simulation::actLeaveShop, 1},
            {&Simulation::actIdle, 3},
            {&Simulation::actAskRandomQuestion, 2},
        }};
    CustomerActions absentCustomerActions{gen, {{&Simulation::actDecideEnterShop, 1}}};
    WorkerActions workerActions{gen, {{&Simulation::actChooseRole, 1}}};
    WorkerActions cashWorkerActions{gen, {{&Simulation::actServeNext, 1}}};

    std::ostream *logfile = nullptr;
    // Print a message to the standard output and to the logfile
    void print(std::string msg);

    std::chrono::steady_clock clock;

    std::mt19937 gen;
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
