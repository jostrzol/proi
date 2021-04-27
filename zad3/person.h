#pragma once
#include <iostream>

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
