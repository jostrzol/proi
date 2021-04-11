#include <vector>
#include <iostream>
#include <stdexcept>
#include <string>
#include <regex>
#include <cmath>
#include <limits>
#define IGNORE_LINE std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n')

#include "application.h"

void Application::Run()
{
    running = true;
    while (running)
    {
        printMenu();
        chooseOption();
    }
};
void Application::quit()
{
    running = false;
};
void Application::printMenu()
{
    std::cout << "Choose action:" << std::endl;
    for (std::size_t i = 0; i < menu.size(); i++)
    {
        const auto &pair = menu[i];
        std::cout << "\t" << i + 1 << ". " << pair.first << std::endl;
    }
};
void Application::chooseOption()
{
    std::size_t input;
    std::cin >> input;
    if (!std::cin)
    {
        std::cin.clear();
        IGNORE_LINE;
        std::cout << "Please enter a numeric index" << std::endl;
        return;
    }
    try
    {
        const auto &func = menu.at(input - 1).second;
        (this->*func)();
    }
    catch (std::out_of_range &)
    {
        std::cout << "Please enter a valid option" << std::endl;
    }
};

void Application::newItem()
{
    std::string name;
    UnitT unit;
    PriceT price;

    IGNORE_LINE;

    std::cout << "Item name: ";
    getline(std::cin, name);

    while (true)
    {
        std::cout << "Choose item unit." << std::endl;
        std::cout << "Units: " << std::endl;
        for (const auto unit : UnitTAll)
        {
            std::cout << int(unit) << ". " << unit << std::endl;
        }
        if (std::cin >> unit)
        {
            break;
        }
        else
        {
            std::cin.clear();
            IGNORE_LINE;
            std::cout << "Invalid unit" << std::endl;
        }
    }

    while (true)
    {
        std::cout << "Choose item price." << std::endl;
        std::cout << "Price: ";
        if (std::cin >> price)
        {
            if (price.Value() < 0)
            {
                std::cout << "Cannot be negative" << std::endl;
            }
            else
            {
                break;
            }
        }
        else
        {
            std::cin.clear();
            IGNORE_LINE;
            std::cout << "Invalid price" << std::endl;
        }
    }
    items.push_back(Item(name, price, unit));
};
void Application::newInvoice()
{
    if (contractors.size() < 2)
    {
        std::cout << "Too few contractors to choose from, make new ones" << std::endl;
        return;
    }
    if (items.size() < 1)
    {
        std::cout << "Too few items to choose from, make new ones" << std::endl;
        return;
    }

    Contractor *buyer = NULL;
    Contractor *seller = NULL;

    while (seller == NULL)
    {
        std::cout << "Choose seller." << std::endl;
        seller = chooseContractor();
    }

    while (buyer == NULL)
    {
        std::cout << "Choose buyer." << std::endl;
        buyer = chooseContractor();
        if (buyer == seller)
        {
            std::cout << "Buyer must differ from seller." << std::endl;
            buyer = NULL;
        }
    }

    Invoice invoice = Invoice(*seller, *buyer);
    chooseItemsForInvoice(invoice);

    invoices.push_back(invoice);
};
void Application::newContractor()
{
    std::string name;
    std::string address;
    std::string phone;

    IGNORE_LINE;

    std::cout << "Contractor's name: ";
    getline(std::cin, name);

    std::cout << "Contractor's address: ";
    getline(std::cin, address);

    while (true)
    {
        //matches strings with optional '+' at the beginning, followed by number groups separeted with '-'
        static const std::regex phoneRegEx(R"regex(\+?\d+(?:-?\d+)+)regex");

        std::cout << "Contractor's phone: ";
        std::cin >> phone;
        if (std::regex_match(phone, phoneRegEx))
        {
            break;
        }
        else
        {
            std::cout << "Invalid phone number" << std::endl;
        }
    }
    contractors.push_back(Contractor(name, address, phone));
};

void Application::listItems()
{
    std::cout << "Items:" << std::endl;
    for (std::size_t i = 0; i < items.size(); i++)
    {
        const auto &item = items[i];
        std::cout << i + 1 << ". " << item << std::endl;
    }
};
void Application::listInvoices()
{
    std::cout << "Invoices:" << std::endl;
    for (std::size_t i = 0; i < invoices.size(); i++)
    {
        const auto &invoice = invoices[i];
        std::cout << i + 1 << ". " << invoice;
    }
};
void Application::listContractors()
{
    std::cout << "Contractors:" << std::endl;
    for (std::size_t i = 0; i < contractors.size(); i++)
    {
        const auto &contractor = contractors[i];
        std::cout << i + 1 << ". " << contractor.Name() << ":" << std::endl
                  << "\tAddress: " << contractor.Address() << std::endl
                  << "\tPhone: " << contractor.Phone() << std::endl;
    }
};

