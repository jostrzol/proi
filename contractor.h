#ifndef CONTRACTOR_H
#define CONTRACTOR_H

#include <string>
#include <iostream>
#include <exception>

class Contractor
{
public:
    Contractor(std::string name, std::string address, std::string phone);

    std::string Name() const;
    void SetName(const std::string &val);

    std::string Address() const;
    void SetAddress(const std::string &val);

    std::string Phone() const;
    void SetPhone(const std::string &val);

private:
    std::string name;
    std::string address;
    std::string phone;
};

#endif