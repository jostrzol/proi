// author       : Jakub Ostrzołek
// description  : Temperature unit converter

#ifndef CONVERT_H
#define CONVERT_H
#include <string>

double celToFahr(const double &val);
std::string celToFahrFormula(const double &val);

double fahrToCel(const double &val);
std::string fahrToCelFormula(const double &val);

double celToKel(const double &val);
std::string celToKelFormula(const double &val);

double kelToCel(const double &val);
std::string kelToCelFormula(const double &val);

double kelToFahr(const double &val);
std::string kelToFahrFormula(const double &val);

double fahrToKel(const double &val);
std::string fahrToKelFormula(const double &val);

#endif