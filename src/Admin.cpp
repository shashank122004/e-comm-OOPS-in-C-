#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "admin.h"
using namespace std;

// ==================== DASHBOARD ====================
void Admin::dashboard() {
    int choice;
    while (true) {
        cout << "\n===== Admin Dashboard =====\n";
        cout << "1. Add Product\n";
        cout << "2. Remove Product\n";
        cout << "3. Update Product Stock/Price\n";
        cout << "4. View All Products\n";
        cout << "5. View All Orders\n";
        cout << "6. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addProduct(); break;
            case 2: removeProduct(); break;
            case 3: updateProduct(); break;
            case 4: viewProducts(); break;
            case 5: viewOrders(); break;
            case 6:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}

// ==================== ADD PRODUCT ====================
void Admin::addProduct() {
    product_info p;
    cout << "Enter product ID: ";
    cin >> p.id;
    cin.ignore();
    cout << "Enter product name: ";
    getline(cin, p.name);
    cout << "Enter product price: ";
    cin >> p.price;
    cout << "Enter product stock: ";
    cin >> p.stock;

    // Append to products.txt
    ofstream outfile("products.txt", ios::app);
    if (!outfile) {
        cout << "Error opening products file for writing!\n";
        return;
    }
    outfile << p.id << " " << p.name << " " << p.price << " " << p.stock << "\n";
    outfile.close();

    cout << "Product added successfully!\n";
}

// ==================== REMOVE PRODUCT ====================
void Admin::removeProduct() {
    int targetId;
    cout << "Enter product ID to remove: ";
    cin >> targetId;

    ifstream infile("products.txt");
    ofstream tempFile("temp.txt");
    if (!infile || !tempFile) {
        cout << "Error opening file!\n";
        return;
    }

    int id, price, stock;
    string name;
    bool found = false;

    while (infile >> id >> name >> price >> stock) {
        if (id != targetId) {
            tempFile << id << " " << name << " " << price << " " << stock << "\n";
        } else {
            found = true;
        }
    }

    infile.close();
    tempFile.close();

    remove("products.txt");
    rename("temp.txt", "products.txt");

    if (found) cout << "Product removed successfully.\n";
    else cout << "Product not found!\n";
}

// ==================== UPDATE PRODUCT ====================
void Admin::updateProduct() {
    int targetId;
    cout << "Enter product ID to update: ";
    cin >> targetId;

    ifstream infile("products.txt");
    ofstream tempFile("temp.txt");
    if (!infile || !tempFile) {
        cout << "Error opening file!\n";
        return;
    }

    int id, price, stock;
    string name;
    bool found = false;

    while (infile >> id >> name >> price >> stock) {
        if (id == targetId) {
            found = true;
            cout << "Enter new price: ";
            cin >> price;
            cout << "Enter new stock: ";
            cin >> stock;
        }
        tempFile << id << " " << name << " " << price << " " << stock << "\n";
    }

    infile.close();
    tempFile.close();

    remove("products.txt");
    rename("temp.txt", "products.txt");

    if (found) cout << "Product updated successfully.\n";
    else cout << "Product not found!\n";
}

// ==================== VIEW PRODUCTS ====================
void Admin::viewProducts() {
    ifstream infile("products.txt");
    if (!infile) {
        cout << "Error opening products file!\n";
        return;
    }

    int id, price, stock;
    string name;
    cout << "\n----- All Products -----\n";
    while (infile >> id >> name >> price >> stock) {
        cout << "ID: " << id << " | Name: " << name << " | Price: " << price << " | Stock: " << stock << "\n";
    }

    infile.close();
}

// ==================== VIEW ORDERS ====================
void Admin::viewOrders() {
    ifstream infile("orders.txt");
    if (!infile) {
        cout << "Error opening orders file!\n";
        return;
    }

    string username, productName;
    int productId, quantity;
    cout << "\n----- All Orders -----\n";
    while (infile >> username >> productId >> productName >> quantity) {
        cout << "User: " << username << " | Product ID: " << productId
             << " | Product: " << productName << " | Quantity: " << quantity << "\n";
    }

    infile.close();
}
