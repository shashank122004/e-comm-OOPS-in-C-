#include <iostream>
#include <string>
#include "User.h"
#include "Customer.h"
#include "admin.h"

using namespace std;

int main() {
    int choice;

    while (true) {
        cout << "\n===== E-Commerce System =====\n";
        cout << "1. Login as Customer\n";
        cout << "2. Login as Admin\n";
        cout << "3. Register New Customer\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string uname, pwd;
                cout << "Enter username: ";
                cin >> uname;
                cout << "Enter password: ";
                cin >> pwd;

                Customer cust(uname, pwd);  // role automatically "user"
                if (cust.login()) {
                    cout << "Login successful!\n";
                    cust.dashboard();  // Go to Customer dashboard
                } else {
                    cout << "Invalid credentials!\n";
                }
                break;
            }

            case 2: {
                string uname, pwd;
                cout << "Enter admin username: ";
                cin >> uname;
                cout << "Enter password: ";
                cin >> pwd;

                Admin admin(uname, pwd);  // role automatically "admin"
                if (admin.login()) {
                    cout << "Login successful!\n";
                    admin.dashboard();  // Go to Admin dashboard
                } else {
                    cout << "Invalid credentials!\n";
                }
                break;
            }

            case 3: {
                Customer temp("", "");  // Temporary object to call register
                temp.registerUser();
                break;
            }

            case 4:
                cout << "Exiting system. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
