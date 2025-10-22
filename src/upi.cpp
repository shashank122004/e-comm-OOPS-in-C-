#include <iostream>
#include "UPI.h"
using namespace std;

void UPI::pay() {
    cout << "Processing UPI payment...\n";
    cout << "UPI ID: " << upi_id << endl;
    cout << "Amount: " << amount << endl;
    // Simulate payment processing
    cout << "Payment done via UPI successfully.\n";
}
