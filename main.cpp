#include <iostream>
#include <fstream>
#include <csignal>

#include "object_generator.h"
#include "simulation.h"

using namespace std;

void ShopTest()
{
    Shop shop{0, "DIY shop", "ul. Kręta 111", "223-445-667"};

    Item &door = shop.AddItem(0, "door", 12300, pcs, 0.23, "home", 200);
    Item &sink = shop.AddItem(1, "sink", 25999, pcs, 0.23, "plumbing", 200);
    Item &bricks = shop.AddItem(2, "bricks", 150, kg, 0.23, "construction", 200);
    Item &window = shop.AddItem(3, "window", 11150, pcs, 0.23, "home", 200);
    Item &oil = shop.AddItem(4, "oil", 2050, l, 0.23, "misc", 200);

    Person manager{0, "Paweł Zieliński", "ul. Krótka 321, Poznań", "344-231-222"};
    shop.SetManager(&manager);

    CashRegister &cr0 = shop.AddCashRegister(0);
    CashRegister &cr1 = shop.AddCashRegister(1);
    /*CashRegister &cr2 =*/shop.AddCashRegister(2);

    Worker &work0 = shop.AddWorker(0, "Kowal Jański", "ul. Szeroka 123, Warszawa", "123-456-789");
    Worker &work1 = shop.AddWorker(1, "Krzysztof Grudziądz", "ul. Piękna 123, Warszawa", "345-232-123");
    Worker &work2 = shop.AddWorker(2, "Marian Ostaszewski", "ul. Jana Pawła II 123, Warszawa", "235-231-223");
    shop.AssignWorkerToCashRegister(work0, cr0);
    shop.AssignWorkerToHelping(work1);
    shop.AssignWorkerToCashRegister(work2, cr1);

    Customer &cust0 = shop.AddCustomer(0, "Jan Kowalski", "ul. Długa 123, Warszawa", "234-235-231", 800'00);
    Customer &cust1 = shop.AddCustomer(1, "Piotr Piotrowski", "ul. Wąska 12, Warszawa", "456-226-233", 10'000'00);

    cust0.TakeProduct(bricks, 5.2);
    cust0.TakeProduct(window, 3);
    cust0.TakeProduct(oil, 6.5);

    cust1.SetPCType(PCInvoice);
    cust1.TakeProduct(door, 4);
    cust1.TakeProduct(sink, 3);
    cust1.LeaveProduct(door);
    cust1.TakeProduct(bricks, 3.3);
    cust1.TakeProduct(window, 1);
    cust1.TakeProduct(oil, 0.2);

    cr0.QueuePush(cust0);
    cr1.QueuePush(cust1);
}

int main(int argc, char *argv[])
{
    ShopTest();

    const int nArgs = 3;

    if (argc != nArgs)
    {
        cout << "Expected " << nArgs - 1 << " arguments, not " << argc - 1 << "\n";
        return -1;
    }

    int nCashRegisters = std::stoi(argv[1]);
    int nWorkers = std::stoi(argv[2]);

    Shop shop(0, "DIY Shop");

    ObjectGenerator og(shop);

    auto f = ifstream("names.txt");
    og.ReadNames(f);
    f.close();

    f = ifstream("addresses.txt");
    og.ReadAddresses(f);
    f.close();

    f = ifstream("items.csv");
    og.ReadItems(f);
    f.close();

    og.GenerateShopInfo();
    Person manager = og.GeneratePerson();
    shop.SetManager(&manager);

    og.AddCashRegisters(nCashRegisters);
    og.AddWorkers(nWorkers);
    og.AddCustomers(og.RemainingRandomPeople());

    shop.SetCloseTime(std::chrono::hours(15));

    Simulation sim(shop);

    auto logfile = ofstream("log.txt");
    sim.SetLogfile(&logfile);

    sim.Run();

    logfile.close();

    return 0;
}
