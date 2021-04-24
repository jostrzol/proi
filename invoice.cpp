#include <iostream>
#include <iomanip>
#include "invoice.h"

int Invoice::nextId = 0;

Invoice::Invoice(Contractor &seller, Contractor &buyer)
    : id(nextId++), seller(&seller), buyer(&buyer) {}
Invoice::Invoice(const Invoice &invoice)
    : id(nextId++), seller(invoice.seller), buyer(invoice.buyer), items(invoice.items) {}
Invoice::Invoice(Invoice &&invoice) noexcept
    : id(invoice.id), seller(invoice.seller), buyer(invoice.buyer)
{
    items.swap(invoice.items); // can use the old items map instead of making a new one
}

Invoice &Invoice::operator=(const Invoice &other)
{
    id = nextId++;
    seller = other.seller;
    buyer = other.buyer;
    items = other.items;
    return *this;
}
Invoice &Invoice::operator=(Invoice &&other)
{
    id = other.id;
    seller = other.seller;
    buyer = other.buyer;
    items.swap(other.items);
    return *this;
}
bool Invoice::operator==(const Invoice &other)
{
    return id == other.id;
}
bool Invoice::operator!=(const Invoice &other)
{
    return id != other.id;
}
std::ostream &operator<<(std::ostream &os, const Invoice &invoice)
{
    const auto &flags = os.flags();
    os << "Invoice no. " << invoice.id << " [" << invoice.seller->Name() << " -> " << invoice.buyer->Name() << "]:" << std::endl;
    std::size_t i = 1;
    for (const auto &pair : invoice.items)
    {
        Item item = pair.first;
        double amount = pair.second;
        PriceT price = item.PriceBrutto(amount);
        os << "\t"
           << std::setw(2) << std::right << i << ". "
           << std::setw(20) << std::left << item.Name() << " "
           << std::setw(6) << std::setprecision(5) << std::right << amount << " "
           << std::setw(4) << std::left << item.Unit() << " | "
           << std::setw(7) << std::right << price << std::endl;
        i++;
    }
    os << "\t" << std::setw(39) << std::left << "TAX: " << std::setw(7) << std::right << invoice.TotalTax() << std::endl;
    os << "\t" << std::setw(39) << std::left << "TOTAL: " << std::setw(7) << std::right << invoice.TotalPriceBrutto() << std::endl;
    os.flags(flags);
    return os;
}

Contractor &Invoice::Seller() { return *seller; }
void Invoice::SetSeller(Contractor &val) { seller = &val; }

Contractor &Invoice::Buyer() { return *buyer; }
void Invoice::SetBuyer(Contractor &val) { buyer = &val; }

void Invoice::SetItemAmount(Item item, double amount)
{
    if (amount == 0)
        items.erase(item);
    else
        items[item] = amount;
}
void Invoice::RemoveItem(Item item) { items.erase(item); }
std::size_t Invoice::Size() const
{
    return items.size();
}
PriceT Invoice::PriceNetto(Item item) const { return item.PriceNetto(items.at(item)); }

PriceT Invoice::PriceBrutto(Item item) const { return item.PriceBrutto(items.at(item)); }

PriceT Invoice::Tax(Item item) const { return item.Tax(items.at(item)); }

PriceT Invoice::TotalPriceNetto() const
{
    PriceT total = 0;
    for (const auto &pair : items)
    {
        Item item = pair.first;
        double amount = pair.second;
        total += item.PriceNetto(amount);
    }
    return total;
}

PriceT Invoice::TotalPriceBrutto() const
{
    PriceT total = 0;
    for (const auto &pair : items)
    {
        Item item = pair.first;
        double amount = pair.second;
        total += item.PriceBrutto(amount);
    }
    return total;
}

PriceT Invoice::TotalTax() const
{
    PriceT total = 0;
    for (const auto &pair : items)
    {
        Item item = pair.first;
        double amount = pair.second;
        total += item.Tax(amount);
    }
    return total;
}