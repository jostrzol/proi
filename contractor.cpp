#include <iostream>
#include <regex>
#include "contractor.h"

Contractor::Contractor(std::string name, std::string address, PhoneT phone)
    : name(name), address(address), phone(phone){};

std::string Contractor::Name() { return name; }
void Contractor::SetName(const std::string &val) { name = val; }

std::string Contractor::Address() { return address; }
void Contractor::SetAddress(const std::string &val) { address = val; }

PhoneT Contractor::Phone() { return phone; }
void Contractor::SetPhone(const PhoneT &val) { phone = val; }

InvalidPhone::InvalidPhone(std::string phone) : phone(phone){};
const char *InvalidPhone::what() const throw()
{
    std::string msg = "Invalid phone number: " + phone;
    return msg.c_str();
}

PhoneT::PhoneT(std::string phone) : phone(phone){};
void validatePhone(std::string phone)
{
    static const std::regex phoneRegEx(R"regex((?:\+\d+)?\s*(?:\(\d+\))?\s*\d+\s*(?:\s*-?\s*\d+)+)regex");
    std::smatch m;
    std::regex_search(phone, m, phoneRegEx);
    if (m.size() == 1)
    {
        phone = m[0];
        break;
    }
};
std::istream &operator>>(std::istream &is, PhoneT &phone);
std::ostream &operator<<(std::ostream &os, PhoneT &phone);

std::istream &operator>>(std::istream &is, PhoneT &phone)
{
    const auto &pos = is.tellg();
    char c;
    is.get(c);
};