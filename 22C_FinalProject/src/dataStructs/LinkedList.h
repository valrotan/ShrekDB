// CIS22CH
// Lab 3B: Stacks and queues
// Taras Priadka

#pragma once
#include "LinkNode.h"
#include <iostream>

enum SORT_STATE {NO_SORT, ASCENDING, DESCENDING};

template <typename T>
class LinkedList {
private:
	int count;
	LinkNode<T> *head;
	LinkNode<T> *tail;
	SORT_STATE sorted;
public:
	LinkedList();
	LinkedList(SORT_STATE);
	virtual ~LinkedList();

	// Adds a node to the list, depends on the SORT_STATE
	// PRE: data - pointer to the data
	// POST: node is allocated and added to the list
	// returns: success message
	int add(T *data);

	// Removes specified node from the list
	// PRE: node - the number of node you wish to remove
	// POST: node at that index is removed
	// returns: data pointer at that node
	T* remove(int node);

	// Returns data at specified node
	// PRE: node - index of node you wish to get dasta from
	// POST: pointer is returned
	// returns: pointer to data
	T* getData(int node);

	//Getters for count and sorted state
	int getCount();
	SORT_STATE getSorted();

	// empties the linked list
	// PRE: void
	// POST: the list is emptied and memory is freed
	// returns: success status
	int emptyList();

	template <typename U>
	friend std::ostream& operator <<(std::ostream&, LinkedList<U>&);
};

template <typename T>
LinkedList<T>::~LinkedList() {
	emptyList();
	delete head;
}

template <typename T>
LinkedList<T>::LinkedList() {
	count = 0;
	head = new LinkNode<T>(); // sentinel node
	head->next = nullptr;
	tail = head;
	sorted = NO_SORT;
}

template <typename T>
LinkedList<T>::LinkedList(SORT_STATE a) {
	count = 0;
	head = new LinkNode<T>(); // sentinel node
	head->next = nullptr;
	tail = head;
	sorted = a;
}

template <typename T>
int LinkedList<T>::add(T *data) {
	LinkNode<T>* adding = new LinkNode<T>(data);
	if (count <= 0) {
		head->next = adding;
		tail = adding;
		count = 1;
	}
	else if (sorted == NO_SORT) {
		tail->next = adding;
		tail = adding;
		count++;
	}
	else if (sorted == ASCENDING) {
		LinkNode<T>* tempHead = head->next;
		LinkNode<T>* slow = head;
		while (tempHead != nullptr  && *(tempHead->data) < *data) {
			slow = slow->next;
			tempHead = tempHead->next;
		}
		slow->next = adding;
		adding->next = tempHead;
		count++;
	}
	else if (sorted == DESCENDING) {
		LinkNode<T>* tempHead = head->next;
		LinkNode<T>* slow = head;
		while (tempHead != nullptr && *(tempHead->data) > *data) {
			slow = slow->next;
			tempHead = tempHead->next;
		}
		slow->next = adding;
		adding->next = tempHead;
		count++;
	}
	return 0;
}

template <typename T>
T* LinkedList<T>::remove(int node) {
	int i = 0;
	LinkNode<T>* iterator = head;
	while (i < node) {
		if (iterator->next == nullptr || i > count)
			return nullptr;
		iterator = iterator->next;
		i++;
	}
	if (iterator->next == nullptr)
		return nullptr;
	LinkNode<T>* remove = iterator->next;
	iterator->next = remove->next;
	count--;
	T* out = remove->data;
	delete remove;
	return out;
}

template <typename T>
T* LinkedList<T>::getData(int node) {
	int i = 0;
	LinkNode<T>* iterator = head;
	while (i < node) {
		if (iterator->next == nullptr || i > count)
			return nullptr;
		iterator = iterator->next;
		i++;
	}
	if (iterator->next == nullptr)
		return nullptr;
	return iterator->next->data;	
}

template <typename T>
int LinkedList<T>::getCount() {
	return count;
}

template <typename T>
SORT_STATE LinkedList<T>::getSorted() {
	return sorted;
}

template <typename T>
int LinkedList<T>::emptyList() {
	while (head->next != nullptr) {
		LinkNode<T>* temp = head->next;
		head->next = head->next->next;
		temp->next = nullptr;
		delete temp;
	}
	count = 0;
	head->next = nullptr;
	tail = nullptr;
	return 0;
}

template <typename T>
std::ostream& operator <<(std::ostream& out, LinkedList<T>& list) {
	LinkNode<T> *head = list.head->getNext();
	while (head != nullptr) {
		out << *(head->getData()) << ", "; 
		head = head->getNext();
	}
	return out;
}
