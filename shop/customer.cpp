#include "customer.h"
#include "shop.h"
#include "cash_register.h"

Customer::Customer(Shop &shop, int id, std::string name, std::string address, std::string phone, PriceT money)
    : Entity(id), Person(id, name, address, phone), money(money), prefPCType(PCReceipt), shop(shop) {}

const IProduct::ProductMap &Customer::GetProducts() const { return products; }

void Customer::ClearProducts()
{
    products.clear();
}

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
    double taken = shop.TakeItem(product.GetID(), amount);
    if (taken != 0)
        products[&product] += taken;
    return taken;
}

bool Customer::LeaveProduct(const IProduct &product)
{
    double amount = GetProductAmount(product);
    if (shop.DepositItem(product.GetID(), amount))
    {
        products.erase(&product);
        return true;
    }
    return false;
}

void Customer::JoinQueue(CashRegister &cr)
{
    if (&cr.GetShop() != &shop)
        return;
    cashRegister = &cr;
    cr.QueuePush(*this);
}

CashRegister *Customer::GetCashRegister()
{
    return cashRegister;
}

CashRegister *Customer::DeassignCashRegister()
{
    auto tmp = cashRegister;
    cashRegister = nullptr;
    return tmp;
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

bool Customer::IsInShop() const
{
    return inShop;
}

void Customer::LeaveShop()
{
    // have to use ordinary for loop for erasing
    for (auto it = products.begin(); it != products.end();)
    {
        auto &pair = *it++;
        auto &product = *pair.first;

        LeaveProduct(product);
    }
    inShop = false;
}

void Customer::EnterShop()
{
    inShop = true;
}

QuestionItemPrice::QuestionItemPrice(int itemId): itemId(itemId){}

std::string QuestionItemPrice::what() const
{
    return "	What's the price of this product?\n";
}

QuestionItemName::QuestionItemName(int itemId): itemId(itemId){}

std::string QuestionItemName::what() const
{
    return "	What's the name of this product?\n";
}

QuestionItemCategory::QuestionItemCategory(int itemId): itemId(itemId){}

std::string QuestionItemCategory::what() const
{
    return "	What's the category of this product?\n";
}

QuestionManager::QuestionManager(){}

std::string QuestionManager::what() const
{
    return "	Who is the manager of this shop?\n";
}

QuestionWorkerInfo::QuestionWorkerInfo(){}

std::string QuestionWorkerInfo::what() const
{
    return "	Could you please tell me your credentials?\n";
}

QuestionShopPhoneNumber::QuestionShopPhoneNumber(){}

std::string QuestionShopPhoneNumber::what() const
{
    return "	Could you please tell me this shop's phone number?\n";
}
