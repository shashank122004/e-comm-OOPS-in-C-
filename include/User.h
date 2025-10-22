#ifndef USER_H
#define USER_H
//are called include guards in C++. 
//  They prevent a header file from being included more than once during compilation
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include<string>
#include<vector>
using namespace std;

// this is user class common for both customer and admin
class User{
    protected:
       string username;
       string password;
       string role;
    public:
        User()=default;
        //User(const string &uname,const string &upassword, const string &urole);
        User(const string &uname, const string &upassword, const string &urole)
    : username(uname), password(upassword), role(urole) {}

        virtual ~User() {}
        //getters
        string getUsername();
        string getRole();

        //setter
        void setUsername(const string& uname);
        void setPassword(const string& pwd);
        void setRole(const string& userRole);

        //core functions
        bool login(); //auth user from user.txt
        bool registerUser(); // Register new customer into users.txt
        
        virtual void dashboard() = 0;
};

#endif