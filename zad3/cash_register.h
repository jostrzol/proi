#pragma once
#include <iostream>
#include <vector>

#include "product.h"
#include "person.h"
#include "queue.h"

class CashRegister{
private:
	int id_;
	std::string location_;
	Person cashier_;
	Queue queue_;
	std::vector<Product> bill_;
	std::string status_;
public:
	CashRegister();
	int id();
	void change_id(int new_id);
	Queue queue();
	void change_queue(Queue new_queue);
	std::string location();
	void change_location(std::string new_location);
	Person cashier();
	void change_cashier(Person new_cashier);
	std::vector<Product> bill();
	void change_bill(std::vector<Product> new_bill);
	std::string status();
	void change_status(bool is_open);
	bool operator==(const CashRegister& cash_register);
	bool operator!=(const CashRegister& cash_register);
	std::ostream& operator<<(const CashRegister& cash_register);
};
