#pragma once

#include <vector>
#include <queue>
#include <exception>

#include "buyer.h"
#include "cash_worker.h"
#include "invoice.h"

class Shop;

class CashRegister : public virtual Entity
{
public:
    CashRegister(Shop &shop, int id = -1);

    // Get all the invoices genereted by this cash register
    const std::vector<Invoice> &GetInvoices() const;
    // Get all the receipts genereted by this cash register
    const std::vector<Receipt> &GetReceipts() const;

    // Add an invoice to the cash register
    void AddInvoice(Invoice invoice);
    // Add a receipt to the cash register
    void AddReceipt(Receipt receipt);

    // Push a buyer to the cash register's queue
    void QueuePush(IBuyer &buyer);
    // Pop a buyer from the cash register's queue
    IBuyer *QueuePop();
    // Return the cash register's queue size
    std::size_t QueueSize() const;
    // Check if the cash register's queue is empty
    bool QueueEmpty() const;

    // Returns the amount of money stored in the cash register
    PriceT GetMoney() const;
    // Returns the amount of money stored in the cash register and clears it
    PriceT ClearMoney();
    // Deposits money to the cash register
    void DepositMoney(PriceT val);

    // Assigns a worker to the cash register
    void AssignWorker(const ICashWorker *newWorker);
    // Returns the worker managing this cash register
    const ICashWorker *GetWorker();
    // Returns the worker managing this cash register and frees him
    const ICashWorker *FreeWorker();

    // Returns the shop that this cash register belongs to
    Shop &GetShop() const;

private:
    PriceT money;

    std::queue<IBuyer *> buyerQueue;
    std::vector<Receipt> receipts;
    std::vector<Invoice> invoices;

    const ICashWorker *worker;

    Shop &shop;
};