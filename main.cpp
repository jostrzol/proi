#include <iostream>

#include "receipt.h"
#include "item.h"

using namespace std;

int main()
{
    Item door("door", 12300, pcs, 0.23, 1);
    Item sink("sink", 25999, pcs, 0.23, 2);
    Item bricks("bricks", 150, kg, 0.23, 3);
    Item window("window", 11150, pcs, 0.23, 4);
    Item oil("oil", 2050, l, 0.23, 5);

    Receipt r(1);

    r.SetItemAmount(door, 1);
    r.SetItemAmount(sink, 3);
    r.SetItemAmount(bricks, 30);

    cout << r;
}
