#include <memory>

#include "cash_worker.h"
#include "buyer.h"

bool ICashWorker::ServeNext()
{
    CashRegister *cr = GetCashRegister();
    if (cr == nullptr || cr->QueueEmpty())
        return false;
    IBuyer &buyer = cr->QueuePop();

    switch (buyer.GetPCType())
    {
    case PCReceipt:
    {
        Receipt r(buyer.GetProducts(), cr->GetReceipts().size(), cr);
        if (buyer.Pay(r.TotalPriceBrutto()))
        {
            cr->AddReceipt(std::move(r));
            return true;
        }
        else
            return false;
    }
    case PCInvoice:
    {
        Invoice i(buyer.GetProducts(), cr->GetInvoices().size(), cr->GetSeller(), &buyer, cr);
        if (buyer.Pay(i.TotalPriceBrutto()))
        {
            cr->AddInvoice(std::move(i));
            return true;
        }
        else
            return false;
    }
    default:
        return false;
    }
}
