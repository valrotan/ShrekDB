#pragma once
#include "BST.h"

template <typename T>
class BST_Node {
private:
	T data;
	int height;
	BST_Node* left;
	BST_Node* right;
	template<typename U> friend class BST; 
public:
	BST_Node(T data, int h);
	BST_Node(T data, int h, BST_Node*, BST_Node*);
	int getHeight();
	void setHeight(int);
	T getData();
	void setData(T);
	BST_Node getLeft();
	void setLeft(BST_Node*);
	BST_Node getRight();
	void setRight(BST_Node*);
};

template <typename T>
BST_Node<T>::BST_Node(T d, int h) {
	data = d;
	height = h;
	left = nullptr;
	right = nullptr;
}

template <typename T>
BST_Node<T>::BST_Node(T d, int h, BST_Node* l, BST_Node* r) {
	data = d;
	left = l;
	right = r;
	height = h;
}

template <typename T>
T BST_Node<T>::getData() {
	return data;
}

template <typename T>
void BST_Node<T>::setData(T d) {
	data = d;
}

template <typename T>
BST_Node<T> BST_Node<T>::getLeft() {
	return left;
}

template <typename T>
void BST_Node<T>::setLeft(BST_Node<T>* l) {
	left = l;
}

template <typename T>
BST_Node<T> BST_Node<T>::getRight() {
	return right;
}

template <typename T>
void BST_Node<T>::setRight(BST_Node<T>* r) {
	right = r;
}

template <typename T>
int BST_Node<T>::getHeight() {
	return height;
}

template <typename T>
void BST_Node<T>::setHeight(int h) {
	height = h;
}