#include <fstream>
#include <iostream>
#include "User.h"
using namespace std;

// ==================== LOGIN ====================
bool User::login() {
    ifstream file("User.txt");
    if (!file) {
        cout << "Error opening file!" << endl;
        return false;
    }

    string fileUsername, filePassword, fileRole;
    while (file >> fileUsername >> filePassword >> fileRole) {
        if (fileUsername == username && filePassword == password && fileRole == role) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// ==================== REGISTER ====================
bool User::registerUser() {
    string usernameInput, passwordInput;
    int roleid;

    cout << "Enter username: ";
    cin >> usernameInput;
    cout << "Enter password: ";
    cin >> passwordInput;
    cout << "Select role:\n1. Admin\n2. User\nChoice: ";
    cin >> roleid;

    string roleInput;
    if (roleid == 1) roleInput = "admin";
    else if (roleid == 2) roleInput = "user";
    else {
        cout << "Invalid role selection!" << endl;
        return false;
    }

    if (usernameInput.empty() || passwordInput.empty()) {
        cout << "All fields are required!" << endl;
        return false;
    }

    // Check if username already exists
    ifstream infile("User.txt");
    if (infile) {
        string fileUsername, filePassword, fileRole;
        while (infile >> fileUsername >> filePassword >> fileRole) {
            if (fileUsername == usernameInput) {
                cout << "Username already exists. Please choose another." << endl;
                infile.close();
                return false;
            }
        }
        infile.close();
    }

    // Append new user to file
    ofstream outfile("User.txt", ios::app);
    if (!outfile) {
        cout << "Error opening user file for writing!" << endl;
        return false;
    }

    outfile << usernameInput << " " << passwordInput << " " << roleInput << "\n";
    outfile.close();

    cout << "Registration successful! You can now login." << endl;
    return true;
}

// ==================== GETTERS ====================
string User::getUsername() { return username; }
string User::getRole() { return role; }

// ==================== SETTERS ====================
void User::setUsername(const string &uname) { username = uname; }
void User::setPassword(const string &upassword) { password = upassword; }
void User::setRole(const string &urole) { role = urole; }
