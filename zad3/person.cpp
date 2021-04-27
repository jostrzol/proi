#include <iostream>

#include "person.h"

using namespace std;

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
