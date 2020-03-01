#pragma once

#include "BST_Node.h"
#include "Queue.h"
#include "LinkedList.h"
#include <string>
#include <iostream>

template <typename T>
class BST {
private:
	BST_Node<T> *root;
	BST_Node<T>* findLargest(BST_Node<T>*);
	BST_Node<T>* findSmallest(BST_Node<T>*);
	BST_Node<T>* searchHelper(BST_Node<T>*, T);
	BST_Node<T>* removeHelper(BST_Node<T>* root, T key);
	void preOrderTravHelper(BST_Node<T>* root, std::ostream& out);
	void inOrderTravHelper(BST_Node<T>* root, std::ostream& out);
	void postOrderTravHelper(BST_Node<T>* root, std::ostream& out);
public:
	BST(T data);
	BST();
	BST_Node<T>* createNode(T data, int h);
	~BST();

	//add/remove
	void add(T data);
	T remove(T key);
	
	//utils
	void empty();
	bool isEmpty();
	int count();
	bool contains(T key);

	//search
	T search(T key);
	
	//find largest/smallest
	T findLargestData();
	T findSmallestData();

	//traversals
	void breadthFirstTrav(std::ostream& out);
	void preOrderTrav(std::ostream& out);
	void inOrderTrav(std::ostream& out);
	void postOrderTrav(std::ostream& out);
	std::string printTree(int);



};

template <typename T>
BST<T>::BST() {
	root = nullptr;
}

template <typename T>
BST<T>::BST(T data) {
	root = new BST_Node<T>(data, 0);
}

template <typename T>
BST_Node<T>* BST<T>::createNode(T data, int h) {
	return new BST_Node<T>(data, h);
}

template <typename T>
BST<T>::~BST() {
	empty();
}

template<typename T>
T BST<T>::findLargestData() {
	return findLargest(this->root)->getData();
}

template<typename T>
T BST<T>::findSmallestData() {
	return findSmallest(this->root)->getData();
}

template<typename T>
BST_Node<T>* BST<T>::findLargest(BST_Node<T>* root) {
	if (root->right)
		return findLargest(root->right);
	return root;
}

template<typename T>
BST_Node<T>* BST<T>::findSmallest(BST_Node<T>* root) {
	if (root->left)
		return findSmallest(root->left);
	return root;
}

template <typename T>
void BST<T>::add(T data) {
	BST_Node<T>* newNode = createNode(data, 0);

	if (this->root == nullptr)
		root = newNode;
	else {
		BST_Node<T>* pWalk = this->root;
		BST_Node<T>* parent = pWalk;
		while (pWalk) {
			parent = pWalk;
			newNode->height += 1;
			if (newNode->data < pWalk->data) {
				pWalk = pWalk->left;
			}
			else {
				pWalk = pWalk->right;
			}
		}
		if (newNode->data > parent->data)
			parent->right = newNode;
		else
			parent->left = newNode;
	}
	return;
}

template <typename T>
T BST<T>::remove(T key) {
	BST_Node<T>* node = removeHelper(this->root, key);
	if (node)
		return node->data;
	else
		throw "Not found";
}

template <typename T>
BST_Node<T>* BST<T>::removeHelper(BST_Node<T>* root, T key){
	if (!root) // if there's no root, return null
		return nullptr;
	if (key < root->data) // if key is less than root->data, assign root->left to the deleted node
		root->left = removeHelper(root->left, key);
	else if (key > root->data) // if more, assign the right child to be the deleted node
		root->right = removeHelper(root->right, key);
	else { // if you found the node
		if (root == this->root) {
			if (!root->left) { // if no left child, assign temp to left, delete current node and return temp 
				BST_Node<T>* temp = root->right;
				delete root;
				this->root = temp;
				return temp;
			}
			else if (!root->right) {
				BST_Node<T>* temp = root->left;
				delete root;
				this->root = temp;
				return temp;
			}
			else {
				// not a leaf
				BST_Node<T>* large = findLargest(root->left);
				root->data = large->data;
				root->left = removeHelper(root->left, large->data);
			}
		} else if (!root->left) { // if no left child, assign temp to left, delete current node and return temp 
			BST_Node<T>* temp = root->right;
			delete root;
			return temp;
		}
		else if (!root->right) {
			BST_Node<T>* temp = root->left;
			delete root;
			return temp;
		} else {
			// not a leaf
			BST_Node<T> *large = findLargest(root->left);
			root->data = large->data;
			root->left =  removeHelper(root->left, large->data);
		}
	}
	return root;
}

template <typename T>
void BST<T>::empty() {
	while (this->root) {
		try {
			this->remove(this->root->data);
		}
		catch (...) {
		
		}
	}
}

template<typename T>
bool BST<T>::isEmpty() {
	return root == nullptr;
}

template<typename T>
int BST<T>::count() {
	int count = 0;
	Queue<BST_Node<T>*> queue;
	queue.enqueue(this->root);
	while (!queue.isEmpty()) {
		BST_Node<T>* root = queue.dequeue();
		count++;
		if (root->left)
			queue.enqueue(root->left);
		if (root->right)
			queue.enqueue(root->right);
	}
	return count;
}

template <typename T>
bool BST<T>::contains(T key) {
	BST_Node<T>* node = searchHelper(this->root, key);
	if (node)
		return true;
	else {
		return false;
	}
}

template <typename T>
T BST<T>::search(T key) {
	BST_Node<T>* node = searchHelper(this->root, key);
	if(node)
		return node->data;
	else {
		throw "Data doesn't exist";
	}
}

template <typename T>
BST_Node<T>* BST<T>::searchHelper(BST_Node<T>* root,T key) {
	if (!root)
		return nullptr;
	if (root->data == key)
		return root;
	else if (key < root->data)
		return searchHelper(root->left, key);
	else if (key > root->data)
		return searchHelper(root->left, key);
	return root;
}

template <typename T>
void BST<T>::breadthFirstTrav(std::ostream& out) {
	Queue<BST_Node<T>*> queue;
	queue.enqueue(this->root);
	while (!queue.isEmpty()) {
		BST_Node<T>* root = queue.dequeue();
		out << root->data << std::endl;
		if (root->left)
			queue.enqueue(root->left);
		if (root->right)
			queue.enqueue(root->right);
	} 
	
}

template <typename T>
void BST<T>::preOrderTrav(std::ostream& out) {
	preOrderTravHelper(this->root, out);
}

template <typename T>
void BST<T>::preOrderTravHelper(BST_Node<T>* root, std::ostream& out) {
	if (!root)
		return;
	out << root->data << std::endl;
	preOrderTravHelper(root->left, out);
	preOrderTravHelper(root->right, out);
}

template <typename T>
void BST<T>::inOrderTrav(std::ostream& out) {
	inOrderTravHelper(this->root, out);
}

template <typename T>
void BST<T>::inOrderTravHelper(BST_Node<T>* root, std::ostream& out) {
	if (!root)
		return;
	inOrderTravHelper(root->left, out);
	out << root->data << std::endl;
	inOrderTravHelper(root->right, out);
}

template <typename T>
void BST<T>::postOrderTrav(std::ostream& out) {
	postOrderTravHelper(this->root, out);
}

template <typename T>
void BST<T>::postOrderTravHelper(BST_Node<T>* root, std::ostream& out) {
	
	if (!root)
		return;
	postOrderTravHelper(root->left, out);
	postOrderTravHelper(root->right, out);
	out << root->data << std::endl;
}

template <typename T>
std::string BST<T>::printTree(int) {
	return 0;
}