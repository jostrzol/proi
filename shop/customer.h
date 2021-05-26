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
    // Clears customers products without leaving it in the shop
    void ClearProducts();
    // Sets a product amount that the customer is carrying
    void SetProductAmount(const IProduct &product, double amount);
    // Returns amount of product that the customer is carrying
    double GetProductAmount(const IProduct &product) const;

    // Takes a product from the current shop and returns the amount of products taken
    // If there isn't enough of given product in the shop, the return value is less than amount argument
    double TakeProduct(const IProduct &product, double amount);
    // Leaves all of the given product in the shop
    // returns true on success
    bool LeaveProduct(const IProduct &product);

    void JoinQueue(CashRegister &cr);
    CashRegister *GetCashRegister();
    CashRegister *DeassignCashRegister();

    // Sets customer's money
    void SetMoney(PriceT newMoney);
    // Returns customer's money
    PriceT GetMoney() const;
    bool Pay(PriceT price);

    // Sets the customer's preferred purchase confirmation type
    void SetPCType(PurchaseConfirmationType newPCType);
    PurchaseConfirmationType GetPCType() const;

    Shop &GetShop() const;

    // Checks if the customer is in shop at the moment
    bool IsInShop() const;
    // Makes the customer leave the shop
    void LeaveShop();
    // Makes the customer enter the shop
    void EnterShop();

private:
    PriceT money;
    IProduct::ProductMap products;
    PurchaseConfirmationType prefPCType;
    Shop &shop;
    CashRegister *cashRegister = nullptr;
    bool inShop = true;
};

struct IQuestion
{
    virtual std::string what() const = 0;
};

struct QuestionItemPrice: IQuestion
{
    std::string what();
    int itemId;
};

struct QuestionItemName: IQuestion
{
    std::string what();
    int itemId;
};

struct QuestionItemCategory: IQuestion
{
    std::string what();
    int itemId;
};

struct QuestionManager: IQuestion
{
    std::string what();
};

struct QuestionWorkerInfo: IQuestion
{
    std::string what();
};

struct QuestionShopPhoneNumber: IQuestion
{
    std::string what();
};
