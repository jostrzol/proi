#pragma once

#include <string>

#include "contractor.h"
#include "entity.h"

class Person : public virtual IContractor, public virtual Entity
{
public:
    Person(std::string name = "", std::string address = "", std::string phone = "", int id = -1);

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