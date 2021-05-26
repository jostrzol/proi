#pragma once

#include "contractor.h"
#include "receipt.h"

class Invoice : public Receipt
{
public:
    Invoice(int id = -1, const IContractor *seller = nullptr, const IContractor *buyer = nullptr, const CashRegister *cr = nullptr);
    Invoice(IProduct::ProductMap products, int id = -1, const IContractor *seller = nullptr, const IContractor *buyer = nullptr, const CashRegister *cr = nullptr);
    Invoice(const Invoice &invoice);
    Invoice(Invoice &&invoice);

    Invoice &operator=(const Invoice &other);
    Invoice &operator=(Invoice &&other);

    // Returns the invoice's seller
    const IContractor &GetSeller() const;
    // Sets the invoice's seller
    void SetSeller(const IContractor &val);

    // Returns the invoice's buyer
    const IContractor &GetBuyer() const;
    // Sets the invoice's buyer
    void SetBuyer(const IContractor &val);

protected:
    const std::string stringHead() const;

private:
    const IContractor *seller;
    const IContractor *buyer;
};
