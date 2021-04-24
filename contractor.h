#ifndef CONTRACTOR_H
#define CONTRACTOR_H

#include <string>
#include <iostream>
#include <exception>

#include "entity.h"

class Contractor : public Entity
{
public:
    Contractor(std::string name = "", std::string address = "", std::string phone = "", int id = -1);

    std::string Name() const;
    void SetName(const std::string &val);

    std::string Address() const;
    void SetAddress(const std::string &val);

    std::string Phone() const;
    void SetPhone(const std::string &val);

private:
    int id;
    std::string name;
    std::string address;
    std::string phone;
};

#endif