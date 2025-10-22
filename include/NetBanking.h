#ifndef NETBANKING_H
#define NETBANKING_H

#include <iostream>
#include <string>
#include "payment.h"
using namespace std;

class NetBanking : public Payment {
private:
    string bank_name;
    string account_number;
public:
    NetBanking(const string &bank, const string &accNum, double amt)
        : Payment(amt), bank_name(bank), account_number(accNum) {}

    void pay() override;
};

#endif
