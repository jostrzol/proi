#pragma once
#include <iostream>

class Product{
public:
	Product(std::string nm="", float prc_ntt=0, float tx=-1);
	std::string name;
	float price_netto;
	float price_brutto;
	float tax;
	bool operator==(const Product& product);
	bool operator!=(const Product& product);
	friend std::ostream& operator<<(std::ostream& os, const Product& product);
};
