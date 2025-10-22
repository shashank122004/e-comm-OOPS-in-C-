#ifndef CARDPAYMENT_H
#define CARDPAYMENT_H

#include <iostream>
#include <string>
#include "payment.h"
using namespace std;

class CardPayment : public Payment {
private:
    string card_number;
    string expiry;
    string cvv;
public:
    CardPayment(const string &cardNum, const string &exp, const string &cvvCode, double amt)
        : Payment(amt), card_number(cardNum), expiry(exp), cvv(cvvCode) {}

    void pay() override;
};

#endif
