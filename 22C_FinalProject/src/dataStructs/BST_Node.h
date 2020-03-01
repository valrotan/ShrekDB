#pragma once
#include "BST.h"

template <typename T>
class BST_Node {
private:
	template <typename U>
	friend class BST;

	T data;
	BST_Node *left;
	BST_Node *right;

public:
	// constructors
	BST_Node(T data);
	BST_Node(T data, BST_Node *l, BST_Node *r);

	// Getters and setters:
	T getData() const;
	void setData(const T &value);
	BST_Node *getLeft() const;
	void setLeft(BST_Node *value);
	BST_Node *getRight() const;
	void setRight(BST_Node *value);
};

template <typename T>
BST_Node<T>::BST_Node(T d) : data(d), left(nullptr), right(nullptr) {}

template <typename T>
BST_Node<T>::BST_Node(T d, BST_Node *l, BST_Node *r)
		: data(d), left(l), right(r) {}

template <typename T>
T BST_Node<T>::getData() const {
	return data;
}

template <typename T>
void BST_Node<T>::setData(const T &value) {
	data = value;
}

template <typename T>
BST_Node<T> *BST_Node<T>::getLeft() const {
	return left;
}

template <typename T>
void BST_Node<T>::setLeft(BST_Node *value) {
	left = value;
}

template <typename T>
BST_Node<T> *BST_Node<T>::getRight() const {
	return right;
}

template <typename T>
void BST_Node<T>::setRight(BST_Node *value) {
	right = value;
}
