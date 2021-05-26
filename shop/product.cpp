
#include "product.h"

PriceT IProduct::PriceBrutto(double amount) const
{
    return PriceNetto(amount) + Tax(amount);
}
