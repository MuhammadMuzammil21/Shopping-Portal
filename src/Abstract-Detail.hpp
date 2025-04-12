#include <iostream>
using namespace std;

/*
Need to incorporate:
Order History:
●	Data Structure: Doubly Linked List
●	Algorithm: Use a doubly linked list to maintain a user's order history for easy navigation and retrieval.
*/

class Shopping_Portal
{ // Main Portal
public:
	/* Features:
	- Main Portal Console
	- Product Recommendation
	*/
	void MainPortal();
	void ProductRecom(); // Uses a graph-based recommendation system.
};

class Product
{
public:
};

class Inventory
{
public:
	/* Features:
	- Searching interpolation search
	- Sorting
		Quicksort to display products in sorted order.*/
	void Searching(); // Uses a interpolation sort data structure for efficient product searching.{name,id}
	void Sorting();	  // Uses Quicksort for sorting products.{name , id , price}
};

class Shopping_Cart
{
	Inventory *inv;

public:
	/* Features:
	- Purchasing History
	1.Filing
	2.Last 5 orders
	*/
	// Features include managing a shopping cart.
	// Uses a linked list to manage items in the cart efficiently.
};

class Retailer_Store
{
	Inventory *inv;

public:
	/* Features:
	- Selling History
	1.Filing
	2.Last 5 orders
	-Global History
	*/
};

class User
{ // Parent Class of customer and seller
public:
	/* Features:
	- Account Management
	- User Authentication
	-

	# Uses a hash table for quick access and secure authentication.
	*/
};

class Customer : public User
{
	Shopping_Cart *cart; // Uses a linked list to manage the shopping cart.

public:
	/* Features:
	- Shopping Cart
	- Review and Rating
	- Product Recommendation

	# Uses a binary (max) heap for efficiently displaying top-rated products and managing user reviews.
	*/
};

class Seller : public User
{
	Retailer_Store *store;
	string SellerName;

public:
	/* Features:
	- Retailer Store
	- Uses an array or hash map for inventory management.
	*/
};

class Admin
{ // Optional
public:
	/* Features:
	 */
};