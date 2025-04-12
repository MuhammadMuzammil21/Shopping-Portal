#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <limits>
#include "SpookyOutput.hpp"
#include "History.hpp"
#include "InventoryClass.hpp"
#include "ShoppingCart+RetailerClass.hpp"
#include "UserClass.hpp"
using namespace std;

class Shopping_Portal
{ // Main Portal
    Inventory inventory;
    // Shopping_Cart *cart;
    // Retailer_Store *store;
    User *currentUser;
    Customer *currentCustomer;
    Seller *currentSeller;
    UserHashTable UserTable;

public:
    /* Features:
    - Main Portal Console
    - Product Recommendation
    */
    Shopping_Portal()
    {
        // cart = new Shopping_Cart;
        // store = new Retailer_Store(&inventory);
        currentUser = NULL;
        currentSeller = NULL;
        currentCustomer = NULL;
    }
    void Entrance();
    void ProductRecom(); // Uses a graph-based recommendation system.
    void PortalSearch();
    void PortalSort();

    // Customer
    void MainPortal_C();
    void RetrieveProduct_C();
    void GoToCart();
    void GoToHistory_C();

    // Seller
    void MainPortal_S();
    void RetrieveProduct_S();
    void GoToStore();
    void GoToHistory_S();

    void wait()
    {
        cout << endl
             << "Press any key to continue." << endl;
        getch();
    }

    void purchase()
    {
        // Calculates Total price of cart
        double totalPrice = currentCustomer->getCart()->calculateTotalCost();
        cout << "Total Price: PKR" << totalPrice << endl;

        if (currentCustomer->updateWallet(totalPrice) == false)
        {
            wait();
            return;
        }
        // Individual rating of products in the cart
        ShoppingCartNode *current = currentCustomer->getCart()->getHead();
        while (current != nullptr)
        {
            Product &tempProduct = current->product;
            float rating;
            cout << "Enter rating for product '" << tempProduct.getName() << "': ";
            cin >> rating;

            UserTable.searchUser(tempProduct.getsellerName(), 's')->updateWallet(-tempProduct.getPrice() * current->quantity);

            tempProduct.setStockQuantity(tempProduct.getStockQuantity() - current->quantity);

            // Adds the cart to History
            GlobalHistory.addToHistory_C(current->product, rating);

            // Set the rating for the product
            current->product.addNewRating(rating);
            current = current->next;
        }

        // Clears cart
        currentCustomer->getCart()->clearCart();
    }

    void AccountManagement()
    {
        int choice = 0;
        do
        {
            sout << "Loading..............";
            system("cls");
            cout << "---------------Account Management---------------" << endl;
            cout << "Current wallet funds PKR " << currentUser->getWallet() << endl;
            cout << "1. Update wallet" << endl;
            cout << "2. Change password" << endl;
            cout << "3. Exit" << endl;
            cout << "Select Option:";
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                double newBalance;
                cout << "Enter a valid wallet ammount (negative for loan): " << endl;
                cin >> newBalance;
                currentUser->setWallet(newBalance);
                cout << "Wallet updated succesfully" << endl;
            }
            break;
            case 2:
            {
                string password, password2;
                cout << "Enter a new password: ";
                cin >> password;
                cout << "Re-enter password: ";
                cin >> password2;
                if (password == password2)
                {
                    currentUser->setPassword(password);
                    cout << "Password updated successfully" << endl;
                }
                else
                {
                    cout << "Password does not match, try again" << endl;
                }
                break;
            }
            case 3:
                system("cls");
                cout << "Changes saved to memory." << endl;
                break;
            default:
                cout << "Invalid option!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            wait();

        } while (choice != 3);
    }
};

