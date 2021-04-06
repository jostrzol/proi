#include <vector>
#include <iostream>
#include <stdexcept>
#include <string>
#include <regex>
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
        std::cout << "\t" << i << ". " << pair.first << std::endl;
    }
};
void Application::chooseOption()
{
    std::size_t input;
    std::cin >> input;
    if (!std::cin)
    {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Please enter a numeric index" << std::endl;
        return;
    }
    try
    {
        const auto &func = menu.at(input).second;
        (*this.*func)();
    }
    catch (std::out_of_range)
    {
        std::cout << "Please enter a valid option" << std::endl;
    }
};

void Application::newItem()
{
    std::string name;
    UnitT unit;
    PriceT price;

    std::cout << "Item name: ";
    std::cin >> name;

    while (true)
    {
        std::cout << "Item unit: ";
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
            std::cin.ignore();
            std::cout << "Please enter a valid unit" << std::endl;
        }
    }

    while (true)
    {
        std::cout << "Item unit price: ";
        if (std::cin >> price)
        {
            break;
        }
        else
        {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Please enter a valid price" << std::endl;
        }
    }
    items.push_back(Item(name, price, unit));
};
void Application::newInvoice(){

};
void Application::newContractor()
{
    //matches strings with optional '+' at the beginning, followed by number groups separeted with '-'
    static const std::regex phoneRegEx(R"regex(\+?\d+(?:-?\d+)+)regex");

    std::string name;
    std::string address;
    std::string phone;

    std::cout << "Contractor's name: ";
    std::cin >> name;

    std::cout << "Contractor's address: ";
    std::cin >> address;

    while (true)
    {
        std::cout << "Contractor's phone: ";
        std::cin >> phone;
        if (std::regex_match(phone, phoneRegEx))
        {
            break;
        }
        else
        {
            std::cout << "Please enter a valid phone number" << std::endl;
        }
    }
};
