#pragma once

#include "entity.h"
#include "string"

class IContractor : public Entity
{
public:
    virtual const std::string Name() const = 0;
    virtual const std::string Address() const = 0;
    virtual const std::string Phone() const = 0;
};