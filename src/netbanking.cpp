#include <iostream>
#include "NetBanking.h"
using namespace std;

void NetBanking::pay() {
    cout << "Processing NetBanking Payment...\n";
    cout << "Bank: " << bank_name << endl;
    cout << "Account Number: " << account_number << endl;
    cout << "Amount: " << amount << endl;
    // Simulate payment processing
    cout << "Payment done via NetBanking successfully.\n";
}
