#ifndef ADMIN_H
#define ADMIN_H
// Include guards to prevent multiple inclusions

#include <iostream>
#include <vector>
#include <string>
#include "User.h"
#include "product.h"   // Use Product.h for product_info struct

using namespace std;

// Admin class inherits from User
class Admin : public User {  // public inheritance
private:
    vector<product_info> shop; // Admin's in-memory product list

    // Admin-specific functions
    void addProduct();
    void removeProduct();
    void updateProduct();
    void viewProducts();
    void viewOrders();

public:
    // Constructor calls base class User constructor
    Admin(const string &uname, const string &pwd)
        : User(uname, pwd, "admin") {}

    // Override pure virtual function from User
    void dashboard() override;
};

#endif
