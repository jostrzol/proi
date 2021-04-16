#include <iostream>

#include "set.h"

using namespace std;

int main()
{
    Set<int> set;
    set.Add(3);
    set.Add(6);
    set.Add(2);
    set.Add(22);
    set.Add(2);
    set.Add(19);

    cout << boolalpha << set.Contains(5) << std::endl;
    cout << boolalpha << set.Contains(6) << std::endl;

    set.Remove(6);
    cout << set.Contains(6);
}