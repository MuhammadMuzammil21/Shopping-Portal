#include <iostream>

class ShoppingCartNode
{
public:
    Product &product;
    int quantity;
    ShoppingCartNode *next;

    ShoppingCartNode(Product &item) : product(item), next(nullptr) {}
};

class Shopping_Cart
{
private:
    ShoppingCartNode *head; // Head of the linked list
    int numCartItems;       // Variable to keep track of the number of items in the cart.

public:
    Shopping_Cart() : head(nullptr), numCartItems(0) {} // Constructor to initialize the linked list.

    // Function to add a product to the shopping cart.
    void addToCart(Product &product)
    {
        int quanTemp = 0;
        cout << "How many do you want to add to the cart?: " << endl;
        cin >> quanTemp;

        ShoppingCartNode *traversalNode = head;
        while (traversalNode != NULL)
        {
            if (&traversalNode->product == &product)
            {
                if (traversalNode->quantity + quanTemp <= product.getStockQuantity())
                {
                    traversalNode->quantity += quanTemp;
                    cout << "Product added to the cart successfully!" << endl;
                }
                else
                {
                    cout << "Too much quantity bought." << endl;
                }
                return;
            }
            traversalNode = traversalNode->next;
        }
        if (product.getStockQuantity() >= quanTemp)
        {
            ShoppingCartNode *newNode = new ShoppingCartNode(product);
            newNode->next = head;
            newNode->quantity = quanTemp;
            head = newNode;
            numCartItems += quanTemp;
            cout << "Product added to the cart successfully!" << endl;
        }
        else
        {
            cout << "Product stock insufficient!" << endl;
        }
    }

    // Function to remove a product from the shopping cart.
    void removeFromCart(const Product &product)
    {
        ShoppingCartNode *current = head;
        ShoppingCartNode *prev = nullptr;

        while (current != nullptr)
        {
            if (current->product.getName() == product.getName())
            {
                if (prev == nullptr)
                {
                    head = current->next;
                }
                else
                {
                    prev->next = current->next;
                }

                numCartItems -= current->quantity;
                delete current;
                cout << "Product removed from the cart successfully!" << endl;
                return;
            }

            prev = current;
            current = current->next;
        }

        cout << "Product not found in the cart." << endl;
    }

    void clearCart()
    {
        while (head != nullptr)
        {
            ShoppingCartNode *temp = head;
            head = head->next;
            delete temp;
        }
        numCartItems = 0;
        cout << "Shopping cart cleared." << endl;
    }

    // Function to display the items in the shopping cart.
    void displayCart() const
    {
        if (numCartItems == 0)
        {
            cout << "Shopping cart is empty." << endl;
        }
        else
        {
            cout << "----------- Shopping Cart -----------" << endl;
            ShoppingCartNode *current = head;
            Product::displayHeader();
            while (current != nullptr)
            {
                current->product.displayProduct();
                cout << "\nNumber of items in cart: " << current->quantity << endl;
                cout << "-------------------------" << endl;
                current = current->next;
            }
            Product::displayFooter();
        }
    }

    // Function to calculate the total cost of items in the shopping cart.
    double calculateTotalCost() const
    {
        double totalCost = 0.0;
        ShoppingCartNode *current = head;
        while (current != nullptr)
        {
            totalCost += current->product.getPrice() * current->quantity;
            current = current->next;
        }
        return totalCost;
    }

    ShoppingCartNode *getHead()
    {
        return head;
    }

    // Destructor to free memory allocated for the linked list.
    ~Shopping_Cart()
    {
        while (head != nullptr)
        {
            ShoppingCartNode *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

class Retailer_Store
{
private:
    Inventory &inv;

public:
    Retailer_Store(Inventory &invptr) : inv(invptr) {} // Constructor to initialize the number of products in the store.

    // Function to add a product to the store inventory.
    void addProductToStore(string sellerName)
    {
        Product *tempProd = getProductData(sellerName);
        inv.addProduct(*tempProd);
    }

    Product *getProductData(string sellerName)
    {
        int cat;
        string name;
        double price;
        int stockQuantity;
        float rating = 0;
        Category category;
        cout << "Enter product name: " << endl;
        cin.ignore();
        getline(cin, name);
        cout << "Enter product price: " << endl;
        cin >> price;
        cout << "Enter product stock quantity: " << endl;
        cin >> stockQuantity;
        cout << "0. ELECTRONICS" << endl;
        cout << "1. CLOTHING" << endl;
        cout << "2. HOUSEHOLD" << endl;
        cout << "3. STATIONARY" << endl;
        cout << "4. OTHERS" << endl;
        cout << "Select category: ";
        cin >> cat;
        switch (cat)
        {
        case 0:
            category = Category::ELECTRONICS;
            break;
        case 1:
            category = Category::CLOTHING;
            break;
        case 2:
            category = Category::HOUSEHOLD;
            break;
        case 3:
            category = Category::STATIONARY;
            break;
        case 4:
            category = Category::OTHERS;
            break;
        default:
            cout << "Invalid!";
            break;
        }
        Product *newProduct = new Product(name, price, stockQuantity, rating, category, sellerName);
        return newProduct;
    }

    // Function to remove a product from the store inventory.
    void removeProductFromStore(int tempID, string sellerName)
    {
        Product *tempProd = inv.searchProduct_ID(tempID);
        if (tempProd)
        {
            if (tempProd->getsellerName() == sellerName)
            {
                inv.removeProduct(inv.getIndex(tempProd));
            }
            else
            {
                cout << "You have no authorithy to remove product" << endl;
            }
        }
        cout << "Product not found in the inventory." << endl;
    }

    void updateProductQuantity(int tempID, string sellerName)
    {
        int q;
        Product *tempProd = inv.searchProduct_ID(tempID);
        if (tempProd)
        {
            if (tempProd->getsellerName() == sellerName)
            {
                cout << "Enter quantity to change (if decrement use '-'):" << endl;
                cin >> q;
                int newq = tempProd->getStockQuantity() + q;
                tempProd->setStockQuantity(newq);
                cout << "Product quantity updated successfully!" << endl;
                return;
            }
            else
            {
                cout << "You have no authorithy to remove product" << endl;
            }
        }
        cout << "Product not found in the inventory." << endl;
    }

    // Function to display the products in the store inventory.
    void displayStoreProducts(string sellerName) const
    {
        inv.displaySellerProducts(sellerName);
    }
};
