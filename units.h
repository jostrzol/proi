#ifndef FINANCE_H
#define FINANCE_H

#include <vector>
#include <iostream>

class PriceT
{
public:
    PriceT();
    PriceT(int value);
    PriceT(int fulls, int hundreths);

    explicit operator double() const;
    explicit operator int() const;
    bool operator==(const PriceT &other) const;
    PriceT operator+(const PriceT &other) const;
    PriceT &operator+=(const PriceT &other);
    PriceT operator-(const PriceT &other) const;
    PriceT &operator-=(const PriceT &other);
    PriceT operator*(const double &multiplier) const;
    PriceT &operator*=(const double &multiplier);
    PriceT operator/(const double &multiplier) const;
    PriceT &operator/=(const double &multiplier);

    friend std::ostream &operator<<(std::ostream &os, const PriceT &price);
    friend std::istream &operator>>(std::istream &os, PriceT &price);

    int Fulls() const;
    int Hundreths() const;
    int Value() const;

private:
    int value;
};

enum UnitT
{
    pcs,
    kg,
    l,
    m,
    square_m
};
std::ostream &operator<<(std::ostream &os, UnitT unit);
std::istream &operator>>(std::istream &is, UnitT &unit);

const std::vector<UnitT> UnitTAll = {pcs, kg, l, m, square_m};

#endif