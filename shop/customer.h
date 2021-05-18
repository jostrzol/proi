#pragma once

#include "person.h"
#include "product.h"
#include "buyer.h"

class Shop;

class Customer : public virtual Person, public virtual IBuyer
{
public:
    Customer(Shop &shop, int id = -1, std::string name = "", std::string address = "", std::string phone = "", PriceT money = 0);

    const IProduct::ProductMap &GetProducts() const;
    void ClearProducts();
    void SetProductAmount(const IProduct &product, double amount);
    double GetProductAmount(const IProduct &product) const;

    // Takes a product from the current shop and returns the amount of products taken
    // If there isn't enough of given product in the shop, the return value is less than amount argument
    double TakeProduct(const IProduct &product, double amount);
    // Leaves all of the given product in the shop
    // returns true onsuccess
    bool LeaveProduct(const IProduct &product);

    void JoinQueue(CashRegister &cr);
    CashRegister *GetCashRegister();
    CashRegister *DeassignCashRegister();

    void SetMoney(PriceT newMoney);
    PriceT GetMoney() const;
    bool Pay(PriceT price);

    void SetPCType(PurchaseConfirmationType newPCType);
    PurchaseConfirmationType GetPCType() const;

    Shop &GetShop() const;

    bool IsInShop() const;
    void LeaveShop();
    void EnterShop();

private:
    PriceT money;
    IProduct::ProductMap products;
    PurchaseConfirmationType prefPCType;
    Shop &shop;
    CashRegister *cashRegister = nullptr;
    bool inShop = true;
};