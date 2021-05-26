#pragma once

#include <unordered_map>
#include <string>
#include <iostream>

#include "product.h"
#include "entity.h"

class CashRegister;

class Receipt : public virtual Entity
{
public:
    Receipt(int id = -1, const CashRegister *cr = nullptr);
    Receipt(IProduct::ProductMap products_, int id = -1, const CashRegister *cr = nullptr);
    Receipt(const Receipt &receipt);
    Receipt(Receipt &&receipt) noexcept;

    Receipt &operator=(const Receipt &other);
    Receipt &operator=(Receipt &&other);
    friend std::ostream &operator<<(std::ostream &os, const Receipt &receipt);

    // Sets the amount of the given product on the receipt
    void SetProductAmount(const IProduct &product, double amount);
    // Removes a product from the receipt
    void RemoveProduct(const IProduct &product);
    // Returns the number of different products on the receipt
    std::size_t Size() const;
    // Returns price netto for the given product on the receipt
    PriceT PriceNetto(const IProduct &product) const;
    // Returns price brutto for the given product on the receipt
    PriceT PriceBrutto(const IProduct &product) const;
    // Returns tax for the given product on the receipt
    PriceT Tax(const IProduct &product) const;

    // Returns price netto of the entire receipt
    PriceT TotalPriceNetto() const;
    // Returns price brutto of the entire receipt
    PriceT TotalPriceBrutto() const;
    // Returns tax of the entire receipt
    PriceT TotalTax() const;

    // Returns the cash register that generated this receipt
    const CashRegister *GetCashRegister() const;
    // Sets the cash register that generated this receipt
    void SetCashRegister(const CashRegister *newCashRegister);

    // Returns the full ID of this receipt in format <ReceiptID>/<CashRegisterID>
    std::string FullID() const;

protected:
    // Returns the string to print on the beginning of the receipt
    virtual const std::string stringHead() const;
    // Returns the string to print for the given product
    virtual const std::string stringRow(const std::pair<const IProduct *, double> &pair, std::size_t index) const;
    // Returns the string to print at the end of the receipt
    virtual const std::string stringTail() const;

private:
    IProduct::ProductMap products;
    const CashRegister *cashRegister;
};
