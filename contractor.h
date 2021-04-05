#ifndef CONTRACTOR_H
#define CONTRACTOR_H

#include <string>

class Contractor
{
public:
    Contractor(std::string name, std::string address, std::string phone)
        : name(name), address(address), phone(phone){};

    std::string Name();
    void SetName(const std::string &val);

    std::string Address();
    void SetAddress(const std::string &val);

    std::string Phone();
    void SetPhone(const std::string &val);

private:
    std::string name;
    std::string address;
    std::string phone;
};

#endif