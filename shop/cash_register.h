#pragma once

#include <vector>
#include <queue>
#include "buyer.h"
#include "cash_worker.h"
#include "invoice.h"

class ICashWorker;
class Invoice;
class Receipt;

class CashRegister : public virtual Entity
{
public:
    CashRegister(int id = -1, const IContractor *seller = nullptr);

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

    void SetSeller(const IContractor *newSeller);
    const IContractor *GetSeller();

private:
    PriceT money;

    std::queue<IBuyer *> buyerQueue;
    std::vector<Receipt> receipts;
    std::vector<Invoice> invoices;

    const IContractor *seller;
    const ICashWorker *worker;
};