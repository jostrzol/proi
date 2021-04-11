#ifndef APP_H
#define APP_H

#include <vector>
#include <utility>
#include "invoice.h"

class Application
{
public:
    void Run();

    std::vector<Invoice> invoices;
    std::vector<Contractor> contractors;
    std::vector<Item> items;

private:
    void newItem();
    void newInvoice();
    void newContractor();
    void listItems();
    void listInvoices();
    void listContractors();
    void modifyInvoice();
    void quit();

    void printMenu();
    void chooseOption();

    Item &getItem(std::size_t index);
    Invoice &getInvoice(std::size_t index);
    Contractor &getContractor(std::size_t index);

    Item *chooseItem();
    Invoice *chooseInvoice();
    Contractor *chooseContractor();

    UnitT *chooseUnit();
    PriceT *choosePrice(bool canBeNegative = false);
    void chooseItemsForInvoice(Invoice &invoice);
    std::string *choosePhone();

    bool running = false;
    const std::vector<std::pair<std::string, void (Application::*)()>> menu = {
        std::make_pair("New item", &Application::newItem),
        std::make_pair("New invoice", &Application::newInvoice),
        std::make_pair("New contractor", &Application::newContractor),
        std::make_pair("List items", &Application::listItems),
        std::make_pair("List invoices", &Application::listInvoices),
        std::make_pair("List contractors", &Application::listContractors),
        std::make_pair("Modify invoice", &Application::modifyInvoice),
        std::make_pair("Quit", &Application::quit),
    };
};

#endif