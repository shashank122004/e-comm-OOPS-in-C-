#ifndef UPI_H
#define UPI_H

#include <iostream>
#include <string>
#include "payment.h"
using namespace std;

class UPI : public Payment {
private:
    string upi_id;
public:
    UPI(const string &id, double amt) : Payment(amt), upi_id(id) {}

    void pay() override;
};

#endif