void Shopping_Portal::Entrance()
{
    int choice;
    inventory.loadFromFile();
    UserTable.loadFromFile();
    Sleep(1000);
    system("cls");
    system("color 2B");
    do
    {
        sout << "Loading..............";
        system("cls");
        cout << "---------------Welcome to Shopping Portal---------------" << endl;
        cout << "1. Customer" << endl;
        cout << "2. Seller" << endl;
        cout << "3. Register" << endl;
        cout << "4. Exit" << endl;
        cout << "Select Option:";
        cin >> choice;

        // if (typeid(choice).name() == typeid("1").name())
        // {
        //     cin.ignore();
        //     cin.clear();
        // }
        // After addition of security system, add login system

        switch (choice)
        {
        case 1:
        {
            currentUser = UserTable.Login('c');
            if (!currentUser)
            {
                cout << "Login failed: Invalid login." << endl;
                break;
            }
            currentCustomer = new Customer(*currentUser);
            MainPortal_C();
            delete currentCustomer;
            currentCustomer = NULL;
            break;
        }
        case 2:
            currentUser = UserTable.Login('s');
            if (!currentUser)
            {
                cout << "Login failed: Invalid login." << endl;
                break;
            }
            currentSeller = new Seller(*currentUser, inventory);
            MainPortal_S();
            delete currentSeller;
            currentSeller = NULL;
            break;
        case 3:
        { // Create Customer class
            string usernameStr, userPassword, choice;
            char type;
            float balance;
            cout << "Enter new user login details" << endl;
            cout << "Registering as a customer, seller or both?: ";
            cin >> choice;
            if (choice == "customer" || choice == "Customer" || choice == "CUSTOMER")
                type = 'c';
            else if (choice == "seller" || choice == "Seller" || choice == "SELLER")
                type = 's';
            else if (choice == "both" || choice == "Both" || choice == "BOTH")
                type = 'b';
            else
            {
                cout << "Invalid choice" << endl;
                break;
            }
            cout << "Username: ";
            cin.ignore();
            getline(cin, usernameStr);
            cout << "Password: ";
            cin >> userPassword;
            cout << "Initial wallet balance?: ";
            cin >> balance;
            UserTable.addUser(User(usernameStr, userPassword, (balance >= 0 ? balance : 0), type));
            break;
        }
        case 4:
            system("cls");
            sout << "Thank you for using our Shopping Portal :)";
            break;
        default:
            cout << "Invalid option!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            wait();
            break;
        }
    } while (choice != 4);
    UserTable.saveToFile();
    inventory.saveToFile();
}

void Shopping_Portal::PortalSearch()
{
    int choice = 0;
    int targetID;
    string targetName;
    system("cls");
    while (choice != 3)
    {
        // inventory.displayAllProducts();
        cout << "---------------Menu---------------" << endl;
        cout << "1. By product Name" << endl;
        cout << "2. By product ID" << endl;
        cout << "3. Exit" << endl;
        cout << "Select Searching Criteria:";
        cin >> choice;
        switch (choice)
        {
        case 1:
            // Search by name
            {
                cout << "Enter product's name to search: ";
                cin >> targetName;
                Product *temp = inventory.searchProduct_name(targetName);
                if (temp)
                {
                    Product::displayHeader();
                    temp->displayProduct();
                    Product::displayFooter();
                }
                wait();
            }
            break;
        case 2:
            // Search by ID
            {
                cout << "Enter product's ID to search: ";
                cin >> targetID;
                cin.clear();
                cin.ignore(12, '\n');
                Product *temp = inventory.searchProduct_ID(targetID);
                if (temp)
                {
                    Product::displayHeader();
                    temp->displayProduct();
                    Product::displayFooter();
                }
                wait();
            }
            break;
        case 3:
            break;
        default:
            cout << "Invalid option!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            wait();
            break;
        }
        if (choice == 3)
        {
            system("cls");
            sout << "Exiting......";
            break;
        }
        system("cls");
    }
}

