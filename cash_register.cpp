#include "cash_register.h"

CashRegister::CashRegister(const IContractor &seller, int id) : Entity(id), seller(&seller) {}

const std::vector<Invoice> &CashRegister::Invoices() const { return invoices; }

const std::vector<Receipt> &CashRegister::Receipts() const { return receipts; }

void CashRegister::AddInvoice(Invoice invoice) { invoices.push_back(std::move(invoice)); }

void CashRegister::AddReceipt(Receipt receipt) { receipts.push_back(std::move(receipt)); }

void CashRegister::QueuePush(IBuyer &buyer) { buyerQueue.push(&buyer); }

IBuyer &CashRegister::QueuePop()
{
    IBuyer &tmp = *(buyerQueue.front());
    buyerQueue.pop();
    return tmp;
}

bool CashRegister::QueueEmpty() const { return buyerQueue.empty(); }

PriceT CashRegister::Money() const { return money; }

PriceT CashRegister::ClearMoney()
{
    PriceT tmp = money;
    money = 0;
    return tmp;
}

void CashRegister::DepositMoney(PriceT val) { money += val; }

void CashRegister::AssignWorker(const ICashWorker *newWorker) { worker = newWorker; }

const ICashWorker *CashRegister::Worker()
{
    return worker;
}

const ICashWorker *CashRegister::FreeWorker()
{
    const ICashWorker *tmp = worker;
    worker = nullptr;
    return tmp;
}

void CashRegister::SetSeller(const IContractor *newSeller)
{
    seller = newSeller;
}

const IContractor *CashRegister::Seller()
{
    return seller;
}
