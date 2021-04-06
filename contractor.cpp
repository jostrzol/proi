#include <iostream>
#include <regex>
#include "contractor.h"

Contractor::Contractor(std::string name, std::string address, std::string phone)
    : name(name), address(address), phone(phone){};

std::string Contractor::Name() { return name; }
void Contractor::SetName(const std::string &val) { name = val; }

std::string Contractor::Address() { return address; }
void Contractor::SetAddress(const std::string &val) { address = val; }

std::string Contractor::Phone() { return phone; }
void Contractor::SetPhone(const std::string &val) { phone = val; }