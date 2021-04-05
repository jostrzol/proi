#ifndef FINANCE_H
#define FINANCE_H

class PriceT
{
public:
    PriceT(int value);
    PriceT(int zloty, int groszy);

    operator int() const;
    PriceT operator+(const PriceT &other) const;
    PriceT &operator+=(const PriceT &other);
    PriceT operator-(const PriceT &other) const;
    PriceT &operator-=(const PriceT &other);
    PriceT operator*(const int &multiplier) const;
    PriceT &operator*=(const int &multiplier);
    PriceT operator/(const int &multiplier) const;
    PriceT &operator/=(const int &multiplier);

    int Zlote();
    int Grosze();
    int Value();

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

#endif