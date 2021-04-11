#include <vector>
#include "application.h"

int main()
{
    Application app;

    app.items.emplace_back("door", 12300, pcs);
    app.items.emplace_back("sink", 25999, pcs);
    app.items.emplace_back("bricks", 150, kg);
    app.items.emplace_back("window", 11150, pcs);
    app.items.emplace_back("oil", 2050, l);
    Item &door = app.items[0];
    Item &sink = app.items[1];
    Item &bricks = app.items[2];
    Item &window = app.items[3];
    Item &oil = app.items[4];

    app.contractors.emplace_back("DIY Store", "ul. Długa 123, Warszawa", "+48-123-456-789");
    app.contractors.emplace_back("Adam Dzwon", "ul. Krótka 123, Warszawa", "111-222-333");
    app.contractors.emplace_back("Jurek Ogórek", "ul. Szeroka 321, Warszawa", "000-000-123");
    Contractor &store = app.contractors[0];
    Contractor &adam = app.contractors[1];
    Contractor &jurek = app.contractors[2];

    app.invoices.emplace_back(store, adam);
    Invoice &invoice1 = app.invoices[0];
    invoice1.SetItemAmount(door, 2);
    invoice1.SetItemAmount(sink, 1);
    invoice1.SetItemAmount(oil, 10.2);

    app.invoices.emplace_back(store, jurek);
    Invoice &invoice2 = app.invoices[1];
    invoice2.SetItemAmount(bricks, 100);
    invoice2.SetItemAmount(window, 25);
    invoice2.SetItemAmount(door, 10);
    invoice2.SetItemAmount(oil, 2.5);

    app.Run();
    return 0;
}