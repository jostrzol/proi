#include "cash_register.h"
#include "shop.h"

CashRegister::CashRegister(Shop &shop, int id) : Entity(id), worker(nullptr), shop(shop) {}

const std::vector<Invoice> &CashRegister::GetInvoices() const { return invoices; }

const std::vector<Receipt> &CashRegister::GetReceipts() const { return receipts; }

void CashRegister::AddInvoice(Invoice invoice) { invoices.push_back(std::move(invoice)); }

void CashRegister::AddReceipt(Receipt receipt) { receipts.push_back(std::move(receipt)); }

void CashRegister::QueuePush(IBuyer &buyer) { buyerQueue.push(&buyer); }

IBuyer *CashRegister::QueuePop()
{
    if (buyerQueue.empty())
        return nullptr;
    IBuyer *tmp = buyerQueue.front();
    tmp->DeassignCashRegister();
    buyerQueue.pop();
    return tmp;
}

std::size_t CashRegister::QueueSize() const
{
    return buyerQueue.size();
}

bool CashRegister::QueueEmpty() const { return buyerQueue.empty(); }

PriceT CashRegister::GetMoney() const { return money; }

PriceT CashRegister::ClearMoney()
{
    PriceT tmp = money;
    money = 0;
    return tmp;
}

void CashRegister::DepositMoney(PriceT val) { money += val; }

void CashRegister::AssignWorker(const ICashWorker *newWorker) { worker = newWorker; }

const ICashWorker *CashRegister::GetWorker()
{
    return worker;
}

const ICashWorker *CashRegister::FreeWorker()
{
    const ICashWorker *tmp = worker;
    worker = nullptr;
    while (!buyerQueue.empty())
    {
        buyerQueue.front()->DeassignCashRegister();
        buyerQueue.pop();
    }
    return tmp;
}

Shop &CashRegister::GetShop() const
{
    return shop;
}
