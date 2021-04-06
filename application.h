#ifndef APP_H
#define APP_H

#include <vector>
#include "invoice.h"

class Application
{
public:
    void Run();

private:
    void newItem();
    void newInvoice();
    void newContractor();
    void quit();

    void printMenu();
    void chooseOption();

    bool running = false;
    std::vector<Invoice> invoices;
    std::vector<Contractor> contractors;
    std::vector<Item> items;
    const std::vector<std::pair<std::string, void (Application::*)()>> menu = {
        {"New item", newItem},
        {"New invoice", newInvoice},
        {"New contractor", newContractor},
        {"Quit", quit},
    };
};

#endif