void Shopping_Portal::PortalSort()
{
    int choice = 0;
    system("cls");
    // inventory.displayAllProducts();
    cout << "---------------Menu---------------" << endl;
    cout << "1. By product Name" << endl;
    cout << "2. By product ID" << endl;
    cout << "3. By product Price" << endl;
    cout << "4. Exit" << endl;
    cout << "Select Sorting Criteria:";
    cin >> choice;

    cin.clear();
    cin.ignore(12, '\n');
    switch (choice)
    {
    case 1:
        // Sort by name
        inventory.sortProduct_name();
        break;
    case 2:
        // Sort by ID
        inventory.sortProduct_ID();
        break;
    case 3:
        // Sort by price
        inventory.sortProduct_price();
        break;
    case 4:
        break;
    default:
        cout << "Invalid option!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        wait();
        break;
    }
}

void Shopping_Portal::ProductRecom()
{
    system("cls");
    inventory.ProductRecom();
    wait();
}

// Customer
void Shopping_Portal::MainPortal_C()
{
    int choice = 0;
    system("cls");
    while (choice != 6)
    {
        cout << "---------------Main Menu---------------" << endl;
        cout << "1. Product list" << endl;
        cout << "2. Shopping Cart" << endl;
        cout << "3. History" << endl;
        cout << "4. Product Recommendation" << endl;
        cout << "5. Account Management" << endl;
        cout << "6. Exit" << endl;
        cout << "Select Option:";
        cin >> choice;

        switch (choice)
        {
        case 1:
            // retireve all products
            RetrieveProduct_C();
            break;
        case 2:
            // Go to Shopping Cart
            GoToCart();
            break;
        case 3:
            // Go to History
            GoToHistory_C();
            break;
        case 4:
            // Product Recom
            ProductRecom();
            break;
        case 5:
            AccountManagement();
            break;
        case 6:
        {
            char input;
            cout << "Are you sure? The cart will be deleted. (Y/N) : " << endl;
            cin >> input;
            if (input == 'Y' || input == 'y')
                choice = 7;
            else
                choice = 0;
        }
        break;
        default:
            cout << "Invalid option!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            wait();
            break;
        }
        if (choice == 7)
        {
            system("cls");
            sout << "Exiting......";
            break;
        }
        system("cls");
    }
}

void Shopping_Portal::RetrieveProduct_C()
{
    int choice = 0;
    system("cls");
    while (choice != 4)
    {
        inventory.displayAllProducts();
        cout << "---------------Menu---------------" << endl;
        cout << "1. Add product to Shopping Cart" << endl;
        cout << "2. Search Product" << endl;
        cout << "3. Sort Product" << endl;
        cout << "4. Exit" << endl;
        cout << "Select Option:";
        cin >> choice;

        switch (choice)
        {
        case 1:
            // Add products to Shopping Cart
            {
                int tempID;
                cout << "Enter product ID to add to cart: ";
                cin >> tempID;
                Product *tempProd = inventory.searchProduct_ID(tempID);
                if (tempProd)
                    currentCustomer->getCart()->addToCart(*tempProd);
            }
            break;
        case 2:
            // Search
            PortalSearch();
            break;
        case 3:
            // Sort
            PortalSort();
            break;
        case 4:
            break;
        default:
            cout << "Invalid option!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            wait();
            break;
        }
        if (choice == 4)
        {
            system("cls");
            sout << "Exiting......";
            break;
        }
        system("cls");
    }
}

void Shopping_Portal::GoToCart()
{
    int choice, tempID;
    Shopping_Cart *tempCart = currentCustomer->getCart();
    system("cls");
    while (choice != 4)
    {
        // Display all product in shopping cart
        tempCart->displayCart();
        cout << "---------------Menu---------------" << endl;
        cout << "1. Add product to Shopping Cart" << endl;
        cout << "2. Remove product from shopping cart" << endl;
        cout << "3. Purchase product" << endl;
        cout << "4. Exit" << endl;
        cout << "Select Option:";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // Add product to shopping cart
            cout << "Enter product ID to add to cart: ";
            cin >> tempID;
            Product *tempProd = inventory.searchProduct_ID(tempID);
            if (tempProd)
                currentCustomer->getCart()->addToCart(*tempProd);
        }
        break;
        case 2:
            // Remove products to Shopping Cart
            {
                cout << "Enter product ID to remove from cart: ";
                cin >> tempID;
                Product *tempProd = inventory.searchProduct_ID(tempID);
                if (tempProd)
                    currentCustomer->getCart()->removeFromCart(*tempProd);
            }
            break;
        case 3:
            purchase();
            break;
        case 4:
            break;
        default:
            cout << "Invalid option!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            wait();
            break;
        }
        if (choice == 4)
        {
            system("cls");
            sout << "Exiting......";
            break;
        }
        system("cls");
    }
}

