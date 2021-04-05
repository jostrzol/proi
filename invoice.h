#ifndef INVOICE_H
#define INVOICE_H

#include <unordered_map>
#include <string>
#include <iostream>

#include "item.h"
#include "contractor.h"

class Invoice
{
public:
    Invoice(Contractor &seller, Contractor &buyer);
    Invoice(const Invoice &invoice);
    ~Invoice();
    Invoice &operator=(const Invoice &other);
    bool operator==(const Invoice &other);
    bool operator!=(const Invoice &other);
    friend std::ostream &operator<<(std::ostream &os, const Invoice &invoice);

    Contractor &Seller();
    void SetSeller(const Contractor &val);

    Contractor &Buyer();
    void SetBuyer(const Contractor &val);

    void SetItemAmount(Item item, double amount);
    void RemoveItem(Item item);
    PriceT Price(Item item) const;
    PriceT TotalPrice() const;

private:
    static int nextId;
    std::string id;

    Contractor &seller;
    Contractor &buyer;

    bool itemEqual(Item first, Item second);
    std::size_t itemHash(Item item);
    typedef std::unordered_map<Item, double, decltype(itemHash), decltype(itemEqual)> ItemMap;
    ItemMap &items;
};

#endif