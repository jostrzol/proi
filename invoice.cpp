#include <sstream>

#include "invoice.h"

const IContractor &Invoice::Seller() const { return *seller; }
void Invoice::SetSeller(const IContractor &val) { seller = &val; }

const IContractor &Invoice::Buyer() const { return *buyer; }
void Invoice::SetBuyer(const IContractor &val) { buyer = &val; }

const std::string Invoice::stringHead() const
{
    std::stringstream ss;

    ss << "Invoice no. " << ID() << ":\n";

    return ss.str();
}