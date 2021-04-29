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
        Receipt r(std::move(buyer.Products()), cr->Receipts().size());
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
        Invoice i(std::move(buyer.Products()), cr->Seller(), &buyer, cr->Receipts().size());
        if (buyer.Pay(i.TotalPriceBrutto()))
        {
            cr->AddReceipt(std::move(i));
            return true;
        }
        else
            return false;
    }
    default:
        return false;
    }
}
