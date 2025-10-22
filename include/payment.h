#ifndef PAYMENT_H
#define PAYMENT_H
//are called include guards in C++. 
//  They prevent a header file from being included more than once during compilation
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include<string>
#include<vector>
#include "product.h"
using namespace std;

class Payment{
    protected: double amount;
    public:
    // Constructor
    Payment(double amt = 0.0) : amount(amt) {}

    // Virtual destructor (important for base classes)
    virtual ~Payment() {}

    virtual void pay()=0; //pure virtual function
    void setAmount(double amt) { amount = amt; }
    double getAmount() const { return amount; }
};

#endif