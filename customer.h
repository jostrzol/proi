#pragma once

#include "person.h"
#include "product.h"
#include "buyer.h"

class Customer : public virtual Person, public virtual IBuyer
{
public:
    Customer(std::string name = "", std::string address = "", std::string phone = "", int id = -1, PriceT money = 0);

    const IProduct::ProductMap &Products() const;
    void SetProductAmount(const IProduct &product, double amount);
    double ProductAmount(const IProduct &product) const;

    void SetMoney(PriceT newMoney);
    PriceT Money() const;
    bool Pay(PriceT price);

    PurchaseConfirmationType PCType() const;
    void SetPreferredPCType(PurchaseConfirmationType newPCType);

private:
    PriceT money;
    IProduct::ProductMap products;
    PurchaseConfirmationType prefPCType;
};