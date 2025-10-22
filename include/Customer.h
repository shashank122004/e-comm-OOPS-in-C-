#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <vector>
#include <string>
#include "User.h"
#include "product.h"
#include "cart.h"   // Cart class to manage customer cart

using namespace std;

// Struct to hold products in the customer's cart
struct CartProduct {
    int id;
    string name;
    double price;
    int quantity; // quantity added to cart
};

// Customer class inherits from User
class Customer : public User {
private:
    vector<CartProduct> cart; // Customer's in-memory cart

    // Customer-specific functions
    void viewProducts();         // View all available products
    void addToCart();            // Add a product to cart
    void removeFromCart();       // Remove a product from cart
    void viewCart();             // View current cart contents
    void checkout();             // Checkout & pay
    void viewOrderHistory();     // View past orders

public:
    // Constructor calls base class User constructor
    Customer(const string &uname, const string &pwd)
        : User(uname, pwd, "user") {}

    // Override pure virtual function from User
    void dashboard() override;
};

#endif
