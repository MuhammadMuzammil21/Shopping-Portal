#include <iostream>
using namespace std;

class Heap_Node {
public:
	Product key;
	Heap_Node* left;
	Heap_Node* right;
	int h;
	Heap_Node(){
		left = NULL; 
		right = NULL;
		h = 0;
	}	
	Heap_Node (Product x){
		key = x;
		left = NULL; 
		right = NULL;
		h = 0;
	}
};

class MaxHeapTree {
public:
	Heap_Node * root;
	MaxHeapTree (){
		root = NULL;	
	}
	
	int height(Heap_Node* node){
		if (node == NULL){
			return -1;
		}
		else {
			return node->h;
		}
	}
	
	int max(int x, int y){
		if (x > y){
			return x;
		}
		else {
			return y;
		}
	}
	
	bool isFull(Heap_Node* temp){
		int x, y;
		if (temp == NULL){
			return 1; 
		}
		if ((temp->left == NULL && temp->right == NULL) || (temp->left != NULL && temp->right != NULL)){
			x = isFull(temp->left);
			y = isFull(temp->right);
			if (x == 1 && y == 1){
				return 1;
			}
		}
		return 0;
	}
	
	void insert (Product key){
		root = insertion (root, key);
		//cout << "r: " << root->h << endl;
	}
	
	Heap_Node* insertion (Heap_Node* temp, Product key){
		int child;
		Heap_Node* new_node = new Heap_Node(key);
		//cout << key << endl;
		if (temp == NULL){
			return new_node;
		}
		else if (temp->left == NULL){
			temp->left = new_node;
			child = 1;
		}
		else if (temp->right == NULL){
			temp->right = new_node;
			child = 0;
		}
		else if (temp->left->h <= temp->right->h && isFull(temp->right)){
			temp->left = insertion(temp->left, key);
			child = 1;
		}
		else if (temp->left->h <= temp->right->h && !isFull(temp->right)){
			temp->right = insertion(temp->right, key);
			child = 0;
		}
		else if (temp->left->h > temp->right->h && !isFull(temp->left)){
			temp->left = insertion(temp->left, key);
			child = 1;
		}
		else if (temp->left->h > temp->right->h && isFull(temp->left)){
			temp->right = insertion(temp->right, key);
			child = 0;
		}
		temp->h = 1 + max(height(temp->left), height(temp->right));
		
		heapify_Insertion(temp, child);
		
		return temp;
	}
	
	void heapify_Insertion (Heap_Node* temp, int child){ //Bottom to Up
		if (child == 1){ //If left child
			if (temp->key.getRating() < temp->left->key.getRating()){
				swap(temp->key, temp->left->key);
			}
		}
		else {
			if (temp->key.getRating() < temp->right->key.getRating()){
				swap(temp->key, temp->right->key);
			}
		}
	}
};

