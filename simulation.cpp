#include <sstream>
#include <random>
#include <unordered_set>
#include <array>
#include <thread>
#include <limits>

#include "simulation.h"

Simulation::Simulation()
    : shop(0, "Shop", "unknown", "unknown") {}

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
    while (!file.eof())
    {
        std::string line;
        std::getline(file, line);
        names.insert(line);
    }
}

void Simulation::ReadAddresses(std::istream &file)
{
    while (!file.eof())
    {
        std::string line;
        std::getline(file, line);
        addresses.insert(line);
    }
}

std::vector<CashRegister *> Simulation::AddCashRegisters(int n)
{
    std::vector<CashRegister *> crs;
    if (n <= 0)
        return crs;
    int firstID = FindFreeIDs(shop.GetCashRegisters(), n);
    for (int i = 0; i < n; i++)
    {
        int id = firstID + i;
        crs.push_back(&shop.AddCashRegister(id));
    }
    return crs;
}

std::vector<Worker *> Simulation::AddWorkers(int n)
{
    std::vector<Worker *> workers;
    if (n <= 0)
        return workers;
    int firstID = FindFreeIDs(shop.GetWorkers(), n);
    for (int i = 0; i < n; i++)
    {
        int id = firstID + i;
        workers.push_back(
            &shop.AddWorker(id, randomName(), randomAddress(), randomPhone()));
    }
    return workers;
}

std::vector<Customer *> Simulation::AddCustomers(int n)
{
    std::vector<Customer *> customers;
    if (n <= 0)
        return customers;
    int firstID = FindFreeIDs(shop.GetCustomers(), n);
    for (int i = 0; i < n; i++)
    {
        int id = firstID + i;
        auto &cust = shop.AddCustomer(id, randomName(), randomAddress(), randomPhone(), randomMoney());
        customers.push_back(&cust);

        std::discrete_distribution<> dist({1, 1});
        cust.SetPCType(static_cast<PurchaseConfirmationType>(dist(gen)));
    }
    return customers;
}

Person Simulation::GeneratePerson()
{
    return std::move(Person(-1, randomName(), randomAddress(), randomPhone()));
}

void Simulation::RecyclePerson(const Person &person)
{
    if (person.GetName() != namePlaceholder)
        names.insert(person.GetName());
    if (person.GetAddress() != addressPlaceholder)
        addresses.insert(person.GetAddress());
}

void Simulation::GenerateShopInfo()
{
    shop.SetPhone(randomPhone());
    shop.SetAddress(randomAddress());
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

Simulation::ShopActions &Simulation::GetShopActions()
{

    return shopActions;
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

    std::normal_distribution<> distrib2(settings.CustomerGetItemMean, settings.CustomerGetItemSD);
    double want = distrib2(gen);

    want = want < 0 ? 0 : want;

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
                   { return cr->QueueEmpty() ? std::numeric_limits<double>::infinity() : 1 / cr->QueueSize(); });

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
    RecyclePerson(cust);
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
            actLeaveShop(shop.GetCustomers().at(buyer.GetID()));
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

std::string Simulation::actGenerateCustomers(Shop &shop)
{
    std::stringstream ss;
    std::discrete_distribution<> dist({1, settings.GenerateCustomerScale / shop.GetCustomers().size()});

    int n = 0;
    while (dist(gen))
    {
        n++;
        dist = {1, settings.GenerateCustomerScale / (shop.GetCustomers().size() + n)};
    }

    auto customers = AddCustomers(n);
    for (const auto &cust : customers)
    {
        ss << "Customer no. " << cust->GetID() << " entered the shop\n"
           << "\tName:\t" << cust->GetName() << "\n"
           << "\tAddress:\t" << cust->GetAddress() << "\n"
           << "\tPhone:\t" << cust->GetPhone() << "\n"
           << "\tMoney:\t" << cust->GetMoney() << "\n";
    }

    return ss.str();
}

std::string Simulation::randomName()
{
    if (names.empty())
        return "unknown";

    std::uniform_int_distribution<> dist(0, names.size() - 1);
    auto it = names.begin();
    std::advance(it, dist(gen));
    auto name = *it;
    names.erase(name);
    return name;
}

std::string Simulation::randomAddress()
{
    if (addresses.empty())
        return "unknown";

    std::uniform_int_distribution<> dist(0, addresses.size() - 1);
    auto it = addresses.begin();
    std::advance(it, dist(gen));
    auto address = *it;
    addresses.erase(address);
    return address;
}

std::string Simulation::randomPhone()
{
    std::uniform_int_distribution<> distrib(100'000'000, 999'999'999);

    int phone;
    do
    {
        phone = distrib(gen);
    } while (phonesTaken.find(phone) != phonesTaken.end());

    phonesTaken.insert(phone);
    return std::to_string(phone);
}

PriceT Simulation::randomMoney()
{
    std::uniform_int_distribution<> distrib(settings.CustomerMoneyMin, settings.CustomerMoneyMax);
    return distrib(gen);
}

void Simulation::turn()
{

    auto action = shopActions.Choose();
    auto msg = (this->*action)(shop);
    std::cout << msg;
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