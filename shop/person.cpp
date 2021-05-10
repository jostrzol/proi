#include "person.h"

Person::Person(int id, std::string name, std::string address, std::string phone)
    : Entity(id), name(name), address(address), phone(phone)
{
    return;
}

std::string Person::GetName() const { return name; }
void Person::SetName(const std::string &val) { name = val; }

std::string Person::GetAddress() const { return address; }
void Person::SetAddress(const std::string &val) { address = val; }

std::string Person::GetPhone() const { return phone; }
void Person::SetPhone(const std::string &val) { phone = val; }