void Application::modifyInvoice()
{
    Invoice *invoice = chooseInvoice();
    if (invoice == NULL)
        return;
    std::cout << "What to modify?" << std::endl
              << "\t1. Seller" << std::endl
              << "\t2. Buyer" << std::endl
              << "\t3. Items" << std::endl;
    int choice;
    std::cin >> choice;
    if (!std::cin)
    {
        std::cin.clear();
        IGNORE_LINE;
        std::cout << "Invalid choice" << std::endl;
        return;
    }

    Contractor *contractor;
    switch (choice)
    {
    case 1:
        contractor = chooseContractor();
        if (contractor == &invoice->Buyer())
        {
            std::cout << "Seller must differ from buyer" << std::endl;
            return;
        }
        invoice->SetSeller(*contractor);
        break;
    case 2:
        contractor = chooseContractor();
        if (contractor == &invoice->Seller())
        {
            std::cout << "Buyer must differ from seller" << std::endl;
            return;
        }
        invoice->SetBuyer(*contractor);
        break;
    case 3:
        chooseItemsForInvoice(*invoice);
        break;

    default:
        std::cout << "Invalid choice" << std::endl;
        break;
    }
};

Item &Application::getItem(std::size_t index) { return items.at(index - 1); };
Invoice &Application::getInvoice(std::size_t index) { return invoices.at(index - 1); };
Contractor &Application::getContractor(std::size_t index) { return contractors.at(index - 1); };

Contractor *Application::chooseContractor()
{
    Contractor *contractor;
    listContractors();
    std::size_t input;
    if (std::cin >> input)
    {
        try
        {
            contractor = &getContractor(input);
            return contractor;
        }
        catch (std::out_of_range &)
        {

            std::cout << "Invalid contractor index" << std::endl;
            return NULL;
        }
    }
    else
    {
        std::cin.clear();
        IGNORE_LINE;
        std::cout << "Not a contractor index" << std::endl;
        return NULL;
    }
};
Item *Application::chooseItem()
{
    Item *item;
    listItems();
    std::size_t input;
    if (std::cin >> input)
    {
        try
        {
            item = &getItem(input);
            return item;
        }
        catch (std::out_of_range &)
        {

            std::cout << "Invalid item index" << std::endl;
            return NULL;
        }
    }
    else
    {
        std::cin.clear();
        IGNORE_LINE;
        std::cout << "Not an item index" << std::endl;
        return NULL;
    }
};
Invoice *Application::chooseInvoice()
{
    Invoice *invoice;
    listInvoices();
    std::size_t input;
    if (std::cin >> input)
    {
        try
        {
            invoice = &getInvoice(input);
            return invoice;
        }
        catch (std::out_of_range &)
        {

            std::cout << "Invalid invoice index" << std::endl;
            return NULL;
        }
    }
    else
    {
        std::cin.clear();
        IGNORE_LINE;
        std::cout << "Not an invoice index" << std::endl;
        return NULL;
    }
};

void Application::chooseItemsForInvoice(Invoice &invoice)
{
    while (true)
    {
        std::cout << "Current invoice:" << std::endl;
        std::cout << invoice;

        std::cout << "Choose items ('q' to end)." << std::endl;
        listItems();

        std::size_t input;
        std::cin >> input;
        if (!std::cin)
        {
            std::cin.clear();
            char c;
            std::cin.get(c);
            IGNORE_LINE;
            if (c == 'q')
            {
                if (invoice.Size() > 0)
                    break;
                else
                    std::cout << "There must be at least one item to proceed" << std::endl;
            }
            else
                std::cout << "Please enter an item index" << std::endl;
            continue;
        }
        try
        {
            const Item &item = getItem(input);
            double amount;
            while (true)
            {
                std::cout << "Choose item amount: ";
                std::cin >> amount;
                if (!std::cin)
                {
                    std::cin.clear();
                    IGNORE_LINE;
                    std::cout << "Expected a numeric value" << std::endl;
                    continue;
                }
                if (amount < 0)
                {
                    std::cout << "Expected a non-negative value" << std::endl;
                    continue;
                }
                if (item.Unit() == pcs)
                {
                    if (ceil(amount) == amount) // check if non-integer
                    {
                        break;
                    }
                    else
                    {
                        std::cout << "Expected an integer, as this item's unit is 'pcs.'" << std::endl;
                        continue;
                    }
                }
                else
                {
                    break;
                }
            }
            invoice.SetItemAmount(item, amount);
        }
        catch (std::out_of_range &)
        {
            std::cout << "Invalid item index" << std::endl;
        }
    }
};