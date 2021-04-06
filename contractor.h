#ifndef CONTRACTOR_H
#define CONTRACTOR_H

#include <string>
#include <iostream>
#include <exception>

class InvalidPhone : public std::exception
{
    std::string phone;

public:
    InvalidPhone(std::string phone);
    virtual const char *what() const throw();
};

class PhoneT
{
public:
    PhoneT(std::string phone);

    friend std::istream &operator>>(std::istream &is, PhoneT &phone);
    friend std::ostream &operator<<(std::ostream &os, PhoneT &phone);

private:
    std::string phone;

    void validatePhone(std::string phone);
};

class Contractor
{
public:
    Contractor(std::string name, std::string address, PhoneT phone);

    std::string Name();
    void SetName(const std::string &val);

    std::string Address();
    void SetAddress(const std::string &val);

    PhoneT Phone();
    void SetPhone(const PhoneT &val);

private:
    std::string name;
    std::string address;
    PhoneT phone;
};

#endif