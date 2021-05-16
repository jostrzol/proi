#include <sstream>
#include <random>
#include <unordered_set>
#include <array>
#include <thread>
#include <limits>

#include "simulation.h"

Simulation::Simulation(std::size_t nCustomers,
                       std::size_t nCashRegisters,
                       std::size_t nWorkers)
    : shop(0, "Shop", "unknown", "unknown")
{
    for (std::size_t i = 0; i < nCustomers; i++)
    {
        std::stringstream ss;
        ss << "Customer " << i;
        shop.AddCustomer(i, ss.str(), "unknown", "unknown");
    }
    for (std::size_t i = 0; i < nCashRegisters; i++)
    {
        shop.AddCashRegister(i);
    }
    for (std::size_t i = 0; i < nWorkers; i++)
    {
        std::stringstream ss;
        ss << "Worker " << i;
        shop.AddWorker(i, ss.str(), "unknown", "unknown");
    }
}

void Simulation::Run(std::size_t nTurns)
{
    auto end = clock.now() + settings.TickDuration;

    for (std::size_t i = 0; i < nTurns; i++)
    {
        std::cout << "########## TURN " << i << " ##########\n";
        turn();
        std::this_thread::sleep_until(end);
        end += settings.TickDuration;
    }
}

void Simulation::ReadNames(std::istream &file)
{
    std::string line;
    std::vector<std::string> names;
    while (!file.eof())
    {
        std::getline(file, line);
        names.push_back(line);
    }
    std::shuffle(names.begin(), names.end(), gen);
    auto it = names.begin();
    for (auto &customer : shop.GetCustomers())
    {
        customer.second.SetName(*it++);
        if (it == names.end())
            return;
    }
    for (auto &worker : shop.GetWorkers())
    {
        worker.second.SetName(*it++);
        if (it == names.end())
            return;
    }
    auto manager = shop.GetManager();
    if (manager != nullptr)
        manager->SetName(*it++);
}

void Simulation::ReadAddresses(std::istream &file)
{
    std::string line;
    std::vector<std::string> addresses;
    while (!file.eof())
    {
        std::getline(file, line);
        addresses.push_back(line);
    }
    std::shuffle(addresses.begin(), addresses.end(), gen);
    auto it = addresses.begin();
    if (it != addresses.end())
        shop.SetAddress(*it++);
    for (auto &customer : shop.GetCustomers())
    {
        customer.second.SetAddress(*it++);
        if (it == addresses.end())
            return;
    }
    for (auto &worker : shop.GetWorkers())
    {
        worker.second.SetAddress(*it++);
        if (it == addresses.end())
            return;
    }
    auto manager = shop.GetManager();
    if (manager != nullptr)
        manager->SetAddress(*it++);
}

void Simulation::RandomizePhones()
{
    std::size_t len = shop.GetCustomers().size() + shop.GetWorkers().size() + 2;

    std::unordered_set<std::string> phones;
    std::uniform_int_distribution<> distrib(100'000'000, 999'999'999);

    while (phones.size() < len)
    {
        phones.insert(std::to_string(distrib(gen)));
    }

    auto it = phones.begin();
    shop.SetPhone(*it++);
    for (auto &customer : shop.GetCustomers())
    {
        customer.second.SetPhone(*it++);
    }
    for (auto &worker : shop.GetWorkers())
    {
        worker.second.SetPhone(*it++);
    }
    auto manager = shop.GetManager();
    if (manager != nullptr)
        manager->SetPhone(*it++);
}

void Simulation::ReadItems(std::istream &file)
{
    // check header
    std::array correctFields{
        "ItemID", "ItemName", "ItemCategory", "ItemUnit",
        "ItemUnitPrice", "ItemUnitTax", "ItemAmount"};
    std::string header;
    std::getline(file, header);

    std::stringstream headerStream{header + ","};
    auto it = correctFields.begin();
    for (std::string field; std::getline(headerStream, field, ',');)
    {
        if (*it++ != field)
            throw ErrorInvalidCSVHeader(header);
    }

    for (std::string line; std::getline(file, line);)
    {
        std::stringstream lineStream{line};
        int id;
        std::string name;
        std::string category;
        UnitT unit;
        PriceT unitPrice;
        double unitTax;
        double itemAmount;

        if (!ReadCSVLine(lineStream, id, name, category, unit, unitPrice, unitTax, itemAmount))
            throw ErrorMalformedCSVLine(line);
        shop.AddItem(id, name, unitPrice, unit, unitTax, category, itemAmount);
    }
}

Simulation::CustomerActions &Simulation::GetCustomerActions()
{
    return customerActions;
}

Simulation::WorkerActions &Simulation::GetWorkerActions()
{
    return workerActions;
}

Simulation::WorkerActions &Simulation::GetCashWorkerActions()
{
    return cashWorkerActions;
}

Shop &Simulation::GetShop()
{
    return shop;
}

Simulation::Settings &Simulation::GetSettings()
{
    return settings;
}

void Simulation::SetSettings(Settings &val)
{
    settings = val;
}

std::string Simulation::actGetItem(Customer &cust)
{
    auto &items = shop.GetItems();
    std::uniform_int_distribution<> distrib(0, items.size() - 1);
    auto it = items.begin();
    std::advance(it, distrib(gen));
    Item &item = it->second.first;

    std::exponential_distribution<> distrib2(settings.CustomerGetItemExpCoefficient);
    double want = distrib2(gen) * settings.CustomerGetItemScale + settings.CustomerGetItemOffset;

    //if the item's unit is pcs. round the want amount
    if (item.GetUnit() == pcs)
        want = round(want);

    auto taken = cust.TakeProduct(item, want);

    std::stringstream msg;
    msg << "Customer no. " << cust.GetID() << " ";

    if (taken != want)
        msg << "wanted to take " << want << " " << item.GetUnit() << " of item no. " << item.GetID()
            << " but took only " << taken << " " << item.GetUnit() << " as there was no more of it.\n";
    else
        msg << "took " << want << " " << item.GetUnit() << " of item no. " << item.GetID() << "\n";

    return msg.str();
}