void Shopping_Portal::GoToHistory_C()
{
    GlobalHistory.printHistory_C(); // prints last 5 as it is a stack.
}

// Seller
void Shopping_Portal::MainPortal_S()
{
    int choice = 0;
    system("cls");
    while (choice != 5)
    {
        cout << "---------------Main Menu---------------" << endl;
        cout << "1. Product list" << endl;
        cout << "2. Store" << endl;
        cout << "3. History" << endl;
        cout << "4. Account Management" << endl;
        cout << "5. Exit" << endl;
        cout << "Select Option:";
        cin >> choice;

        switch (choice)
        {
        case 1:
            // retireve all products
            RetrieveProduct_S();
            break;
        case 2:
            // Go to Store
            GoToStore();
            break;
        case 3:
            // Go to History
            GoToHistory_S();
            break;
        case 4:
            AccountManagement();
            break;
        case 5:
            break;
        default:
            cout << "Invalid option!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            wait();
            break;
        }
        if (choice == 5)
        {
            system("cls");
            sout << "Exiting......";
            break;
        }
        system("cls");
    }
}

void Shopping_Portal::RetrieveProduct_S()
{
    int choice = 0;
    system("cls");
    while (choice != 3)
    {
        inventory.displayAllProducts();
        cout << "---------------Menu---------------" << endl;
        cout << "1. Search Product" << endl;
        cout << "2. Sort Product" << endl;
        cout << "3. Exit" << endl;
        cout << "Select Option:";
        cin >> choice;

        switch (choice)
        {
        case 1:
            // Search
            PortalSearch();
            break;
        case 2:
            // Sort
            PortalSort();
            break;
        case 3:
            break;
        default:
            cout << "Invalid option!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            wait();
            break;
        }
        if (choice == 3)
        {
            system("cls");
            sout << "Exiting......";
            break;
        }
        system("cls");
    }
}

void Shopping_Portal::GoToStore()
{
    int choice;
    Retailer_Store *tempStore = currentSeller->getStore();
    string sname = currentSeller->getUsername();
    system("cls");
    while (choice != 4)
    {
        // Display all product in Store
        tempStore->displayStoreProducts(sname);
        cout << sname << endl;
        cout << "---------------Menu---------------" << endl;
        cout << "1. Add product to Store" << endl;
        cout << "2. Remove product from Store" << endl;
        cout << "3. Update product quantity" << endl;
        cout << "4. Exit" << endl;
        cout << "Select Option:";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // Add product to store
            tempStore->addProductToStore(sname);
        }
        break;
        case 2:
        {
            // Remove products to Shopping Cart
            int tempID;
            cout << "Enter product ID to remove from store: ";
            cin >> tempID;
            tempStore->removeProductFromStore(tempID, sname);
        }
        break;
        case 3:
        {
            // Update product quantity
            int tempID;
            cout << "Enter product ID to update from store: ";
            cin >> tempID;
            tempStore->updateProductQuantity(tempID, sname);
        }
        break;
        case 4:
            break;
        default:
            cout << "Invalid option!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            wait();
            break;
        }
        if (choice == 4)
        {
            system("cls");
            sout << "Exiting......";
            break;
        }
        system("cls");
    }
}

void Shopping_Portal::GoToHistory_S()
{
    GlobalHistory.printHistory_S(currentSeller->getUsername());
}

int main()
{
    Shopping_Portal s;
    s.Entrance();
}