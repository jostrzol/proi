#include <memory>

#include "cash_worker.h"
#include "buyer.h"

bool ICashWorker::ServeNext()
{
    CashRegister *cr = AssignedCashRegister();
    if (cr == nullptr || cr->QueueEmpty())
        return false;
    IBuyer &buyer = cr->QueuePop();

    switch (buyer.PCType())
    {
    case PCReceipt:
    {
        Receipt r(buyer.Products(), cr, cr->Receipts().size());
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
        Invoice i(buyer.Products(), cr->Seller(), &buyer, cr, cr->Invoices().size());
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
