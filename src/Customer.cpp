#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Customer.h"
#include "UPI.h"
#include "cardPayment.h"
#include "NetBanking.h"
#include "payment.h"
using namespace std;

// ==================== DASHBOARD ====================
void Customer::dashboard() {
    int choice;
    while (true) {
        cout << "\n===== Customer Dashboard =====\n";
        cout << "1. View Products\n";
        cout << "2. Add Product to Cart\n";
        cout << "3. Remove Product from Cart\n";
        cout << "4. View Cart\n";
        cout << "5. Checkout\n";
        cout << "6. View Order History\n";
        cout << "7. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: viewProducts(); break;
            case 2: addToCart(); break;
            case 3: removeFromCart(); break;
            case 4: viewCart(); break;
            case 5: checkout(); break;
            case 6: viewOrderHistory(); break;
            case 7:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}

// ==================== VIEW PRODUCTS ====================
void Customer::viewProducts() {
    ifstream file("products.txt");
    if (!file) {
        cout << "Problem opening products file.\n";
        return;
    }

    int id, price, stock;
    string name;
    cout << "\n----- Available Products -----\n";
    while (file >> id >> name >> price >> stock) {
        cout << "ID: " << id << " | Name: " << name << " | Price: " << price
             << " | Stock: " << stock << endl;
    }
    file.close();
}

// ==================== ADD TO CART ====================
void Customer::addToCart() {
    int product_id, quantity;
    cout << "Enter product ID to add to cart: ";
    cin >> product_id;
    cout << "Enter quantity: ";
    cin >> quantity;

    ifstream file("products.txt");
    if (!file) {
        cout << "Problem opening products file.\n";
        return;
    }

    int id, stock;
    double price;
    string name;
    bool found = false;

    while (file >> id >> name >> price >> stock) {
        if (id == product_id) {
            found = true;
            if (stock >= quantity) {
                // Check if product already in cart
                bool inCart = false;
                for (auto &p : cart) {
                    if (p.id == id) {
                        p.quantity += quantity;
                        inCart = true;
                        break;
                    }
                }
                if (!inCart) {
                    cart.push_back({id, name, price, quantity});
                }
                cout << "Product added to cart successfully!\n";
            } else {
                cout << "Not enough stock. Available: " << stock << endl;
            }
            break;
        }
    }

    if (!found) cout << "Product ID not found.\n";

    file.close();
}

// ==================== REMOVE FROM CART ====================
void Customer::removeFromCart() {
    if (cart.empty()) {
        cout << "Cart is empty.\n";
        return;
    }

    int product_id;
    cout << "Enter product ID to remove from cart: ";
    cin >> product_id;

    bool removed = false;
    for (auto it = cart.begin(); it != cart.end(); ++it) {
        if (it->id == product_id) {
            cart.erase(it);
            removed = true;
            cout << "Product removed from cart.\n";
            break;
        }
    }

    if (!removed) cout << "Product not found in cart.\n";
}

// ==================== VIEW CART ====================
void Customer::viewCart() {
    if (cart.empty()) {
        cout << "Your cart is empty.\n";
        return;
    }

    cout << "\n----- Your Cart -----\n";
    int total = 0;
    for (const auto &p : cart) {
        cout << "ID: " << p.id << " | Name: " << p.name << " | Price: " << p.price
             << " | Quantity: " << p.quantity << endl;
        total += p.price * p.quantity;
    }
    cout << "Total Amount: " << total << endl;
}

// ==================== CHECKOUT ====================
void Customer::checkout() {
    if (cart.empty()) {
        cout << "Cart is empty. Add products first.\n";
        return;
    }

    // 1️⃣ Calculate total amount
    double total = 0.0;
    for (const auto &p : cart) {
        total += p.price * p.quantity;  // assuming cart_prod has 'quantity'
    }
    cout << "\nTotal Amount to pay: " << total << endl;

    // 2️⃣ Select payment method
    int paymentChoice;
    cout << "Select Payment Method:\n";
    cout << "1. UPI\n2. Card\n3. Net Banking\nChoice: ";
    cin >> paymentChoice;

    Payment* payment = nullptr;  // base class pointer

    switch (paymentChoice) {
        case 1: {
            string upiID;
            cout << "Enter your UPI ID: ";
            cin >> upiID;
            payment = new UPI(upiID, total);  // creates derived object
            break;
        }
        case 2: {
            string cardNum, expiry, cvv;
            cout << "Enter Card Number: ";
            cin >> cardNum;
            cout << "Enter Expiry Date (MM/YY): ";
            cin >> expiry;
            cout << "Enter CVV: ";
            cin >> cvv;
            payment = new CardPayment(cardNum, expiry, cvv, total);
            break;
        }
        case 3: {
            string bankName, accNum;
            cout << "Enter Bank Name: ";
            cin >> bankName;
            cout << "Enter Account Number: ";
            cin >> accNum;
            payment = new NetBanking(bankName, accNum, total);
            break;
        }
        default:
            cout << "Invalid choice!\n";
            return;
    }

    // 3️⃣ Perform payment via polymorphism
    payment->pay();  // calls the correct pay() depending on the object type
    cout << "Payment successful!\n";

    // 4️⃣ Save order to orders.txt
    ofstream ordersFile("orders.txt", ios::app);
    if (!ordersFile) {
        cout << "Error opening orders file.\n";
        delete payment;  // free memory
        return;
    }

    for (const auto &p : cart) {
        ordersFile << username << " " << p.id << " " << p.name << " " << p.quantity << "\n";
    }
    ordersFile.close();

    // 5️⃣ Update product stock
    ifstream infile("products.txt");
    ofstream tempFile("temp.txt");
    if (!infile || !tempFile) {
        cout << "Error updating product stock.\n";
        delete payment;
        return;
    }

    int id, price, stock;
    string name;
    while (infile >> id >> name >> price >> stock) {
        for (const auto &p : cart) {
            if (p.id == id) {
                stock -= p.quantity;
                if (stock < 0) stock = 0;
            }
        }
        tempFile << id << " " << name << " " << price << " " << stock << "\n";
    }

    infile.close();
    tempFile.close();
    remove("products.txt");
    rename("temp.txt", "products.txt");

    // 6️⃣ Clean up
    delete payment;  // free dynamic memory
    cart.clear();    // empty cart

    cout << "Order confirmed!\n";
}


// ==================== VIEW ORDER HISTORY ====================
void Customer::viewOrderHistory() {
    ifstream file("orders.txt");
    if (!file) {
        cout << "Problem opening orders file.\n";
        return;
    }

    string user, name;
    int id, quantity;
    bool found = false;

    cout << "\n----- Your Order History -----\n";
    while (file >> user >> id >> name >> quantity) {
        if (user == username) {
            found = true;
            cout << "Product ID: " << id << " | Name: " << name
                 << " | Quantity: " << quantity << endl;
        }
    }

    if (!found) cout << "No orders found.\n";

    file.close();
}
