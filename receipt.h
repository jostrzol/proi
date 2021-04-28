#pragma once

#include <unordered_map>
#include <string>
#include <iostream>

#include "product.h"
#include "entity.h"

class Receipt : public Entity
{
public:
    Receipt(int id = -1);
    Receipt(const Receipt &receipt);
    Receipt(Receipt &&receipt) noexcept;

    Receipt &operator=(const Receipt &other);
    Receipt &operator=(Receipt &&other);
    friend std::ostream &operator<<(std::ostream &os, const Receipt &receipt);

    void SetItemAmount(const IProduct &product, double amount);
    void RemoveItem(const IProduct &product);
    std::size_t Size() const;
    PriceT PriceNetto(const IProduct &product) const;
    PriceT PriceBrutto(const IProduct &product) const;
    PriceT Tax(const IProduct &product) const;

    PriceT TotalPriceNetto() const;
    PriceT TotalPriceBrutto() const;
    PriceT TotalTax() const;

protected:
    virtual const std::string stringHead() const;
    virtual const std::string stringRow(const std::pair<const IProduct *, double> &pair, std::size_t index) const;
    virtual const std::string stringTail() const;

private:
    IProduct::ProductMap products;
};