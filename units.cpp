#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <cmath>
#include <string>

#include "units.h"

const std::string &CURRENCY = "zł";

PriceT::PriceT() : value(0) {}
PriceT::PriceT(int value) : value(value) {}
PriceT::PriceT(int fulls, int hundreths) { value = fulls * 100 + hundreths; }

PriceT::operator double() const { return double(value) / 100; }
PriceT::operator int() const { return value; }

bool PriceT::operator==(const PriceT &other) const { return value == other.value; }
bool PriceT::operator!=(const PriceT &other) const { return value != other.value; }
bool PriceT::operator>(const PriceT &other) const { return value > other.value; }
bool PriceT::operator>=(const PriceT &other) const { return value >= other.value; }
bool PriceT::operator<(const PriceT &other) const { return value < other.value; }
bool PriceT::operator<=(const PriceT &other) const { return value <= other.value; }

PriceT PriceT::operator+(const PriceT &other) const { return value + other.value; }
PriceT &PriceT::operator+=(const PriceT &other)
{
    value += other.value;
    return *this;
}
PriceT PriceT::operator-(const PriceT &other) const { return value - other.value; }
PriceT &PriceT::operator-=(const PriceT &other)
{
    value -= other.value;
    return *this;
}
PriceT PriceT::operator*(const double &multiplier) const { return round(value * multiplier); }
PriceT &PriceT::operator*=(const double &multiplier)
{
    value = round(value * multiplier);
    return *this;
}
PriceT PriceT::operator/(const double &multiplier) const { return value / multiplier; }
PriceT &PriceT::operator/=(const double &multiplier)
{
    value = round(value / multiplier);
    return *this;
}

int PriceT::Fulls() const { return value / 100; }
int PriceT::Hundreths() const { return value % 100; }
int PriceT::Value() const { return value; }

std::ostream &operator<<(std::ostream &os, const PriceT &price)
{
    const auto &flags = os.flags();
    os << std::setprecision(2) << std::fixed << double(price) << " " << CURRENCY;
    os.flags(flags);
    return os;
}
std::istream &operator>>(std::istream &is, PriceT &price)
{
    double temp;
    is >> temp;
    if (!is)
    {
        return is;
    }
    price.value = round(temp * 100);
    return is;
}

std::ostream &operator<<(std::ostream &os, UnitT unit)
{
    switch (unit)
    {
    case pcs:
        os << "pcs.";
        break;
    case kg:
        os << "kg";
        break;
    case l:
        os << "l";
        break;
    case m:
        os << "m";
        break;
    case square_m:
        os << "m^2";
        break;
    }
    return os;
}

std::istream &operator>>(std::istream &is, UnitT &unit)
{
    static const std::unordered_map<std::string, UnitT> str_map = {
        {"pcs.", pcs},
        {"kg", kg},
        {"l", l},
        {"m", m},
        {"m^2", square_m}};
    const auto &pos = is.tellg();
    int tmpInt;

    if (is >> tmpInt)
    {
        if (tmpInt < UnitTAll.front() || tmpInt > UnitTAll.back())
        {
            is.seekg(pos);
            is.setstate(is.rdstate() | std::ios::failbit);
        }
        else
        {
            unit = static_cast<UnitT>(tmpInt);
        }
    }
    else
    {
        std::string tmpString;
        is.clear();
        is >> tmpString;
        if (!is)
        {
            return is;
        }
        try
        {
            unit = str_map.at(tmpString);
        }
        catch (std::out_of_range &)
        {
            is.seekg(pos);
            is.setstate(is.rdstate() | std::ios::failbit);
        }
    }

    return is;
}