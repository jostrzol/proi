// author: Jakub Ostrzołek

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    unsigned int len = 0;
    double max = -INFINITY, min = INFINITY, sum = 0, number;
    cout << "Enter numeric values, to stop enter a non-numeric value:" << endl;
    do
    {
        cin >> number;
        if (cin)
        {
            len++;
            max = number > max ? number : max;
            min = number < min ? number : min;
            sum += number;
        }
    } while (cin);
    if (len > 0)
    {
        cout << "Maximum: " << max << endl;
        cout << "Minimum: " << min << endl;
        cout << "Average: " << sum / len << endl;
    }
    else
    {
        cout << "No numeric values given, cannot calculate anything." << endl;
        return -1;
    }
    return 0;
}