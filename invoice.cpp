#include <iostream>
#include <iomanip>
#include "invoice.h"

int Invoice::nextId = 0;

bool Invoice::itemEqual(Item first, Item second) { return first.Name() == second.Name(); }
std::size_t Invoice::itemHash(Item item) { return std::hash<std::string>()(item.Name()); };

Invoice::Invoice(Contractor &seller, Contractor &buyer)
    : seller(seller), buyer(buyer), items(*new Invoice::ItemMap{}) { id = nextId++; }
Invoice::Invoice(const Invoice &invoice)
    : seller(invoice.seller), buyer(invoice.buyer), items(*new std::unordered_map<Item, double, decltype(Invoice::itemHash), decltype(Invoice::itemEqual)>{})
{
    id = nextId++;         //want a new id
    items = invoice.items; //want to copy the items map, not reference the old one
}
Invoice::~Invoice()
{
    delete &items;
}
Invoice &Invoice::operator=(const Invoice &other)
{
    if (id == "")
        id = nextId++;
    seller = other.seller;
    buyer = other.buyer;
    items = other.items;
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
    os << "Invoice no. " << invoice.id << " [" << invoice.seller.Name() << " -> " << invoice.buyer.Name() << "]:" << std::endl;
    std::size_t i = 1;
    for (const auto &pair : invoice.items)
    {
        Item item = pair.first;
        double amount = pair.second;
        PriceT price = item.Price(amount);
        os << std::setw(2) << i << ". "
           << std::setw(20) << std::left << item.Name() << " "
           << std::setw(5) << std::setprecision(5) << amount << " "
           << std::setw(4) << std::left << item.Unit() << " "
           << price << std::endl;
    }
    os << "TOTAL: " << invoice.TotalPrice() << std::endl;
    return os;
};

Contractor &Invoice::Seller() { return seller; }
void Invoice::SetSeller(const Contractor &val) { seller = val; }

Contractor &Invoice::Buyer() { return buyer; }
void Invoice::SetBuyer(const Contractor &val) { buyer = val; }

void Invoice::SetItemAmount(Item item, double amount)
{
    items[item] = amount;
}
void Invoice::RemoveItem(Item item) { items.erase(item); }
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