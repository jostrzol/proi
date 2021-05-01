#pragma once

#include "string"

class IContractor
{
public:
    virtual std::string Name() const = 0;
    virtual std::string Address() const = 0;
    virtual std::string Phone() const = 0;
};