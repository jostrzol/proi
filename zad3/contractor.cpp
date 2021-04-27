#include "contractor.h"

Contractor::Contractor(std::string name, std::string address, std::string phone, int id = -1)
    : Entity(id), name(name), address(address), phone(phone) {}

std::string Contractor::Name() const { return name; }
void Contractor::SetName(const std::string &val) { name = val; }

std::string Contractor::Address() const { return address; }
void Contractor::SetAddress(const std::string &val) { address = val; }

std::string Contractor::Phone() const { return phone; }
void Contractor::SetPhone(const std::string &val) { phone = val; }