#include <iostream>
#include <iomanip>
#include <sstream>

#include "receipt.h"
#include "cash_register.h"

Receipt::Receipt(int id, const CashRegister *cr) : Entity(id), cashRegister(cr) {}
Receipt::Receipt(const Receipt &receipt) : Entity(receipt.GetID()), products(receipt.products), cashRegister(receipt.cashRegister) {}
Receipt::Receipt(Receipt &&receipt) noexcept
    : Entity(receipt.GetID())
{
    products.swap(receipt.products); // can use the old products map instead of making a new one
    cashRegister = receipt.cashRegister;
}

Receipt::Receipt(IProduct::ProductMap products_, int id, const CashRegister *cr)
    : Entity(id), products(std::move(products_)), cashRegister(cr) {}

Receipt &Receipt::operator=(const Receipt &other)
{
    if (this == &other)
        return *this;
    SetID(other.GetID());
    products = other.products;
    cashRegister = other.cashRegister;
    return *this;
}
Receipt &Receipt::operator=(Receipt &&other)
{
    SetID(other.GetID());
    products = std::move(other.products);
    cashRegister = other.cashRegister;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Receipt &receipt)
{
    const auto &flags = os.flags();

    os << receipt.stringHead();

    std::size_t i = 1;
    for (const auto &pair : receipt.products)
    {
        os << receipt.stringRow(pair, i);
        i++;
    }

    os << receipt.stringTail();

    os.flags(flags);
    return os;
}
void Receipt::SetProductAmount(const IProduct &product, double amount)
{
    if (amount == 0)
        products.erase(&product);
    else
        products[&product] = amount;
}
void Receipt::RemoveProduct(const IProduct &product) { products.erase(&product); }
std::size_t Receipt::Size() const { return products.size(); }
PriceT Receipt::PriceNetto(const IProduct &product) const { return product.PriceNetto(products.at(&product)); }
PriceT Receipt::PriceBrutto(const IProduct &product) const { return product.PriceBrutto(products.at(&product)); }
PriceT Receipt::Tax(const IProduct &product) const { return product.Tax(products.at(&product)); }

PriceT Receipt::TotalPriceNetto() const
{
    PriceT total = 0;
    for (const auto &pair : products)
    {
        const IProduct &product = *(pair.first);
        double amount = pair.second;
        total += product.PriceNetto(amount);
    }
    return total;
}

PriceT Receipt::TotalPriceBrutto() const
{
    PriceT total = 0;
    for (const auto &pair : products)
    {
        const IProduct &product = *(pair.first);
        double amount = pair.second;
        total += product.PriceBrutto(amount);
    }
    return total;
}

PriceT Receipt::TotalTax() const
{
    PriceT total = 0;
    for (const auto &pair : products)
    {
        const IProduct &product = *(pair.first);
        double amount = pair.second;
        total += product.Tax(amount);
    }
    return total;
}

const CashRegister *Receipt::GetCashRegister() const { return cashRegister; }

void Receipt::SetCashRegister(const CashRegister *newCashRegister) { cashRegister = newCashRegister; }

std::string Receipt::FullID() const
{
    std::stringstream ss;
    ss << GetID() << "/";
    if (cashRegister != nullptr)
        ss << cashRegister->GetID();
    else
        ss << "-";
    return ss.str();
}

const std::string Receipt::stringHead() const
{
    std::stringstream ss;
    ss << "Receipt no. " << FullID() << ":\n";
    return ss.str();
}

const std::string Receipt::stringRow(const std::pair<const IProduct *, double> &pair, std::size_t index) const
{
    std::stringstream ss;

    const auto &product = *(pair.first);
    const auto &amount = pair.second;

    ss << "\t" << std::setw(2) << index << ". ";

    ss << std::setw(20) << std::left << product.GetName() << " "
       << std::setw(6) << std::setprecision(5) << std::right << amount << " "
       << std::setw(4) << std::left << product.GetUnit() << " | "
       << std::setw(7) << std::right << product.PriceBrutto(amount) << "\n";

    return ss.str();
}

const std::string Receipt::stringTail() const
{
    std::stringstream ss;
    ss << "\t" << std::setw(39) << std::left << "TAX: " << std::setw(7) << std::right << TotalTax() << "\n";
    ss << "\t" << std::setw(39) << std::left << "TOTAL: " << std::setw(7) << std::right << TotalPriceBrutto() << "\n";
    return ss.str();
}