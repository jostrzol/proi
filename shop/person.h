#pragma once

#include <string>

#include "contractor.h"
#include "entity.h"

class Person : public virtual IContractor, public virtual Entity
{
public:
    Person(int id = -1, std::string name = "", std::string address = "", std::string phone = "");

    Person &operator=(Person &&) = default;

    std::string GetName() const;
    void SetName(const std::string &val);

    std::string GetAddress() const;
    void SetAddress(const std::string &val);

    std::string GetPhone() const;
    void SetPhone(const std::string &val);

private:
    std::string name;
    std::string address;
    std::string phone;
};