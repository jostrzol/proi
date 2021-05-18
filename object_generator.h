#pragma once

#include <unordered_set>
#include <random>

#include "shop/shop.h"

class ObjectGenerator
{
public:
    ObjectGenerator(Shop &shop);

    // Reads names from a file to use them to generate objects
    void ReadNames(std::istream &file);
    // Reads addresses from a file to use them to generate objects
    void ReadAddresses(std::istream &file);
    // Read items from the .csv file in format:
    // ItemID,ItemName,ItemCategory,ItemUnit,ItemUnitPrice,ItemUnitTax,ItemAmount
    // to the given shop
    void ReadItems(std::istream &file);

    // Adds n cash registers
    std::vector<CashRegister *> AddCashRegisters(int n);
    // Adds n randomly generated workers
    std::vector<Worker *> AddWorkers(int n);
    // Adds n randomly generated customers
    std::vector<Customer *> AddCustomers(int n, bool inShop = false);
    // Returns the amount of possible random people to generate without using placeholders
    std::size_t RemainingRandomPeople() const;

    // Returns randomly generated person
    Person GeneratePerson();
    // Makes person's data possible to generate again
    void RecyclePerson(const Person &person);
    // Assigns randomly generated info to shop
    void GenerateShopInfo();

    // Placeholder to use if no more names can be generated
    std::string NamePlaceholder = "unknown";
    // Placeholder to use if no more addresses can be generated
    std::string AddressPlaceholder = "unknown";

    // Minimal customer money used in customer generation
    PriceT CustomerMoneyMin = 500'00;
    // Maximal customer money used in customer generation
    PriceT CustomerMoneyMax = 5000'00;

private:
    Shop &shop;

    std::unordered_set<std::string> names;
    std::unordered_set<std::string> addresses;
    std::unordered_set<int> phonesTaken;

    // Generates random name which isn't already taken, or NamePlaceholder if no new names are available
    std::string randomName();
    // Generates random address which isn't already taken, or AddressPlaceholder if no new addresses are available
    std::string randomAddress();
    // Generates random phone number which isn't already taken
    std::string randomPhone();
    // Generates random amount of money for a new customer
    PriceT randomMoney();

    static std::random_device rd;
    static std::mt19937 gen;
};

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