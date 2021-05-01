#include "customer.h"

Customer::Customer(std::string name, std::string address, std::string phone, int id, PriceT money)
    : Person(name, address, phone, id), money(money), prefPCType(PCReceipt) {}

const IProduct::ProductMap &Customer::Products() const { return products; }

void Customer::SetProductAmount(const IProduct &product, double amount)
{
    if (amount == 0)
        products.erase(&product);
    else
        products[&product] = amount;
}

double Customer::ProductAmount(const IProduct &product) const
{
    return products.at(&product);
}

void Customer::SetMoney(PriceT newMoney) { money = newMoney; }

PriceT Customer::Money() const { return money; }

bool Customer::Pay(PriceT price)
{
    if (price > money)
        return false;
    money -= price;
    return true;
}

PurchaseConfirmationType Customer::PCType() const { return prefPCType; }

void Customer::SetPreferredPCType(PurchaseConfirmationType newPCType) { prefPCType = newPCType; }
