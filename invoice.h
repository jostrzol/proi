#pragma once

#include "contractor.h"
#include "receipt.h"

class Invoice : public virtual Receipt
{
public:
    Invoice(const IContractor *seller = nullptr, const IContractor *buyer = nullptr, const CashRegister *cr = nullptr, int id = -1);
    Invoice(IProduct::ProductMap products, const IContractor *seller = nullptr, const IContractor *buyer = nullptr, const CashRegister *cr = nullptr, int id = -1);
    Invoice(const Invoice &invoice);
    Invoice(Invoice &&invoice);

    Invoice &operator=(const Invoice &other);
    Invoice &operator=(Invoice &&other);

    const IContractor &Seller() const;
    void SetSeller(const IContractor &val);

    const IContractor &Buyer() const;
    void SetBuyer(const IContractor &val);

protected:
    const std::string stringHead() const;

private:
    const IContractor *seller;
    const IContractor *buyer;
};