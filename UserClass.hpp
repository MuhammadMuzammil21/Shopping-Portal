#include <iostream>
#include <string>
#include <fstream>

using namespace std;
// Add Filing
void encryptFile(string filename)
{
    ifstream inFile(filename, ios::in);
    string content;

    char ch;
    while (inFile.get(ch))
    {
        content += (ch + 5) % 256;
    }

    inFile.close();

    ofstream outFile(filename, ios::out | ios::binary);
    outFile << content;
    outFile.close();
}
void decryptFile(string filename)
{
    ifstream inFile(filename, ios::in | ios::binary);
    string content;

    char ch;
    while (inFile.get(ch))
        content += (int(ch) - 5 + 256) % 256;

    inFile.close();

    ofstream outFile(filename, ios::out | ios::binary);
    outFile.write(content.c_str(), content.size());
    outFile.close();
}

class User
{
protected:
    string username;
    string password;
    double wallet;
    char typeOfUser; // 'c' for customer. 's' for seller

public:
    User(const string &uName, const string &uPassword, float wallet = 0, char typeOfUser = 'c')
        : username(uName), password(uPassword), wallet(wallet), typeOfUser(typeOfUser) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    double getWallet() { return wallet; }
    char getTypeOfUser() { return typeOfUser; }
    void setUsername(const string &newUsername) { username = newUsername; }
    void setPassword(const string &newPassword) { password = newPassword; }
    void setWallet(const double &newWallet) { wallet = newWallet; }

    bool authenticate(const string &uName, const string &uPassword, char type) const
    {
        return (uName == username && uPassword == password && (typeOfUser == type || typeOfUser == 'b'));
    }

    bool updateWallet(double amount)
    {
        if (amount <= wallet)
        {
            wallet -= amount;
            cout << "Wallet updated successfully. New balance: $" << wallet << endl;
            return true;
        }

        cout << "Amount greater than wallet." << endl;
        return false;
    }
};

class UserNode
{
public:
    User user;
    UserNode *next;

    UserNode(const User &u) : user(u), next(nullptr) {}
};

class UserHashTable
{
private:
    static const int TABLE_SIZE = 10;
    UserNode *table[TABLE_SIZE];

    void clearTable()
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            UserNode *current = table[i];
            while (current != nullptr)
            {
                UserNode *temp = current;
                current = current->next;
                delete temp;
            }
            table[i] = nullptr;
        }
    }

