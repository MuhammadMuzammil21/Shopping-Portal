#ifndef PRODUCTCLASS_HPP
#define PRODUCTCLASS_HPP
using namespace std;

// Enum to represent different product categories
enum class Category
{
    ELECTRONICS = 0,
    CLOTHING = 1,
    HOUSEHOLD = 2,
    STATIONARY = 3,
    OTHERS = 4
    // Add more categories as needed
};

class Product
{
private:
    static int nextID;
    int productID;
    string name;
    double price;
    int stockQuantity;
    float rating;
    double ratingSum;
    int totalRatings;
    string sellerName;
    Category category; // New category attribute

public:
    Product() {}
    Product(const string &productName, double productPrice, int quantity, float productRating, Category productCategory, string sellerName)
        : productID(nextID++), name(productName), price(productPrice), stockQuantity(quantity), rating(productRating), category(productCategory),
          ratingSum(productRating), totalRatings(1), sellerName(sellerName) {}

    void addNewRating(float rating)
    {
        ratingSum += rating;
        totalRatings++;
        rating = ratingSum / totalRatings;
    }

    int getID() const
    {
        return productID;
    }

    string getName() const
    {
        return name;
    }

    double getPrice() const
    {
        return price;
    }

    int getStockQuantity() const
    {
        return stockQuantity;
    }

    int getRating() const
    {
        return rating;
    }

    Category getCategory() const
    {
        return category;
    }

    void setName(const string &newName)
    {
        name = newName;
    }

    void setPrice(double newPrice)
    {
        price = newPrice;
    }

    void setStockQuantity(int newQuantity)
    {
        stockQuantity = newQuantity;
    }

    void setRating(float rate)
    {
        rating = rate;
    }
    
    void setSellerName(string name)
    {
        sellerName = name;
    }

    void setCategory(Category newCategory)
    {
        category = newCategory;
    }
    string getCategoryString() const
    {
        switch (category)
        {
        case Category::ELECTRONICS:
            return "Electronics";
            break;
        case Category::CLOTHING:
            return "Clothing";
            break;
        case Category::HOUSEHOLD:
            return "Household";
            break;
        case Category::STATIONARY:
            return "Stationary";
            break;
        case Category::OTHERS:
            return "Others";
            // Add more cases as needed
        }
        return "error";
    }
    string getsellerName() { return sellerName; }
    void displayProductOld() const
    {
        cout << "Product ID: " << productID << endl;
        cout << "Product Name: " << name << endl;
        cout << "Category: ";
        cout << getCategoryString() << endl;
        cout << "Price: PKR " << price << endl;
        cout << "Stock Quantity: " << stockQuantity << endl;
        cout << "Rating: " << rating << endl;
        cout << "Seller: " << sellerName << endl;
    }
    static void displayHeader()
    {
        cout << " _______________________________________________________________________________________________________________\n";
        cout << "|  ID  | Product Name                 |   Category   |   Price PKR  | Quantity | Rating (/5) | Seller           |\n";
        cout << "|======|==============================|==============|==============|==========|=============|==================|\n";
    }
    void displayProduct() const
    {
        printf("| %4i | %-28s | %-12s | %12.2lf | %8i |     %1.1f     | %-16s |\n", productID, name.c_str(), getCategoryString().c_str(), price, stockQuantity, rating, sellerName.c_str());
    }
    static void displayFooter()
    {
        cout << "=================================================================================================================\n";
    }
    void sellProduct(int quantitySold)
    {
        if (quantitySold > 0 && quantitySold <= stockQuantity)
        {
            stockQuantity -= quantitySold;
        }
        else
        {
            cout << "Invalid quantity to sell." << endl;
        }
    }
    void writeToFile(fstream &file)
    {
        file << productID << ','
             << name << ','
             << price << ','
             << stockQuantity << ','
             << ratingSum << ','
             << totalRatings << ','
             << sellerName << ','
             << (int)category
             << endl;
    }
    int readFromFile(FILE **file)
    {
        FILE *File = *file;
        char tempStrName[255] = {0};
        char tempStrSellerName[255] = {0};
        int tempForCategory;
        int val = fscanf(File, "%d,%255[^,],%lf,%ld,%lf,%d,%255[^,],%d\n",
                         &productID,
                         tempStrName,
                         &price,
                         &stockQuantity,
                         &ratingSum,
                         &totalRatings,
                         tempStrSellerName,
                         &tempForCategory);
        rating = ratingSum / totalRatings;
        name = tempStrName;
        sellerName = tempStrSellerName;
        category = Category(tempForCategory);
        nextID = productID + 1;
        return val;
    }
};

// Initialize the static variable for product IDs
int Product::nextID = 1;
#endif
