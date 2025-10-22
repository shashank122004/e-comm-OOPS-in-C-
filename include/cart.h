#ifndef CART_H
#define CART_H
//are called include guards in C++. 
//  They prevent a header file from being included more than once during compilation
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include<string>
#include<vector>
#include "product.h"
using namespace std;

class Cart{
    private:
    vector<Product>items;
    public:
    void add_item(const Product &p);
    void remove_item(int &id);
    void cart_total();
    void view_cart();
};

#endif