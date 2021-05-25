#include <sstream>
#include <random>
#include <unordered_set>
#include <array>
#include <thread>
#include <limits>
#include <iomanip>

#include "shop/utility.h"
#include "simulation.h"

#define BARWIDTH 40

Simulation::Simulation(std::mt19937 &gen, Shop &shop)
    : shop(shop), gen(gen) {}

void Simulation::Run(std::size_t nTurns)
{
    virtualTime = shop.GetOpenTime();

    auto end = clock.now() + settings.TickDuration;
    for (std::size_t i = 0; i < nTurns; i++)
    {
        turn();

        if (i < nTurns - 1)
            std::this_thread::sleep_until(end);
        end += settings.TickDuration;
    }
}

void Simulation::Run()
{
    virtualTime = shop.GetOpenTime();

    auto end = clock.now() + settings.TickDuration;
    bool stop = false;
    std::thread t1([&]()
                   {
                       std::string s;
                       std::getline(std::cin, s);

                       stop = true;
                   });

    int i = 0;
    while (!stop)
    {
        turn();

        while (clock.now() < end)
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 30));
        end += settings.TickDuration;

        i++;
    }

    t1.detach();
}

Shop &Simulation::GetShop()
{
    return shop;
}

Simulation::Settings Simulation::GetSettings()
{
    return settings;
}

void Simulation::SetSettings(Settings &val)
{
    settings = val;
}

void Simulation::SetLogfile(std::ostream *file)
{
    logfile = file;
}

std::ostream *Simulation::GetLogfile()
{
    return logfile;
}

std::string Simulation::actGetItem(Customer &cust)
{
    std::stringstream msg;
    msg << "Customer no. " << cust.GetID() << " ";

    auto &items = shop.GetItems();
    if (items.empty())
    {
        msg << "realized that the shop is empty and left.\n";
        cust.LeaveShop();
        return msg.str();
    }
    std::uniform_int_distribution<> distrib(0, items.size() - 1);
    auto it = items.begin();
    std::advance(it, distrib(gen));
    Item &item = it->second.first;

    std::normal_distribution<> distrib2(settings.CustomerGetItemMean, settings.CustomerGetItemSD);
    double want = distrib2(gen);

    want = want < 0 ? 0 : want;

    //if the item's unit is pcs. round the want amount
    if (item.GetUnit() == pcs)
        want = round(want);

    auto taken = cust.TakeProduct(item, want);

    if (taken != want)
    {
        msg << "wanted to take " << want << " " << item.GetUnit() << " of item no. " << item.GetID();
        msg << " (" << item.GetName() << ")";
        if (taken == 0)
            msg << ", but the shop did not have that item anymore.\n";
        else
            msg << ", but took only " << taken << " " << item.GetUnit() << " as there was no more of it.\n";
    }
    else
    {
        msg << "took " << want << " " << item.GetUnit() << " of item no. " << item.GetID();
        msg << " (" << item.GetName() << ").\n";
    }

    return msg.str();
}

std::string Simulation::actLeaveItem(Customer &cust)
{
    auto &products = cust.GetProducts();

    if (products.empty())
        return "";

    std::uniform_int_distribution<> distrib(0, products.size() - 1);
    auto it = products.begin();
    std::advance(it, distrib(gen));

    auto &product = *it->first;
    cust.LeaveProduct(product);

    std::stringstream msg;
    msg << "Customer no. " << cust.GetID() << " left item no. " << product.GetID();
    msg << " (" << product.GetName() << ").\n";
    return msg.str();
}

std::string Simulation::actJoinQueue(Customer &cust)
{
    std::stringstream msg;
    msg << "Customer no. " << cust.GetID() << " ";
    if (cust.GetProducts().empty())
    {
        msg << "wanted to join the queue, but was let through the queue "
            << "as he had nothing to buy.\n";
        Simulation::actLeaveShop(cust);
        return msg.str();
    }
    auto &openCRMap = shop.GetOpenCashRegisters();
    if (openCRMap.empty())
    {
        msg << "wanted to join the queue, but there were none available.\n";
        return msg.str();
    }

    std::vector<CashRegister *> openCRs;
    std::transform(openCRMap.begin(), openCRMap.end(), std::back_inserter(openCRs),
                   [](std::pair<int, CashRegister *> pair)
                   { return pair.second; });

    std::vector<int> queueWeights;
    std::transform(openCRs.begin(), openCRs.end(), std::back_inserter(queueWeights),
                   [](CashRegister *cr)
                   { return cr->QueueEmpty() ? std::numeric_limits<double>::infinity() : 1 / cr->QueueSize(); });

    std::discrete_distribution<> distrib(queueWeights.begin(), queueWeights.end());
    auto &cr = *openCRs[distrib(gen)];

    cust.JoinQueue(cr);
    msg << "stepped into queue to cash register no. " << cr.GetID() << ".\n";
    return msg.str();
}

