#pragma once

#include "person.h"
#include "product.h"
#include "buyer.h"

class Shop;

class Customer : public virtual Person, public virtual IBuyer
{
public:
    Customer(std::string name = "", std::string address = "", std::string phone = "", int id = -1, PriceT money = 0);

    const IProduct::ProductMap &GetProducts() const;
    void SetProductAmount(const IProduct &product, double amount);
    double GetProductAmount(const IProduct &product) const;

    void SetMoney(PriceT newMoney);
    PriceT GetMoney() const;
    bool Pay(PriceT price);

    void SetPCType(PurchaseConfirmationType newPCType);
    PurchaseConfirmationType GetPCType() const;

    void SetShop(Shop *newShop);
    Shop *GetShop() const;

private:
    PriceT money;
    IProduct::ProductMap products;
    PurchaseConfirmationType prefPCType;
    Shop *shop;
};