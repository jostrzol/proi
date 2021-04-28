
#include "product.h"

PriceT IProduct::PriceBrutto(double amount) const
{
    return PriceNetto(amount) + Tax(amount);
}
std::size_t IProduct::PtrHash::operator()(const IProduct *product) const
{
    return std::hash<Entity>()(*product);
}
bool IProduct::PtrEqualTo::operator()(const IProduct *first, const IProduct *second) const
{
    return *first == *second;
}