std::string Simulation::actLeaveShop(Customer &cust)
{
    // have to use ordinary for loop because of deleting
    std::stringstream msg;
    msg << "Customer no. " << cust.GetID() << " left the shop.\n";
    cust.LeaveShop();
    return msg.str();
}

std::string Simulation::actIdle(Customer &)
{
    return "";
}

std::string Simulation::actDecideEnterShop(Customer &cust)
{
    std::stringstream ss;
    std::discrete_distribution<> dist({1, settings.GenerateCustomerScale / shop.GetCustomers().size()});

    if (dist(gen))
    {
        cust.EnterShop();
        ss << "Customer no. " << cust.GetID() << " entered the shop.\n";
    }

    return ss.str();
}

std::string Simulation::actChooseRole(Worker &work)
{
    auto currentCr = work.GetCashRegister();
    if (currentCr != nullptr && !currentCr->QueueEmpty())
        return ""; // Worker is serving at the cash register at the momment

    auto &openCRMap = shop.GetOpenCashRegisters();
    std::size_t cap = settings.OpenNewCashRegisterQueueCap;
    auto crIt = shop.GetCloseCashRegisters().begin();
    CashRegister *cr = crIt == shop.GetCloseCashRegisters().end() ? nullptr : crIt->second;

    std::stringstream msg;
    msg << "Worker no. " << work.GetID() << " ";

    if (openCRMap.empty())
    {
        // No open cash registers, need at least one
        if (cr == nullptr)
        {
            msg << "tried to open the first cash register, but there were none in the shop!\n";
            return msg.str();
        }
        shop.AssignWorkerToCashRegister(work, *cr);
        msg << "opened the first cash register no. " << cr->GetID() << ".\n";
        return msg.str();
    }
    else if (shop.GetHelperWorkers().empty())
    {
        shop.AssignWorkerToHelping(work);
        msg << "is ready to help customers as the first helper worker.\n";
        return msg.str();
    }
    else if (std::any_of(openCRMap.begin(), openCRMap.end(),
                         [&cap](std::pair<int, CashRegister *> pair)
                         { return pair.second->QueueSize() > cap; }) &&
             cr != nullptr)
    {
        shop.AssignWorkerToCashRegister(work, *cr);
        msg << "opened cash register no. " << cr->GetID() << ", as one of the queues was getting too big.\n";
        return msg.str();
    }
    else
    {
        if (shop.WorkerIsAssigned(work.GetID()))
            return "";
        shop.AssignWorkerToHelping(work);
        msg << "is ready to help customers as a helper worker.\n";
        return msg.str();
    }
}

