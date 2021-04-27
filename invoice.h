#pragma once

#include "contractor.h"
#include "receipt.h"

class Invoice : public Receipt
{
public:
    Invoice(const IContractor &seller, const IContractor &buyer, int id = -1);

    const IContractor &Seller() const;
    void SetSeller(const IContractor &val);

    const IContractor &Buyer() const;
    void SetBuyer(const IContractor &val);

protected:
private:
    const IContractor *seller;
    const IContractor *buyer;
};