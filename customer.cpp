#include "customer.h"
#include "shop.h"

Customer::Customer(std::string name, std::string address, std::string phone, int id, PriceT money)
    : Person(name, address, phone, id), money(money), prefPCType(PCReceipt) {}

const IProduct::ProductMap &Customer::GetProducts() const { return products; }

void Customer::SetProductAmount(const IProduct &product, double amount)
{
    if (amount == 0)
        products.erase(&product);
    else
        products[&product] = amount;
}

double Customer::GetProductAmount(const IProduct &product) const
{
    return products.at(&product);
}

void Customer::SetMoney(PriceT newMoney) { money = newMoney; }

PriceT Customer::GetMoney() const { return money; }

bool Customer::Pay(PriceT price)
{
    if (price > money)
        return false;
    money -= price;
    return true;
}

PurchaseConfirmationType Customer::GetPCType() const { return prefPCType; }

void Customer::SetPCType(PurchaseConfirmationType newPCType) { prefPCType = newPCType; }

void Customer::SetShop(Shop *newShop) { shop = newShop; }

Shop *Customer::GetShop() const { return shop; }
