#pragma once

#include <string>

class IContractor
{
public:
    // Returns the name of the contractor
    virtual std::string GetName() const = 0;
    // Returns the address of the contractor
    virtual std::string GetAddress() const = 0;
    // Returns the phone of the contractor
    virtual std::string GetPhone() const = 0;

    virtual ~IContractor() = 0;
};
inline IContractor::~IContractor() = default;
