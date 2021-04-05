#include <iostream>
#include <iomanip>
#include "units.h"

PriceT::PriceT(int value) : value(value){};
PriceT::PriceT(int zloty, int groszy) { value = zloty * 100 + groszy; };

PriceT::operator int() const { return value; };
PriceT PriceT::operator+(const PriceT &other) const { return value + other.value; };
PriceT &PriceT::operator+=(const PriceT &other)
{
    value += other.value;
    return *this;
};
PriceT PriceT::operator-(const PriceT &other) const { return value - other.value; };
PriceT &PriceT::operator-=(const PriceT &other)
{
    value -= other.value;
    return *this;
};
PriceT PriceT::operator*(const int &multiplier) const { return value * multiplier; };
PriceT &PriceT::operator*=(const int &multiplier)
{
    value *= multiplier;
    return *this;
};
PriceT PriceT::operator/(const int &multiplier) const { return value / multiplier; };
PriceT &PriceT::operator/=(const int &multiplier)
{
    value /= multiplier;
    return *this;
};

int PriceT::Zlote() { return value / 100; };
int PriceT::Grosze() { return value % 100; };
int PriceT::Value() { return value; };

std::ostream &operator<<(std::ostream &os, PriceT price)
{
    os << price.Zlote() << '.' << std::setfill('0') << std::setw(2) << price.Grosze() << " zł";
    return os;
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
