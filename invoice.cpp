#include <iostream>
#include <iomanip>
#include "invoice.h"

int Invoice::nextId = 0;

bool Invoice::ItemEqual::operator()(const Item &first, const Item &second) const { return first.Name() == second.Name(); }
std::size_t Invoice::ItemHasher::operator()(const Item &item) const { return std::hash<std::string>()(item.Name()); };

Invoice::Invoice(Contractor &seller, Contractor &buyer)
    : seller(seller), buyer(buyer) { id = std::to_string(nextId++); }
Invoice::Invoice(const Invoice &invoice)
    : seller(invoice.seller), buyer(invoice.buyer), items(invoice.items) //want to copy the items map, not reference the old one
{
    id = std::to_string(nextId++); //want a new id
}
Invoice::Invoice(Invoice &&invoice) noexcept
    : id(invoice.id), seller(invoice.seller), buyer(invoice.buyer)
{
    items.swap(invoice.items);
}

Invoice &Invoice::operator=(const Invoice &other)
{
    if (id == "")
        id = nextId++;
    seller = other.seller;
    buyer = other.buyer;
    items = other.items;
    return *this;
};
Invoice &Invoice::operator=(Invoice &&other)
{
    id = other.id;
    seller = other.seller;
    buyer = other.buyer;
    items.swap(other.items);
    return *this;
};
bool Invoice::operator==(const Invoice &other)
{
    return id == other.id;
};
bool Invoice::operator!=(const Invoice &other)
{
    return id != other.id;
};
std::ostream &operator<<(std::ostream &os, const Invoice &invoice)
{
    const auto &flags = os.flags();
    os << "Invoice no. " << invoice.id << " [" << invoice.seller.Name() << " -> " << invoice.buyer.Name() << "]:" << std::endl;
    std::size_t i = 1;
    for (const auto &pair : invoice.items)
    {
        Item item = pair.first;
        double amount = pair.second;
        PriceT price = item.Price(amount);
        os << "\t"
           << std::setw(2) << std::right << i << ". "
           << std::setw(20) << std::left << item.Name() << " "
           << std::setw(6) << std::setprecision(5) << std::right << amount << " "
           << std::setw(4) << std::left << item.Unit() << " | "
           << std::setw(7) << std::right << price << std::endl;
        i++;
    }
    os << "\t" << std::setw(39) << std::left << "TOTAL: " << std::setw(7) << std::right << invoice.TotalPrice() << std::endl;
    os.flags(flags);
    return os;
};

Contractor &Invoice::Seller() { return seller; }
void Invoice::SetSeller(const Contractor &val) { seller = val; }

Contractor &Invoice::Buyer() { return buyer; }
void Invoice::SetBuyer(const Contractor &val) { buyer = val; }

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
};
PriceT Invoice::Price(Item item) const { return item.Price(items.at(item)); }
PriceT Invoice::TotalPrice() const
{
    PriceT total = 0;
    for (const auto &pair : items)
    {
        Item item = pair.first;
        double amount = pair.second;
        total += item.Price(amount);
    }
    return total;
}