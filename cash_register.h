#pragma once
#include <iostream>
#include <vector>

class Person{
public:
	Person(std:: string frst_nm="", std::string lst_nm="", int prsn_id=-1);
	std::string first_name;
	std::string last_name;
	int id;
	bool operator==(const Person& person);
	bool operator!=(const Person& person);
	friend std::ostream& operator<<(std::ostream& os, const Person& person);
};

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

class Queue{
private:
	int size_;
	std::vector<Person> queue_;
public:
	Queue();
	int size();
	std::vector<Person> queue();
	void push(const Person client);
	void pop();
	void switch_places(int index1, int index2);
	Queue operator+(const Queue& queue);
	Queue& operator+=(const Queue& queue);
	bool operator==(const Queue& queue);
	bool operator!=(const Queue& queue);
	Person operator[](const int& id);
	friend std::ostream& operator<<(std::ostream& os, const Queue& queue);
};

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
