#ifndef HISTORY_HPP
#define HISTORY_HPP
#include "ProductClass.hpp"

class History_Node
{
public:
    History_Node *next;
    Product &productData;
    float userRecentRating;
    History_Node(float rating, Product &p) : next(NULL), productData(p), userRecentRating(rating) {}
};

class History
{
    History_Node *histList_C;
    History_Node *histList_S;
    int size_C;
    int size_S;

public:
    History()
    {
        histList_C = NULL;
        histList_S = NULL;
        size_C = 0;
        size_S = 0;
    }
    ~History()
    {
        if (histList_C)
            delete[] histList_C;

        if (histList_S)
            delete[] histList_S;
    }
    void addToHistory_C(Product &p, float user_Rating)
    {
        if (histList_C == NULL)
        {
            histList_C = new History_Node(user_Rating, p);
            size_C++;
            return;
        }
        History_Node *newNode = new History_Node(user_Rating, p);
        newNode->next = histList_C;
        histList_C = newNode;
        size_C++;

        // free memory if size_C > 5 Optional.
    }
    void printHistory_C(unsigned numberOfItems = 5)
    {
        History_Node *tempNode = histList_C;
        if (tempNode == NULL)
        {
            cout << "History is currently empty. Check back later..." << endl;
            getch();
            return;
        }
        cout << "Recently bought products: " << endl;
        cout << "-------------------------------------" << endl;
        int count = 0;
        Product::displayHeader();
        while (tempNode != NULL && count++ < numberOfItems)
        {

            tempNode->productData.displayProduct();
            cout << "| The last purchase's user rated this product a ";
            printf("%1.1f", tempNode->userRecentRating);
            cout << "                                                             |" << endl;
            cout << "|                                                                                                               |" << endl;
            tempNode = tempNode->next;
        }
        Product::displayFooter();
        getch();
    }

    void printHistory_S(string sname, unsigned numberOfItems = 5)
    {
        History_Node *tempNode = histList_C;
        if (tempNode == NULL)
        {
            cout << "History is currently empty. Check back later..." << endl;
            getch();
            return;
        }
        cout << "Recently bought products from your store: " << endl;
        cout << "-------------------------------------" << endl;
        int count = 0;
        Product::displayHeader();
        while (tempNode != NULL && count < numberOfItems)
        {
            if (tempNode->productData.getsellerName() == sname)
            {
                tempNode->productData.displayProduct();
                cout << "| The last purchase's user rated this product a ";
                printf("%1.1f", tempNode->userRecentRating);
                cout << "                                                             |" << endl;
                cout << "|                                                                                                               |" << endl;
                count++;
            }
            tempNode = tempNode->next;
        }
        Product::displayFooter();
        cout << "Press any key to continue..." << endl;
        getch();
    }
} GlobalHistory;

/*
TEST:
1
Asim
1234
2
1
7

*/

#endif