#include <sstream>

#include "invoice.h"

Invoice::Invoice(const IContractor *seller, const IContractor *buyer, int id)
    : Receipt(id), seller(seller), buyer(buyer) {}

Invoice::Invoice(IProduct::ProductMap products, const IContractor *seller, const IContractor *buyer, int id)
    : Receipt(std::move(products), id), seller(seller), buyer(buyer) {}

const IContractor &Invoice::Seller() const { return *seller; }
void Invoice::SetSeller(const IContractor &val) { seller = &val; }

const IContractor &Invoice::Buyer() const { return *buyer; }
void Invoice::SetBuyer(const IContractor &val) { buyer = &val; }

const std::string Invoice::stringHead() const
{
    std::stringstream ss;

    ss << "Invoice no. " << ID() << " [" << seller->Name() << " -> " << buyer->Name() << "]:\n";

    return ss.str();
}
