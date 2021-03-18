#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <sstream>
#include "convert.h"

using namespace std;

typedef double (*ConvertFunc)(double);
typedef string (*ConvertFormulaFunc)(string);
vector<tuple<string, ConvertFunc, ConvertFormulaFunc>> options = {
    {"Celsius to Fahrenheit", celToFahr, celToFahrFormula},
    {"Fahrenheit to Celsius", fahrToCel, fahrToCelFormula},
    {"Celsius to Kelvin", celToKel, celToKelFormula},
    {"Kelvin to Celsius", kelToCel, kelToCelFormula},
    {"Kelvin to Fahrenheit", kelToFahr, kelToFahrFormula},
    {"Fahrenheit to Kelvin", fahrToKel, fahrToKelFormula},
};

void printMenu()
{
    cout << "Choose an option:" << endl;
    for (size_t i = 0; i < options.size(); i++)
    {
        string optionName = get<0>(options[i]);
        cout << "\t" << i + 1 << ". " << optionName << endl;
    }
    cout << "\t" << options.size() + 1 << ". "
         << "Exit" << endl;
}

void executeOption(int optionIndex)
{
    auto option = options[optionIndex - 1];
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
            cin.sync();
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

    while (!exit)
    {
        printMenu();
        cin >> option;
        if (!cin)
        {
            cout << "Invalid option. Try again." << endl;
            cin.clear();
            cin.sync();
        }
        if (option <= 0 || option > options.size() + 1)
        {
            cout << "Invalid option. Try again." << endl;
        }
        else if (option == options.size() + 1)
        {
            exit = true;
        }
        else
        {
            executeOption(option);
        }
    }
    return 0;
}