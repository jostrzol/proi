#include <sstream>

#include "invoice.h"

Invoice::Invoice(const IContractor *seller, const IContractor *buyer, const CashRegister *cr, int id)
    : Receipt(cr, id), seller(seller), buyer(buyer) {}

Invoice::Invoice(IProduct::ProductMap products, const IContractor *seller, const IContractor *buyer, const CashRegister *cr, int id)
    : Receipt(std::move(products), cr, id), seller(seller), buyer(buyer) {}

Invoice::Invoice(const Invoice &invoice) : Receipt(invoice)
{
    seller = invoice.seller;
    buyer = invoice.buyer;
}

Invoice::Invoice(Invoice &&invoice) : Receipt(invoice)
{
    seller = invoice.seller;
    buyer = invoice.buyer;
}

Invoice &Invoice::operator=(const Invoice &other)
{
    if (this == &other)
        return *this;
    Receipt::operator=(other);
    seller = other.seller;
    buyer = other.buyer;
    return *this;
}

Invoice &Invoice::operator=(Invoice &&other)
{
    Receipt::operator=(other);
    seller = other.seller;
    buyer = other.buyer;
    return *this;
}

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
