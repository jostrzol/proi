#include "person.h"

Person::Person(std::string name, std::string address, std::string phone, int id)
    : Entity(id), name(name), address(address), phone(phone) {}

std::string Person::GetName() const { return name; }
void Person::SetName(const std::string &val) { name = val; }

std::string Person::GetAddress() const { return address; }
void Person::SetAddress(const std::string &val) { address = val; }

std::string Person::GetPhone() const { return phone; }
void Person::SetPhone(const std::string &val) { phone = val; }