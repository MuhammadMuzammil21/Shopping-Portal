#include <iostream>
#include <fstream>
#include "ProductClass.hpp"
#include "productRecom.h"
#ifndef INVENTORYCLASS
#define INVENTORYCLASS 1
using namespace std;

class Inventory
{
private:
	Product *products; // Dynamic array to store Product objects in the inventory.
	int size;
	int capacity;

	void swapProducts(int, int);
	int interpolation(int, int, int);
	int binarySearch(int, int, string);
	int Partition_ID(int, int);
	void QuickSort_ID(int, int);
	void quicksort_ID(int);
	int Partition_price(int, int);
	void QuickSort_price(int, int);
	void quicksort_price(int);
	int Partition_name(int, int);
	void QuickSort_name(int, int);
	void quicksort_name(int);
	Heap_Node *CreateHeap(int);

public:
	Inventory()
	{
		products = new Product[2];
		capacity = 2;
		size = 0;
	}
	// Function to add a new product to the inventory.
	void addProduct(Product passedProduct)
	{
		Product newProduct(passedProduct); // Create a new Product object.
		if (size + 1 < capacity)
		{
			products[size] = newProduct; // Add the new product to the array.
			size++;
			cout << "Product added successfully!" << endl;
		}
		else
		{
			capacity *= 2;
			Product *newProducts = new Product[capacity];
			for (int i = 0; i < size; i++)
				newProducts[i] = products[i];
			delete[] products;
			products = newProducts;
			newProducts[size] = newProduct;
			size++;
		}
	}
	void removeProduct(int index)
	{
		if (index >= size)
		{
			cout << "Error in inventory product removal" << endl;
			return;
		}
		if (capacity / 2 != 0 && capacity / 2 > size - 1)
		{
			capacity /= 2;
			Product *newProducts = new Product[capacity];
			for (int i = 0; i < index; i++)
				newProducts[i] = products[i];
			for (int i = index, j = index + 1; i < size - 1; i++, j++)
			{
				newProducts[i] = products[j];
			}
			size--;
		}
		else
		{
			for (int i = index, j = index + 1; i < size - 1; i++, j++)
			{
				products[i] = products[j];
			}
			size--;
		}
	}

	int getIndex(Product *product)
	{
		return product - products;
	}

	bool saveToFile(const string &fname = "inventory.csv")
	{
		fstream file(fname, ios::out);
		if (!file.is_open())
		{
			cout << "Error opening file: " << fname << endl;
			return false;
		}
		sortProduct_ID();
		file << "ProductID,Product Name,Price,Quantity,Rating Sum,Total Ratings,Seller Name,Category Number" << endl;
		for (int i = 0; i < size; i++)
		{
			products[i].writeToFile(file);
		}
		return true;
	}
	bool loadFromFile(const string &fname = "inventory.csv")
	{
		FILE *file = fopen(fname.c_str(), "r");
		if (!file)
		{
			cout << "Error opening file: " << fname << endl;
			return false;
		}
		fscanf(file, "ProductID,Product Name,Price,Quantity,Rating Sum,Total Ratings,Seller Name,Category Number\n");
		while (!feof(file))
		{
			Product tempProduct;
			int scannedNum = tempProduct.readFromFile(&file);
			if (scannedNum != 8)
			{
				cout << "CSV File format error." << endl;
				return false;
			}
			addProduct(tempProduct);
		}
		return true;
	}
	bool empty() const { return size == 0; }
	// Function to display information about all products in the inventory.
	void displayAllProducts() const
	{
		if (empty())
		{
			cout << "No products in the inventory." << endl;
		}
		else
		{
			cout << "All Products" << endl;
			Product::displayHeader();
			for (int i = 0; i < size; i++)
			{
				products[i].displayProduct();
			}
			Product::displayFooter();
		}
	}

	void displaySellerProducts(string sellerName) const
	{
		if (empty())
		{
			cout << "No products in the inventory." << endl;
		}
		else
		{
			cout << sellerName << "'s Products" << endl;
			Product::displayHeader();
			for (int i = 0; i < size; i++)
			{
				if (products[i].getsellerName() == sellerName)
				{
					products[i].displayProduct();
				}
			}
			Product::displayFooter();
		}
	}

	void sortProduct_ID()
	{
		quicksort_ID(size);
	}

	void sortProduct_price()
	{
		quicksort_price(size);
	}

	void sortProduct_name()
	{
		quicksort_name(size);
	}

	Product *searchProduct_ID(int target)
	{
		sortProduct_ID();
		int i = interpolation(0, size - 1, target);
		if (i == -1)
		{
			cout << "Not found!" << endl;
			return NULL;
		}
		else
		{
			return &products[i];
		}
	}

	Product *searchProduct_name(string target)
	{
		sortProduct_name();
		int i = binarySearch(0, size - 1, target);
		if (i == -1)
		{
			cout << "Not found!" << endl;
			return NULL;
		}
		else
		{
			return &products[i];
		}
	}

