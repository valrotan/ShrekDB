// CIS22CH
// Lab 3B: Stacks and queues
// Taras Priadka

#pragma once
#include "LinkedList.h"
#include <iostream>

template <typename T>
class LinkNode {
private:
	T* data;
	LinkNode<T>* next;
	bool sentinel;
	template<typename U> friend class LinkedList;
public:
	LinkNode(T* data);

	LinkNode();
	// getters and setters for data and next
	T* getData() { return data; }
	void setNext(LinkNode<T> *n) { next = n; }
	LinkNode<T>* getNext() { return next; }
};

template <typename T>
LinkNode<T>::LinkNode(T *d) {
	data = d;
	sentinel = false;
	next = nullptr;
}

template <typename T>
LinkNode<T>::LinkNode() {
	data = nullptr;
	sentinel = true;
	next = nullptr;
}



