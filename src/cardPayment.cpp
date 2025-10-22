#include <iostream>
#include "cardPayment.h"
using namespace std;

void CardPayment::pay() {
    cout << "Processing Card Payment...\n";
    cout << "Card Number: " << card_number << endl;
    cout << "Expiry: " << expiry << " | CVV: " << cvv << endl;
    cout << "Amount: " << amount << endl;
    // Simulate payment processing
    cout << "Payment done via Card successfully.\n";
}
