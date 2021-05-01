#include <iostream>

#include "receipt.h"
#include "item.h"
#include "worker.h"
#include "customer.h"

using namespace std;

int main()
{
    Item door{"door", 12300, pcs, 0.23, 1};
    Item sink{"sink", 25999, pcs, 0.23, 2};
    Item bricks{"bricks", 150, kg, 0.23, 3};
    Item window{"window", 11150, pcs, 0.23, 4};
    Item oil{"oil", 2050, l, 0.23, 5};

    Person manager{"Paweł Zieliński", "ul. Krótka 321, Poznań", "344-231-222"};

    CashRegister cr{&manager, 1};
    Worker work1{"Kowal Jański", "ul. Szeroka 123, Warszawa", "123-456-789", 1, &cr};

    Customer cust1{"Jan Kowalski", "ul. Długa 123, Warszawa", "234-235-231", 1, 800'00};
    Customer cust2{"Piotr Piotrowski", "ul. Wąska 12, Warszawa", "456-226-233", 1, 10'000'00};

    cust1.SetProductAmount(bricks, 5.2);
    cust1.SetProductAmount(window, 3);
    cust1.SetProductAmount(oil, 6.5);

    cust2.SetPreferredPCType(PCInvoice);
    cust2.SetProductAmount(door, 4);
    cust2.SetProductAmount(sink, 3);
    cust2.SetProductAmount(bricks, 3.3);
    cust2.SetProductAmount(window, 1);
    cust2.SetProductAmount(oil, 0.2);

    cr.QueuePush(cust1);
    cr.QueuePush(cust2);

    if (work1.ServeNext())
        cout << cr.Receipts()[0];
    if (work1.ServeNext())
        cout << cr.Invoices()[0];
}