public:
    UserHashTable()
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            table[i] = nullptr;
        }
    }
    ~UserHashTable()
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            UserNode *current = table[i];
            while (current != nullptr)
            {
                UserNode *temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
    bool saveToFile(string filename = "UserTable.dat")
    {
        ofstream outFile(filename, ios::out | ios::binary);

        if (!outFile)
        {
            cout << "UserHashTable::Error: Unable to open the file for writing." << endl;
            return false;
        }

        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            UserNode *current = table[i];
            while (current != nullptr)
            {
                auto currUser = current->user;
                outFile << currUser.getUsername() << ',' << currUser.getPassword() << ',' << currUser.getWallet() << ',' << currUser.getTypeOfUser() << endl;
                current = current->next;
            }
        }
        outFile.close();
        encryptFile(filename);
        return true;
    }
    bool loadFromFile(string filename = "UserTable.dat")
    {
        decryptFile(filename);
        FILE *file;
        file = fopen(filename.c_str(), "r");
        if (!file)
        {
            cout << "UserHashTable::Error: Unable to open the file for reading." << endl;
            return false;
        }

        // Clear existing data
        clearTable();

        char username[50] = {0};
        char password[50] = {0};
        float wallet = 0.0f;
        char type;
        while (fscanf(file, "%49[^,],%49[^,],%f,%c\n", username, password, &wallet, &type) == 4)
        {
            User user(username, password, wallet, type);
            addUser(user);
        }

        fclose(file);
        encryptFile(filename);
        return true;
    }

    int hashFunction(const string &username) const
    {
        int hash = 0;
        for (char ch : username)
        {
            hash += static_cast<int>(ch);
        }
        return hash % TABLE_SIZE;
    }

    void addUser(const User &user)
    {
        int hashValue = hashFunction(user.getUsername());

        // Check if the username is already present
        UserNode *current = table[hashValue];
        while (current != nullptr)
        {
            if (current->user.getUsername() == user.getUsername())
            {
                cout << "Username '" << user.getUsername() << "' already exists. Please choose a different username." << endl;
                return;
            }
            current = current->next;
        }

        // If the username is not present, add the new user
        UserNode *newNode = new UserNode(user);
        newNode->next = table[hashValue];
        table[hashValue] = newNode;
        cout << "User '" << user.getUsername() << "' added successfully!" << endl;
    }

    bool authenticateUser(const string &username, const string &password, char type) const
    {
        int hashValue = hashFunction(username);
        UserNode *current = table[hashValue];

        while (current != nullptr)
        {
            if (current->user.authenticate(username, password, type))
            {
                return true;
            }
            current = current->next;
        }

        return false;
    }
    User *searchUser(const string &username, char type)
    {
        int hashValue = hashFunction(username);
        UserNode *current = table[hashValue];

        while (current != nullptr)
        {
            if (current->user.getUsername() == username && (current->user.getTypeOfUser() == type || current->user.getTypeOfUser() == 'b'))
            {
                return &current->user;
            }
            current = current->next;
        }
        return NULL;
    }
    User *Login(char type)
    {
        string username, password;
        cout << "Enter login details" << endl;
        cout << "Username: ";
        cin.ignore();
        getline(cin, username);
        cout << "Password: ";
        cin >> password;
        int hashValue = hashFunction(username);
        UserNode *current = table[hashValue];

        while (current != nullptr)
        {
            if (current->user.authenticate(username, password, type))
            {
                return &current->user;
            }
            current = current->next;
        }

        return NULL;
    }
};

class Customer : public User
{
    Shopping_Cart cart;

public:
    Customer(User &user) : User(user) {}
    Customer(const string &uName, const string &uPassword, float wallet = 0)
        : User(uName, uPassword, wallet) {}

    Shopping_Cart *getCart() { return &cart; }

    // Function to add a product to the shopping cart.
    void addToCart(Product &product)
    {
        cart.addToCart(product);
        cout << "Product added to the shopping cart successfully!" << endl;
    }

    // Function to remove a product from the shopping cart.
    void removeFromCart(const Product &product)
    {
        cart.removeFromCart(product);
        cout << "Product removed from the shopping cart successfully!" << endl;
    }

    // Function to display the items in the shopping cart.
    void displayCart() const
    {
        cart.displayCart();
    }

    // Function to calculate the total cost of items in the shopping cart.
    double calculateTotalCost() const
    {
        return cart.calculateTotalCost();
    }

    // Function to submit a review and rating for a product.
    void setRating(float rating)
    {
        // Couldnt do the same way as others because error occured usint const Product &product as an argumnet in the function.
        Product product;
        product.setRating(rating);
        cout << "Review and rating submitted successfully!" << endl;
    }
};

class Seller : public User
{
    Retailer_Store *store;
    string SellerName;

public:
    Seller(User &user, Inventory &invptr) : User(user)
    {
        store = new Retailer_Store(invptr);
    }
    Seller(const string &uName, const string &uPassword, const string &sellerName)
        : User(uName, uPassword), SellerName(sellerName) {}

    Retailer_Store *getStore() { return store; }

    string getsellerName()
    {
        return SellerName;
    }

    // Function to add a product to the store inventory.
    /*
    void addProductToStore(const Product &product)
    {
        store->addProductToStore(product);
        cout << "Product added to the store inventory successfully!" << endl;
    }

    // Function to remove a product from the store inventory.
    void removeProductFromStore(const Product &product)
    {
        store->removeProductFromStore(product);
        cout << "Product removed from the store inventory successfully!" << endl;
    }

    // Function to display the products in the store inventory.
    void displayStoreProducts() const
    {
        store->displayStoreProducts();
    }
    */
};
