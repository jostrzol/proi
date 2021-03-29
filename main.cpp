#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <sstream>
#include <limits>

#include "convert.h"

using namespace std;

typedef double (*ConvertFunc)(double);
typedef string (*ConvertFormulaFunc)(string);
typedef vector<tuple<string, ConvertFunc, ConvertFormulaFunc>> Menu;

void printMenu(Menu menu)
{
    cout << "Choose an option:" << endl;
    for (size_t i = 0; i < menu.size(); i++)
    {
        string optionName = get<0>(menu[i]);
        cout << "\t" << i + 1 << ". " << optionName << endl;
    }
    cout << "\t" << menu.size() + 1 << ". "
         << "Exit" << endl;
}

void executeOption(Menu menu, size_t optionIndex)
{
    auto option = menu[optionIndex - 1];
    ConvertFunc convertFunc = get<1>(option);
    ConvertFormulaFunc formulaFunc = get<2>(option);
    double input;
    bool correct = false;
    stringstream ss;

    while (!correct)
    {
        cout << "Enter value to process: ";
        cin >> input;
        if (!cin)
        {
            cout << "Not a numeric value. Try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        ss << input;
        cout << formulaFunc(ss.str()) << " = " << convertFunc(input) << endl;
        correct = true;
    }
}

int main()
{
    bool exit = false;
    size_t option;
    Menu menu = {
        {"Celsius to Fahrenheit", celToFahr, celToFahrFormula},
        {"Fahrenheit to Celsius", fahrToCel, fahrToCelFormula},
        {"Celsius to Kelvin", celToKel, celToKelFormula},
        {"Kelvin to Celsius", kelToCel, kelToCelFormula},
        {"Kelvin to Fahrenheit", kelToFahr, kelToFahrFormula},
        {"Fahrenheit to Kelvin", fahrToKel, fahrToKelFormula},
    };

    while (!exit)
    {
        printMenu(menu);
        cin >> option;
        if (!cin)
        {
            cout << "Invalid option. Try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (option <= 0 || option > menu.size() + 1)
        {
            cout << "Invalid option. Try again." << endl;
        }
        else if (option == menu.size() + 1)
        {
            exit = true;
        }
        else
        {
            executeOption(menu, option);
        }
    }
    return 0;
}