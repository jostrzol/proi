#include <iostream>

#include "shop.h"

using namespace std;

int main()
{
    Shop shop{"DIY shop", "ul. Kręta 111", "223-445-667"};

    Item door{"door", 12300, pcs, 0.23, 1};
    Item sink{"sink", 25999, pcs, 0.23, 2};
    Item bricks{"bricks", 150, kg, 0.23, 3};
    Item window{"window", 11150, pcs, 0.23, 4};
    Item oil{"oil", 2050, l, 0.23, 5};
    shop.SetItemAmount(door, 200);
    shop.SetItemAmount(sink, 200);
    shop.SetItemAmount(bricks, 200);
    shop.SetItemAmount(window, 200);
    shop.SetItemAmount(oil, 200);

    Person manager{"Paweł Zieliński", "ul. Krótka 321, Poznań", "344-231-222"};
    shop.SetManager(&manager);

    CashRegister cr1{&shop, 1};
    CashRegister cr2{&shop, 2};
    CashRegister cr3{&shop, 3};
    shop.AddCashRegister(cr1);
    shop.AddCashRegister(cr2);
    shop.AddCashRegister(cr3);

    Worker work1{"Kowal Jański", "ul. Szeroka 123, Warszawa", "123-456-789", 1};
    Worker work2{"Krzysztof Grudziądz", "ul. Piękna 123, Warszawa", "345-232-123", 2};
    Worker work3{"Marian Ostaszewski", "ul. Jana Pawła II 123, Warszawa", "235-231-223", 3};
    shop.AddWorker(work1);
    shop.AssignWorkerToCashRegister(work1, cr1);
    shop.AddWorker(work2);
    shop.AssignWorkerToHelping(work2);
    shop.AddWorker(work3);
    shop.AssignWorkerToCashRegister(work3, cr2);

    Customer cust1{"Jan Kowalski", "ul. Długa 123, Warszawa", "234-235-231", 1, 800'00};
    Customer cust2{"Piotr Piotrowski", "ul. Wąska 12, Warszawa", "456-226-233", 2, 10'000'00};
    shop.AddCustomer(cust1);
    shop.AddCustomer(cust2);

    cust1.SetProductAmount(bricks, 5.2);
    cust1.SetProductAmount(window, 3);
    cust1.SetProductAmount(oil, 6.5);

    cust2.SetPCType(PCInvoice);
    cust2.SetProductAmount(door, 4);
    cust2.SetProductAmount(sink, 3);
    cust2.SetProductAmount(bricks, 3.3);
    cust2.SetProductAmount(window, 1);
    cust2.SetProductAmount(oil, 0.2);

    cr1.QueuePush(cust1);
    cr2.QueuePush(cust2);

    if (work1.ServeNext())
        cout << cr1.GetReceipts()[0];
    if (work3.ServeNext())
        cout << cr2.GetInvoices()[0];
}
