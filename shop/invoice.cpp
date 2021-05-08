#include <sstream>

#include "invoice.h"

Invoice::Invoice(int id, const IContractor *seller, const IContractor *buyer, const CashRegister *cr)
    : Receipt(id, cr), seller(seller), buyer(buyer) {}

Invoice::Invoice(IProduct::ProductMap products, int id, const IContractor *seller, const IContractor *buyer, const CashRegister *cr)
    : Receipt(std::move(products), id, cr), seller(seller), buyer(buyer) {}

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

const IContractor &Invoice::GetSeller() const { return *seller; }
void Invoice::SetSeller(const IContractor &val) { seller = &val; }

const IContractor &Invoice::GetBuyer() const { return *buyer; }
void Invoice::SetBuyer(const IContractor &val) { buyer = &val; }

const std::string Invoice::stringHead() const
{
    std::stringstream ss;

    ss << "Invoice no. " << FullID() << " [" << seller->GetName() << " -> " << buyer->GetName() << "]:\n";

    return ss.str();
}
