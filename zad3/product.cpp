#include <iostream>

#include "product.h"

using namespace std;

Product::Product(std::string nm, float prc_ntt, float tx){
	name = nm;
	price_netto = prc_ntt;
	tax = tx;
	price_brutto = prc_ntt * (1 + tx); // lista inicjalizacyjna
}

bool Product::operator==(const Product& product){
	if(product.name != name){
		return false;
	} else if(product.price_netto != price_netto){
		return false;
	} else if(product.tax != tax){
		return false;
	}
	return true;
}

bool Product::operator!=(const Product& product){
	return !(*this == product);
}

std::ostream& operator<<(std::ostream& os, const Product& product){
	os << "Nazwa produktu: " << product.name << ", ";
	os << "Cena netto: " << product.price_netto << ", ";
	os << "Cena brutto: " << product.price_brutto << ", ";
	os << "Podatek: " << product.tax;
	return os;
}
