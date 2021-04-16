#include "cash_register.h"
#include <iostream>
#include <vector>

using namespace std;

CashRegister::CashRegister(){
	int id_;
	string location_;
	Person cashier_;
	Queue queue_;
	vector<Product> bill_;
	string status_;
}

int CashRegister::id(){
	return id_;
}

void CashRegister::change_id(int new_id){
	id_ = new_id; // pola statyczne
}

Queue CashRegister::queue(){
	return queue_;
}

void CashRegister::change_queue(Queue new_queue){
	queue_ = new_queue;
}

string CashRegister::location(){
	return location_;
}

void CashRegister::change_location(std::string new_location){
	location_ = new_location;
}

Person CashRegister::cashier(){
	return cashier_;
}

void CashRegister::change_cashier(Person new_cashier){
	cashier_ = new_cashier;
}

vector<Product> CashRegister::bill(){
	return bill_;
}

void CashRegister::change_bill(std::vector<Product> new_bill){
	bill_ = new_bill; // referencje
}

string CashRegister::status(){
	return status_;
}

void CashRegister::change_status(bool is_open){
	if(is_open){
		status_ = "Open";
	} else{
		status_ = "Closed";
	}
}

bool CashRegister::operator==(const CashRegister& cash_register){
	if(cash_register.id_ != id_){
		return false;
	} else if(cash_register.location_ != location_){
		return false;
	} else if(cash_register.status_ != status_){
		return false;
	}
	if(cash_register.bill_.size() == bill_.size()){
		for(int i = 0; i < bill_.size(); i++){
			if(cash_register.bill_.at(i).name != bill_.at(i).name){
				return false;
			} else if(cash_register.bill_.at(i).price_netto != bill_.at(i).price_netto){
				return false;
			} else if(cash_register.bill_.at(i).tax != bill_.at(i).tax){
				return false;
			}
		}
	} else{
		return false;
	}
	return true;
}

bool CashRegister::operator!=(const CashRegister& cash_register){
	return !(*this == cash_register);
}

std::ostream& operator<<(std::ostream& os, CashRegister& cash_register){
	os << "Kasa #" << cash_register.id() << endl;
	os << "Położenie: " << cash_register.location() << endl;
	return os;
}

int Queue::size(){
	return size_;
}

Queue::Queue(){
	vector<Person> queue_;
	size_ = 0;
}

vector<Person> Queue::queue(){
	return queue_;
}

void Queue::push(const Person client){
	queue_.push_back(client);
	size_++;
}

void Queue::pop(){
	queue_.erase(queue_.begin());
	size_--;
}

void Queue::switch_places(int index1, int index2){
	Person temp = queue_.at(index1);
	queue_.at(index1) = queue_.at(index2);
	queue_.at(index2) = temp;
}

Person Queue::operator[](const int& id){
	return queue_[id];
}

bool Queue::operator==(const Queue& queue){
	if(queue.size_ != size_){
		return false;
	}
	for(int i = 0; i < size_ - 1; i++){
		if(queue_[i] != queue.queue_[i]){
			return false;
		}
	}
	return true;
}

bool Queue::operator!=(const Queue& queue){
	return !(*this == queue);
}

Queue Queue::operator+(const Queue& queue){
	Queue new_queue;
	for(auto elem: queue_){
		new_queue.push(elem);
	}
	for(auto elem: queue.queue_){
		new_queue.push(elem);
	}
	new_queue.size_ = size_ + queue.size_;
	return new_queue;
}

Queue& Queue::operator+=(const Queue& queue){
	this->queue_.reserve(queue.queue_.size());
	for (auto elem: queue.queue_){
		this->push(elem);
	}
	this->size_ += queue.size_;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Queue& queue){
	for(int i = 0; i < queue.queue_.size(); i++){
		os << queue.queue_.at(i) << endl;
	}
	return os;
}

Person::Person(std:: string frst_nm, std::string lst_nm, int prsn_id){
	first_name = frst_nm;
	last_name = lst_nm;
	id = prsn_id;
}

bool Person::operator==(const Person& person){
	if(person.first_name != first_name){
		return false;
	} else if(person.last_name != last_name){
		return false;
	} else if(person.id != id){
		return false;
	}
	return true;
}

bool Person::operator!=(const Person& person){
	return !(*this == person);
}

std::ostream& operator<<(std::ostream& os, const Person& person){
	os << "Imię: " << person.first_name << ", ";
	os << "Nazwisko: " << person.last_name << ", ";
	os << "Id: " << person.id;
	return os;
}

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