	void ProductRecom()
	{
		int cat;
		cout << "0. ELECTRONICS" << endl;
		cout << "1. CLOTHING" << endl;
		cout << "2. HOUSEHOLD" << endl;
		cout << "3. STATIONARY" << endl;
		cout << "4. OTHERS" << endl;
		cout << "Select category: ";
		cin >> cat;
		Heap_Node *temp = CreateHeap(cat);
		system("cls");
		cout << "---------Recommended!!-----------" << endl;
		Product::displayHeader();
		temp->key.displayProduct();
	}
};

void Inventory::swapProducts(int i, int j)
{
	Product t;
	t = products[j];
	products[j] = products[i];
	products[i] = t;
}

int Inventory::interpolation(int l, int h, int target)
{
	int mid;
	while (l <= h)
	{
		mid = l + ((target - products[l].getID()) * (h - l) / (products[h].getID() - products[l].getID()));
		if (products[mid].getID() == target)
		{
			return mid;
		}
		else if (products[mid].getID() < target)
		{
			l = mid + 1;
		}
		else if (products[mid].getID() > target)
		{
			h = mid - 1;
		}
	}
	return -1;
}

int Inventory::binarySearch(int l, int h, string target)
{
	int mid;
	while (l <= h)
	{
		mid = (l + h) / 2;
		if (products[mid].getName() == target)
		{
			return mid;
		}
		else if (products[mid].getName() < target)
		{
			l = mid + 1;
		}
		else if (products[mid].getName() > target)
		{
			h = mid - 1;
		}
	}
	return -1;
}

int Inventory::Partition_ID(int l, int h)
{
	int i, j;
	int pivot = products[l].getID();
	i = l;
	j = h;
	while (i < j)
	{
		do
		{
			i++;
		} while (products[i].getID() <= pivot);
		do
		{
			j--;
		} while (products[j].getID() > pivot);
		if (i < j)
		{
			swapProducts(i, j);
		}
	}
	swapProducts(l, j);
	return j;
}

void Inventory::QuickSort_ID(int l, int h)
{
	int j;
	if (l < h)
	{
		j = Partition_ID(l, h);
		QuickSort_ID(l, j);
		QuickSort_ID(j + 1, h);
	}
}

void Inventory::quicksort_ID(int n)
{
	int i, max;
	for (i = 1, max = 0; i < n; i++)
	{
		if (products[max].getID() < products[i].getID())
		{
			max = i;
		}
	}
	swapProducts(n - 1, max);
	QuickSort_ID(0, n - 1);
}

int Inventory::Partition_price(int l, int h)
{
	int i, j;
	int pivot = products[l].getPrice();
	i = l;
	j = h;
	while (i < j)
	{
		do
		{
			i++;
		} while (products[i].getPrice() <= pivot);
		do
		{
			j--;
		} while (products[j].getPrice() > pivot);
		if (i < j)
		{
			swapProducts(i, j);
		}
	}
	swapProducts(l, j);
	return j;
}

void Inventory::QuickSort_price(int l, int h)
{
	int j;
	if (l < h)
	{
		j = Partition_price(l, h);
		QuickSort_price(l, j);
		QuickSort_price(j + 1, h);
	}
}

void Inventory::quicksort_price(int n)
{
	int i, max;
	for (i = 1, max = 0; i < n; i++)
	{
		if (products[max].getPrice() < products[i].getPrice())
		{
			max = i;
		}
	}
	swapProducts(n - 1, max);
	QuickSort_price(0, n - 1);
}

int Inventory::Partition_name(int l, int h)
{
	int i, j;
	string pivot = products[l].getName();
	i = l;
	j = h;
	while (i < j)
	{
		do
		{
			i++;
		} while (products[i].getName() <= pivot);
		do
		{
			j--;
		} while (products[j].getName() > pivot);
		if (i < j)
		{
			swapProducts(i, j);
		}
	}
	swapProducts(l, j);
	return j;
}

void Inventory::QuickSort_name(int l, int h)
{
	int j;
	if (l < h)
	{
		j = Partition_name(l, h);
		QuickSort_name(l, j);
		QuickSort_name(j + 1, h);
	}
}

void Inventory::quicksort_name(int n)
{
	int i, max;
	for (i = 1, max = 0; i < n; i++)
	{
		if (products[max].getName() < products[i].getName())
		{
			max = i;
		}
	}
	swapProducts(n - 1, max);
	QuickSort_name(0, n - 1);
}

Heap_Node *Inventory::CreateHeap(int cat)
{ // If Category is added then pass Category string
	MaxHeapTree b;
	int ch;
	if (empty())
	{
		cout << "No products in the inventory." << endl;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			switch (products[i].getCategory())
			{
			case Category::ELECTRONICS:
				ch = 0;
				break;
			case Category::CLOTHING:
				ch = 1;
				break;
			case Category::HOUSEHOLD:
				ch = 2;
				break;
			case Category::STATIONARY:
				ch = 3;
				break;
			case Category::OTHERS:
				ch = 4;
				// Add more cases as needed
			}
			if (ch == cat)
			{
				b.insert(products[i]);
			}
		}
	}
	return b.root;
}

// int main()
//{
//     Inventory inv;
//     int n;
//     string f;
//     inv.loadFromFile();
//     //inv.displayAllProducts();
//
//	inv.sortProduct_name();
//	inv.displayAllProducts();
//     inv.ProductRecom();
//     return 0;
// }

#endif