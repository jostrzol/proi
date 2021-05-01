#pragma once

#include <unordered_map>
#include <string>
#include <iostream>

#include "product.h"
#include "entity.h"

class CashRegister;

class Receipt : public Entity
{
public:
    Receipt(const CashRegister *cr = nullptr, int id = -1);
    Receipt(IProduct::ProductMap products_, const CashRegister *cr = nullptr, int id = -1);
    Receipt(const Receipt &receipt);
    Receipt(Receipt &&receipt) noexcept;

    Receipt &operator=(const Receipt &other);
    Receipt &operator=(Receipt &&other);
    friend std::ostream &operator<<(std::ostream &os, const Receipt &receipt);

    void SetProductAmount(const IProduct &product, double amount);
    void RemoveProduct(const IProduct &product);
    std::size_t Size() const;
    PriceT PriceNetto(const IProduct &product) const;
    PriceT PriceBrutto(const IProduct &product) const;
    PriceT Tax(const IProduct &product) const;

    PriceT TotalPriceNetto() const;
    PriceT TotalPriceBrutto() const;
    PriceT TotalTax() const;

    const CashRegister *FromCashRegister() const;
    void SetFromCashRegister(const CashRegister *newCashRegister);

    std::string FullID() const;

protected:
    virtual const std::string stringHead() const;
    virtual const std::string stringRow(const std::pair<const IProduct *, double> &pair, std::size_t index) const;
    virtual const std::string stringTail() const;

private:
    IProduct::ProductMap products;
    const CashRegister *cashRegister;
};