// author       : Jakub Ostrzołek
// description  : Temperature unit converter

#include <string>
#include <sstream>
#include "convert.h"

double const CEL_KEL_DIFF = 273.15;

double const CEL_FAHR_DIFF = 32;
double const CEL_FAHR_MULT = 1.8;

using namespace std;

double celToFahr(const double &val)
{
    return val * CEL_FAHR_MULT + CEL_FAHR_DIFF;
}

string celToFahrFormula(const double &val)
{
    stringstream ss;
    ss << val << " * " << CEL_FAHR_MULT << " + " << CEL_FAHR_DIFF;
    return ss.str();
}

double fahrToCel(const double &val)
{
    return (val - CEL_FAHR_DIFF) / CEL_FAHR_MULT;
}
string fahrToCelFormula(const double &val)
{
    stringstream ss;
    ss << "(" << val << " - " << CEL_FAHR_DIFF << ") / " << CEL_FAHR_MULT;
    return ss.str();
}

double celToKel(const double &val)
{
    return val + CEL_KEL_DIFF;
}
string celToKelFormula(const double &val)
{
    stringstream ss;
    ss << val << " + " << CEL_KEL_DIFF;
    return ss.str();
}

double kelToCel(const double &val)
{
    return val - CEL_KEL_DIFF;
}
string kelToCelFormula(const double &val)
{
    stringstream ss;
    ss << val << " - " << CEL_KEL_DIFF;
    return ss.str();
}

double kelToFahr(const double &val)
{
    return celToFahr(kelToCel(val));
}
string kelToFahrFormula(const double &val)
{
    stringstream ss;
    string celForm = "(" + kelToCelFormula(val) + ")";
    ss << celForm << " * " << CEL_FAHR_MULT << " + " << CEL_FAHR_DIFF;
    return ss.str();
}

double fahrToKel(const double &val)
{
    return celToKel(fahrToCel(val));
}
string fahrToKelFormula(const double &val)
{
    stringstream ss;
    string fahrForm = fahrToCelFormula(val);
    ss << fahrForm << " + " << CEL_KEL_DIFF;
    return ss.str();
}
