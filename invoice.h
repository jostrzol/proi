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
    Invoice(Invoice &&invoice) noexcept;

    Invoice &operator=(const Invoice &other);
    Invoice &operator=(Invoice &&other);
    bool operator==(const Invoice &other);
    bool operator!=(const Invoice &other);
    friend std::ostream &operator<<(std::ostream &os, const Invoice &invoice);

    Contractor &Seller();
    void SetSeller(Contractor &val);

    Contractor &Buyer();
    void SetBuyer(Contractor &val);

    void SetItemAmount(Item item, double amount);
    void RemoveItem(Item item);
    std::size_t Size() const;
    PriceT Price(Item item) const;
    PriceT TotalPrice() const;

private:
    struct ItemHasher
    {
        std::size_t operator()(const Item &item) const;
    };
    struct ItemEqual
    {
        bool operator()(const Item &first, const Item &second) const;
    };

    static int nextId;
    std::string id;

    Contractor *seller;
    Contractor *buyer;

    typedef std::unordered_map<Item, double> ItemMap;
    ItemMap items;
};

#endif