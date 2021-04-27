#include <iostream>
#include <iomanip>
#include "receipt.h"
#include "sstream"

Receipt::Receipt(int id) : Entity(id) {}
Receipt::Receipt(const Receipt &receipt) : Entity(receipt.ID()), products(receipt.products) {}
Receipt::Receipt(Receipt &&receipt) noexcept
    : Entity(receipt.ID())
{
    products.swap(receipt.products); // can use the old products map instead of making a new one
}

Receipt &Receipt::operator=(const Receipt &other)
{
    SetID(other.ID());
    products = other.products;
    return *this;
}
Receipt &Receipt::operator=(Receipt &&other)
{
    SetID(other.ID());
    products.swap(other.products);
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Receipt &receipt)
{
    const auto &flags = os.flags();

    os << receipt.stringHead();

    std::size_t i = 1;
    for (const auto &pair : receipt.products)
    {
        os << "\t" << std::setw(2) << i << receipt.stringRow(pair);
    }

    os << "\t" << receipt.stringTail();

    os.flags(flags);
    return os;
}
void Receipt::SetItemAmount(const IProduct &product, double amount)
{
    if (amount == 0)
        products.erase(&product);
    else
        products[&product] = amount;
}
void Receipt::RemoveItem(const IProduct &product) { products.erase(&product); }
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

const std::string Receipt::stringHead() const
{
    std::stringstream ss;
    ss << "Receipt no. " << ID() << "\n";
    return ss.str();
}

const std::string Receipt::stringRow(const std::pair<const IProduct *, double> &pair) const
{
    std::stringstream ss;

    const auto &product = *(pair.first);
    const auto &amount = pair.second;

    ss << std::setw(20) << std::left << product.Name() << " "
       << std::setw(6) << std::setprecision(5) << std::right << amount << " "
       << std::setw(4) << std::left << product.Unit() << " | "
       << std::setw(7) << std::right << product.PriceBrutto(amount) << "\n";

    return ss.str();
}

const std::string Receipt::stringTail() const
{
    std::stringstream ss;
    ss << std::setw(39) << std::left << "TAX: " << std::setw(7) << std::right << TotalTax() << "\n";
    ss << std::setw(39) << std::left << "TOTAL: " << std::setw(7) << std::right << TotalPriceBrutto() << "\n";
    return ss.str();
}