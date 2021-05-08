#pragma once

#include "contractor.h"
#include "receipt.h"

class Invoice : public virtual Receipt
{
public:
    Invoice(int id = -1, const IContractor *seller = nullptr, const IContractor *buyer = nullptr, const CashRegister *cr = nullptr);
    Invoice(IProduct::ProductMap products, int id = -1, const IContractor *seller = nullptr, const IContractor *buyer = nullptr, const CashRegister *cr = nullptr);
    Invoice(const Invoice &invoice);
    Invoice(Invoice &&invoice);

    Invoice &operator=(const Invoice &other);
    Invoice &operator=(Invoice &&other);

    const IContractor &GetSeller() const;
    void SetSeller(const IContractor &val);

    const IContractor &GetBuyer() const;
    void SetBuyer(const IContractor &val);

protected:
    const std::string stringHead() const;

private:
    const IContractor *seller;
    const IContractor *buyer;
};