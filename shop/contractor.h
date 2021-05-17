#pragma once

#include <string>

class IContractor
{
public:
    virtual std::string GetName() const = 0;
    virtual std::string GetAddress() const = 0;
    virtual std::string GetPhone() const = 0;

    virtual ~IContractor() = 0;
};
inline IContractor::~IContractor() = default;