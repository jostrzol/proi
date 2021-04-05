#include "contractor.h"

std::string Contractor::Name() { return name; }
void Contractor::SetName(const std::string &val) { name = val; }

std::string Contractor::Address() { return address; }
void Contractor::SetAddress(const std::string &val) { address = val; }

std::string Contractor::Phone() { return phone; }
void Contractor::SetPhone(const std::string &val) { phone = val; }
