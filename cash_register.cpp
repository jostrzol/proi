#include <iostream>
#include <vector>

#include "cash_register.h"

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
