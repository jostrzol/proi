#include <iostream>

#include "shop/shop.h"

using namespace std;

int main()
{
    Shop shop{0, "DIY shop", "ul. Kręta 111", "223-445-667"};

    Item door{0, "door", 12300, pcs, 0.23};
    Item sink{1, "sink", 25999, pcs, 0.23};
    Item bricks{2, "bricks", 150, kg, 0.23};
    Item window{3, "window", 11150, pcs, 0.23};
    Item oil{4, "oil", 2050, l, 0.23};
    shop.SetItemAmount(door, 200);
    shop.SetItemAmount(sink, 200);
    shop.SetItemAmount(bricks, 200);
    shop.SetItemAmount(window, 200);
    shop.SetItemAmount(oil, 200);

    Person manager{0, "Paweł Zieliński", "ul. Krótka 321, Poznań", "344-231-222"};
    shop.SetManager(&manager);

    CashRegister cr0{0, &shop};
    CashRegister cr1{1, &shop};
    CashRegister cr2{2, &shop};
    shop.AddCashRegister(cr0);
    shop.AddCashRegister(cr1);
    shop.AddCashRegister(cr2);

    Worker work0{0, "Kowal Jański", "ul. Szeroka 123, Warszawa", "123-456-789"};
    Worker work1{1, "Krzysztof Grudziądz", "ul. Piękna 123, Warszawa", "345-232-123"};
    Worker work2{2, "Marian Ostaszewski", "ul. Jana Pawła II 123, Warszawa", "235-231-223"};
    shop.AddWorker(work0);
    shop.AssignWorkerToCashRegister(work0, cr0);
    shop.AddWorker(work1);
    shop.AssignWorkerToHelping(work1);
    shop.AddWorker(work2);
    shop.AssignWorkerToCashRegister(work2, cr1);

    Customer cust0{0, "Jan Kowalski", "ul. Długa 123, Warszawa", "234-235-231", 800'00};
    Customer cust1{1, "Piotr Piotrowski", "ul. Wąska 12, Warszawa", "456-226-233", 10'000'00};
    shop.AddCustomer(cust0);
    shop.AddCustomer(cust1);

    cust0.SetProductAmount(bricks, 5.2);
    cust0.SetProductAmount(window, 3);
    cust0.SetProductAmount(oil, 6.5);

    cust1.SetPCType(PCInvoice);
    cust1.SetProductAmount(door, 4);
    cust1.SetProductAmount(sink, 3);
    cust1.SetProductAmount(bricks, 3.3);
    cust1.SetProductAmount(window, 1);
    cust1.SetProductAmount(oil, 0.2);

    cr0.QueuePush(cust0);
    cr1.QueuePush(cust1);

    if (work0.ServeNext())
        cout << cr0.GetReceipts()[0];
    if (work2.ServeNext())
        cout << cr1.GetInvoices()[0];
}
