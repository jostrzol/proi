#pragma once

#include <vector>
#include <iostream>
#include <exception>

class PriceT
{
public:
    PriceT();
    PriceT(int value);
    PriceT(int fulls, int hundreths);

    explicit operator double() const;
    explicit operator int() const;

    bool operator==(const PriceT &other) const;
    bool operator!=(const PriceT &other) const;
    bool operator>(const PriceT &other) const;
    bool operator>=(const PriceT &other) const;
    bool operator<(const PriceT &other) const;
    bool operator<=(const PriceT &other) const;

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

    // Returns the fulls part of this price
    int Fulls() const;
    // Returns the hundreths part of this price
    int Hundreths() const;
    // Returns the integer value used to store the price
    int Value() const;

private:
    int value;
};

struct ErrorNegativePriceT : std::invalid_argument
{
    ErrorNegativePriceT(PriceT price);
    PriceT price;
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