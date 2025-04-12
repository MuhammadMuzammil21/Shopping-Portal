#include <iostream>
#include <fstream>
#include <string>
#include "UserClass.hpp"
using namespace std;
class PaymentGateway
{
public:
    // Simulated method to process a payment
    static bool processPayment(const string &username, double amount)
    {
        // Simulate connecting to the payment gateway and processing the payment
        cout << "Connecting to the payment gateway..." << endl;
        cout << "Processing payment for user: " << username << " | Amount: $" << amount << endl;

        // Simulate a successful payment (replace with actual payment processing logic)
        bool success = true;

        if (success)
        {
            cout << "Payment successful! Thank you for your purchase." << endl;
        }
        else
        {
            cout << "Payment failed. Please try again or use a different payment method." << endl;
        }

        return success;
    }
};

class PaymentProcessor : public User
{
private:
    UserHashTable &userTable; // Reference to the HashTable for user authentication

public:
    PaymentProcessor(const string &uName, const string &uPassword, UserHashTable &users)
        : User(uName, uPassword), userTable(users) {}

    // Function to initiate the payment process using an external payment gateway
    void initiatePayment(double amount)
    {
        // Authenticate the user before processing the payment
        if (userTable.authenticateUser(getUsername(), getPassword()))
        {
            bool paymentSuccess = PaymentGateway::processPayment(getUsername(), amount);

            if (paymentSuccess)
            {
                // Update user wallet, order history, etc. (replace with actual logic)
                updatePaymentStatus(amount);
            }
        }
        else
        {
            cout << "Authentication failed. Unable to process payment." << endl;
        }
    }

private:
    // Simulated method to update user payment status
    void updatePaymentStatus(double amount)
    {
        cout << "Updating user payment status..." << endl;
    }
};
