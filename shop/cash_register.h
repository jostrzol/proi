#pragma once

#include <vector>
#include <queue>
#include "buyer.h"
#include "cash_worker.h"
#include "invoice.h"

class ICashWorker;
class Invoice;
class Receipt;
class Shop;

class CashRegister : public Entity
{
public:
    CashRegister(Shop &shop, int id = -1);

    const std::vector<Invoice> &GetInvoices() const;
    const std::vector<Receipt> &GetReceipts() const;

    void AddInvoice(Invoice invoice);
    void AddReceipt(Receipt receipt);

    void QueuePush(IBuyer &buyer);
    IBuyer &QueuePop();
    bool QueueEmpty() const;

    PriceT GetMoney() const;
    PriceT ClearMoney();
    void DepositMoney(PriceT val);

    void AssignWorker(const ICashWorker *newWorker);
    const ICashWorker *GetWorker();
    const ICashWorker *FreeWorker();

    Shop &GetShop() const;

private:
    PriceT money;

    std::queue<IBuyer *> buyerQueue;
    std::vector<Receipt> receipts;
    std::vector<Invoice> invoices;

    const ICashWorker *worker;

    Shop &shop;
};