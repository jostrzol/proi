#include <sstream>

#include "object_generator.h"

ObjectGenerator::ObjectGenerator(std::mt19937 &gen, Shop &shop)
    : shop(shop), gen(gen) {}

Person ObjectGenerator::GeneratePerson()
{
    return std::move(Person(-1, randomName(), randomAddress(), randomPhone()));
}

void ObjectGenerator::RecyclePerson(const Person &person)
{
    if (person.GetName() != NamePlaceholder)
        names.insert(person.GetName());
    if (person.GetAddress() != AddressPlaceholder)
        addresses.insert(person.GetAddress());
}

void ObjectGenerator::GenerateShopInfo()
{
    shop.SetPhone(randomPhone());
    shop.SetAddress(randomAddress());
}
void ObjectGenerator::ReadNames(std::istream &file)
{
    while (!file.eof())
    {
        std::string line;
        std::getline(file, line);
        names.insert(line);
    }
}

void ObjectGenerator::ReadAddresses(std::istream &file)
{
    while (!file.eof())
    {
        std::string line;
        std::getline(file, line);
        addresses.insert(line);
    }
}

std::vector<CashRegister *> ObjectGenerator::AddCashRegisters(int n)
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

std::vector<Worker *> ObjectGenerator::AddWorkers(int n)
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

std::vector<Customer *> ObjectGenerator::AddCustomers(int n, bool inShop)
{
    std::vector<Customer *> customers;
    if (n <= 0)
        return customers;
    int firstID = FindFreeIDs(shop.GetCustomers(), n);
    for (int i = 0; i < n; i++)
    {
        int id = firstID + i;
        auto &cust = shop.AddCustomer(id, randomName(), randomAddress(), randomPhone(), randomMoney());
        if (!inShop)
            cust.LeaveShop();
        customers.push_back(&cust);

        std::discrete_distribution<> dist({1, 1});
        cust.SetPCType(static_cast<PurchaseConfirmationType>(dist(gen)));
    }
    return customers;
}

std::size_t ObjectGenerator::RemainingRandomPeople() const
{
    return names.size() < addresses.size() ? names.size() : addresses.size();
}

void ObjectGenerator::ReadItems(std::istream &file)
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
        double unitTaxPercentage;
        double itemAmount;

        if (!ReadCSVLine(lineStream, id, name, category, unit, unitPrice, unitTaxPercentage, itemAmount))
            throw ErrorMalformedCSVLine(line);
        shop.AddItem(id, name, unitPrice, unit, unitTaxPercentage, category, itemAmount);
    }
}
std::string ObjectGenerator::randomName()
{
    if (names.empty())
        return NamePlaceholder;

    std::uniform_int_distribution<> dist(0, names.size() - 1);
    auto it = names.begin();
    std::advance(it, dist(gen));
    auto name = *it;
    names.erase(name);
    return name;
}

std::string ObjectGenerator::randomAddress()
{
    if (addresses.empty())
        return AddressPlaceholder;

    std::uniform_int_distribution<> dist(0, addresses.size() - 1);
    auto it = addresses.begin();
    std::advance(it, dist(gen));
    auto address = *it;
    addresses.erase(address);
    return address;
}

std::string ObjectGenerator::randomPhone()
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

PriceT ObjectGenerator::randomMoney()
{
    std::uniform_int_distribution<> distrib(CustomerMoneyMin.Value(), CustomerMoneyMax.Value());
    return distrib(gen);
}

ErrorInvalidCSVHeader::ErrorInvalidCSVHeader(std::string header)
    : ErrorCSV("Invalid CSV header"), header(header)
{
}

ErrorMalformedCSVLine::ErrorMalformedCSVLine(std::string line)
    : ErrorCSV("Malformed CSV line"), line(line) {}
