#include "invoice.h"

const IContractor &Invoice::Seller() const { return *seller; }
void Invoice::SetSeller(const IContractor &val) { seller = &val; }

const IContractor &Invoice::Buyer() const { return *buyer; }
void Invoice::SetBuyer(const IContractor &val) { buyer = &val; }