#pragma once

#include <vector>
#include <queue>
#include "buyer.h"
#include "cash_worker.h"
#include "invoice.h"
#include "receipt.h"
#include "units.h"

class CashRegister : public Entity
{
public:
    CashRegister(int id = -1);

    const std::vector<Invoice> &Invoices() const;
    const std::vector<Receipt> &Receipts() const;

    void AddInvoice(Invoice invoice);
    void AddReceipt(Receipt invoice);

    void PutInQueue(IBuyer &buyer);

    PriceT Money() const;
    PriceT ClearMoney();
    void DepositMoney(PriceT money);

    void AssignWorker(const ICashWorker &worker);
    const ICashWorker &FreeWorker();

private:
    PriceT money;

    std::queue<IBuyer *> buyerQueue;
    std::vector<Receipt> receipts;
    std::vector<Invoice> invoices;
};