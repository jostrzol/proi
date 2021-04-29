#pragma once

#include <vector>
#include <queue>
#include "buyer.h"
#include "cash_worker.h"
#include "invoice.h"

class ICashWorker;

class CashRegister : public virtual Entity
{
public:
    CashRegister(const IContractor &seller, int id = -1);

    const std::vector<Invoice> &Invoices() const;
    const std::vector<Receipt> &Receipts() const;

    void AddInvoice(Invoice invoice);
    void AddReceipt(Receipt receipt);

    void QueuePush(IBuyer &buyer);
    IBuyer &QueuePop();
    bool QueueEmpty() const;

    PriceT Money() const;
    PriceT ClearMoney();
    void DepositMoney(PriceT val);

    void AssignWorker(const ICashWorker *newWorker);
    const ICashWorker *Worker();
    const ICashWorker *FreeWorker();

    void SetSeller(const IContractor *newSeller);
    const IContractor *Seller();

private:
    PriceT money;

    std::queue<IBuyer *> buyerQueue;
    std::vector<Receipt> receipts;
    std::vector<Invoice> invoices;

    const IContractor *seller;
    const ICashWorker *worker;
};