std::string Simulation::actServeNext(Worker &work)
{
    CashRegister *cr = work.GetCashRegister();
    if (cr->QueueEmpty())
        return "";
    IBuyer &buyer = *cr->QueuePop();

    std::stringstream msg;
    msg << "Worker no. " << work.GetID() << " ";

    switch (buyer.GetPCType())
    {
    case PCReceipt:
    {
        Receipt r(buyer.GetProducts(), cr->GetReceipts().size(), cr);
        if (buyer.Pay(r.TotalPriceBrutto()))
        {
            msg << "successfully served customer no. " << buyer.GetID() << ", generating a receipt:\n"
                << r;
            cr->AddReceipt(std::move(r));
            cr->DepositMoney(r.TotalPriceBrutto());
            Customer *cust = dynamic_cast<Customer *>(&buyer);
            if (cust)
            {
                cust->ClearProducts();
                cust->LeaveShop();
            }
        }
        else
            msg << "tried to serve customer no. " << buyer.GetID() << ", but the buyer couldn't pay.\n";
        break;
    }
    case PCInvoice:
    {
        Invoice i(buyer.GetProducts(), cr->GetInvoices().size(), &cr->GetShop(), &buyer, cr);
        if (buyer.Pay(i.TotalPriceBrutto()))
        {
            msg << "successfully served customer no. " << buyer.GetID() << ", generating an invoice:\n"
                << i;
            cr->AddInvoice(std::move(i));
            cr->DepositMoney(i.TotalPriceBrutto());
            Customer *cust = dynamic_cast<Customer *>(&buyer);
            if (cust)
            {
                cust->ClearProducts();
                cust->LeaveShop();
            }
        }
        else
            msg << "tried to serve customer no. " << buyer.GetID() << ", but the buyer couldn't pay.\n";
        break;
    }
    default:
        msg << "tried to serve customer no. " << buyer.GetID() << ", but the buyer demanded unhandled purchase confirmation document.\n";
        break;
    }
    return msg.str();
}

void Simulation::print(std::string msg)
{
    std::cout << msg;
    if (logfile)
        *logfile << msg;
}

void Simulation::turn()
{
    bool shouldClose = false;
    if (shop.IsOpen())
    {
        shouldClose = incrementTime();
    }
    else
    {
        virtualTime = shop.GetOpenTime();
        shop.Open();
        print("\n" + std::string(BARWIDTH, '=') + "\n");
        print("Shop just opened!\n");
        print(std::string(BARWIDTH, '=') + "\n");
    }

    print(turnLabel());

    if (shouldClose)
    {
        shop.Close();
        print(std::string(BARWIDTH, '=') + "\n");
        print("Shop is closing for today.\n");
        print(std::string(BARWIDTH, '=') + "\n\n");
        endDay();
        return;
    }

    for (auto &pair : shop.GetWorkers())
    {
        auto &worker = pair.second;
        auto action = workerActions.Choose();
        auto msg = (this->*action)(worker);
        print(msg);
    }

    for (auto &pair : shop.GetCustomers())
    {
        auto &customer = pair.second;

        // if in queue cannot perform actions
        if (customer.GetCashRegister())
            continue;

        auto action = customer.IsInShop() ? customerActions.Choose() : absentCustomerActions.Choose();
        auto msg = (this->*action)(customer);

        print(msg);
    }

    for (auto &pair : shop.GetCashWorkers())
    {
        auto &worker = pair.second;
        auto action = cashWorkerActions.Choose();
        auto msg = (this->*action)(*worker);
        print(msg);
    }

    print("\n");
}

void Simulation::endDay()
{
    // Add extra money for customers
    for (auto &pair : shop.GetCustomers())
    {
        auto &cust = pair.second;
        std::uniform_int_distribution<> dist(
            settings.EndDayCustomerMinExtraMoney.Value(),
            settings.EndDayCustomerMaxExtraMoney.Value());
        PriceT extra = dist(gen);
        cust.SetMoney(cust.GetMoney() + extra);

        std::stringstream msg;
        msg << "Customer no. " << cust.GetID() << " got extra " << extra << ".\n";
        print(msg.str());
    }

    // Restock
    for (auto &pair : shop.GetItems())
    {
        std::uniform_int_distribution dist(
            settings.EndDayMinItemRestock,
            settings.EndDayMaxItemRestock);
        const auto &item = pair.second.first;
        auto &amount = pair.second.second;
        int extra = dist(gen);
        amount += extra;

        std::stringstream msg;
        msg << "Extra " << extra << " " << item.GetUnit() << " of item no. " << item.GetID() << " was delivered to the shop.\n";
        print(msg.str());
    }
}

bool Simulation::incrementTime()
{
    virtualTime += settings.VirtualTickDuration;
    virtualTime = std::min<std::chrono::minutes>(std::chrono::hours(24), virtualTime);
    return virtualTime >= shop.GetCloseTime();
}

std::string Simulation::turnLabel()
{
    std::string bar(BARWIDTH, '#');
    std::stringstream ss;
    ss << bar << "\n";

    ss << "TIME:\t" << MinutesToDaytime(virtualTime) << "\n";

    ss << bar << "\n";
    return ss.str();
}
