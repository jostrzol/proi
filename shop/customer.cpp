#include "customer.h"
#include "shop.h"

Customer::Customer(Shop &shop, int id, std::string name, std::string address, std::string phone, PriceT money)
    : Entity(id), Person(id, name, address, phone), money(money), prefPCType(PCReceipt), shop(shop) {}

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
    try
    {
        return products.at(&product);
    }
    catch (std::out_of_range &)
    {
        return 0;
    }
}

double Customer::TakeProduct(const IProduct &product, double amount)
{
    auto item = shop.GetItem(product.GetID());
    if (amount > item.second)
    {
        SetProductAmount(product, item.second);
        shop.SetItemAmount(item.first->GetID(), 0);
        return item.second;
    }
    SetProductAmount(product, amount);
    shop.SetItemAmount(item.first->GetID(), item.second - amount);
    return amount;
}

void Customer::LeaveProduct(const IProduct &product)
{
    double amount = GetProductAmount(product);
    SetProductAmount(product, 0);
    auto item = shop.GetItem(product.GetID());
    shop.SetItemAmount(item.first->GetID(), item.second + amount);
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

Shop &Customer::GetShop() const
{
    return shop;
}