#include <string>
#include <sstream>
#include "convert.h"

double const CEL_KEL_DIFF = 273.15;

double const CEL_FAHR_DIFF = 32;
double const CEL_FAHR_MULT = 1.8;

using namespace std;

double celToFahr(double val)
{
    return val * CEL_FAHR_MULT + CEL_FAHR_DIFF;
}

string celToFahrFormula(string val)
{
    stringstream ss;
    ss << val << " * " << CEL_FAHR_MULT << " + " << CEL_FAHR_DIFF;
    return ss.str();
}

double fahrToCel(double val)
{
    return (val - CEL_FAHR_DIFF) / CEL_FAHR_MULT;
}
string fahrToCelFormula(string val)
{
    stringstream ss;
    ss << "(" << val << " - " << CEL_FAHR_DIFF << ") / " << CEL_FAHR_MULT;
    return ss.str();
}

double celToKel(double val)
{
    return val + CEL_KEL_DIFF;
}
string celToKelFormula(string val)
{
    stringstream ss;
    ss << val << " + " << CEL_KEL_DIFF;
    return ss.str();
}

double kelToCel(double val)
{
    return val - CEL_KEL_DIFF;
}
string kelToCelFormula(string val)
{
    stringstream ss;
    ss << val << " - " << CEL_KEL_DIFF;
    return ss.str();
}

double kelToFahr(double val)
{
    return celToFahr(kelToCel(val));
}
string kelToFahrFormula(string val)
{
    string celForm = "(" + kelToCelFormula(val) + ")";
    return celToFahrFormula(celForm);
}

double fahrToKel(double val)
{
    return celToKel(fahrToCel(val));
}
string fahrToKelFormula(string val)
{
    string fahrForm = "(" + fahrToCelFormula(val) + ")";
    return celToKelFormula(fahrForm);
}