std::string Simulation::actJoinQueue(Customer &cust)
{
    std::stringstream msg;
    msg << "Customer no. " << cust.GetID() << " ";
    if (cust.GetProducts().empty())
    {
        msg << "wanted to join the queue, but was let through the queue "
            << "as he had nothing to buy\n";
        Simulation::actLeaveShop(cust);
        return msg.str();
    }
    auto &openCRMap = shop.GetOpenCashRegisters();
    if (openCRMap.empty())
    {
        msg << "wanted to join the queue, but there were none available\n";
        return msg.str();
    }

    std::vector<CashRegister *> openCRs;
    std::transform(openCRMap.begin(), openCRMap.end(), std::back_inserter(openCRs),
                   [](std::pair<int, CashRegister *> pair)
                   { return pair.second; });

    std::vector<int> queueWeights;
    std::transform(openCRs.begin(), openCRs.end(), std::back_inserter(queueWeights),
                   [](CashRegister *cr)
                   { return cr->QueueEmpty() ? std::numeric_limits<int>::max() : 1000 / cr->QueueSize(); });

    std::discrete_distribution<> distrib(queueWeights.begin(), queueWeights.end());
    auto &cr = *openCRs[distrib(gen)];

    cr.QueuePush(cust);
    msg << "stepped into queue to cash register no. " << cr.GetID() << "\n";
    return msg.str();
}

std::string Simulation::actLeaveShop(Customer &cust)
{
    // have to use ordinary for loop because of deleting
    for (auto it = cust.GetProducts().begin(); it != cust.GetProducts().end();)
    {
        auto &pair = *it++;
        cust.LeaveProduct(*pair.first);
    }
    std::stringstream msg;
    msg << "Customer no. " << cust.GetID() << " left the shop\n";
    cust.GetShop().RemoveCustomer(cust.GetID());
    return msg.str();
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
        msg << "opened the first cash register no. " << cr->GetID() << "\n";
        return msg.str();
    }
    else if (shop.GetHelperWorkers().empty())
    {
        shop.AssignWorkerToHelping(work);
        msg << "is ready to help customers as the first helper worker\n";
        return msg.str();
    }
    else if (std::any_of(openCRMap.begin(), openCRMap.end(),
                         [&cap](std::pair<int, CashRegister *> pair)
                         { return pair.second->QueueSize() > cap; }) &&
             cr != nullptr)
    {
        shop.AssignWorkerToCashRegister(work, *cr);
        msg << "opened cash register no. " << cr->GetID() << ", as one of the queues was getting too big\n";
        return msg.str();
    }
    else
    {
        if (shop.WorkerIsAssigned(work.GetID()))
            return "";
        shop.AssignWorkerToHelping(work);
        msg << "is ready to help customers as a helper worker\n";
        return msg.str();
    }
}

std::string Simulation::actServeNext(Worker &work)
{
    CashRegister *cr = work.GetCashRegister();
    if (cr->QueueEmpty())
        return "";
    IBuyer &buyer = cr->QueuePop();

    std::stringstream msg;
    msg << "Worker no. " << work.GetID() << " ";

    switch (buyer.GetPCType())
    {
    case PCReceipt:
    {
        Receipt r(buyer.GetProducts(), cr->GetReceipts().size(), cr);
        if (buyer.Pay(r.TotalPriceBrutto()))
        {
            msg << "successfully served customer no. " << buyer.GetID() << " generating receipt:\n"
                << r;
            cr->AddReceipt(std::move(r));
        }
        else
            msg << "tried to serve customer no. " << buyer.GetID() << ", but the buyer couldn't pay\n";
        break;
    }
    case PCInvoice:
    {
        Invoice i(buyer.GetProducts(), cr->GetInvoices().size(), &cr->GetShop(), &buyer, cr);
        if (buyer.Pay(i.TotalPriceBrutto()))
        {
            msg << "successfully served customer no. " << buyer.GetID() << " generating invoice:\n"
                << i;
            cr->AddInvoice(std::move(i));
        }
        else
            msg << "tried to serve customer no. " << buyer.GetID() << ", but the buyer couldn't pay\n";
        break;
    }
    default:
        msg << "tried to serve customer no. " << buyer.GetID() << ", but the buyer demanded unhandled purchase confirmation document\n";
        break;
    }
    return msg.str();
}

void Simulation::turn()
{
    for (auto &pair : shop.GetWorkers())
    {
        auto &worker = pair.second;
        auto action = workerActions.Choose();
        auto msg = (this->*action)(worker);
        std::cout << msg;
    }
    // customers might leave the shop, so have to use ordinary for loop
    for (auto it = shop.GetCustomers().begin(); it != shop.GetCustomers().end();)
    {
        auto &pair = *it++;
        auto &customer = pair.second;
        auto action = customerActions.Choose();
        auto msg = (this->*action)(customer);
        std::cout << msg;
    }
    for (auto &pair : shop.GetCashWorkers())
    {
        auto &worker = pair.second;
        auto action = cashWorkerActions.Choose();
        auto msg = (this->*action)(*worker);
        std::cout << msg;
    }
}

ErrorInvalidCSVHeader::ErrorInvalidCSVHeader(std::string header)
    : ErrorCSV("Invalid CSV header"), header(header) {}

ErrorMalformedCSVLine::ErrorMalformedCSVLine(std::string line)
    : ErrorCSV("Malformed CSV line"), line(line) {}