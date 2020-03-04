#pragma once
#include "../util/comparator.h"
#include "LinkNode.h"
#include <iostream>

enum SORT_STATE { NO_SORT, ASCENDING, DESCENDING };

template <typename T>
class LinkedList {
private:
	int count;
	LinkNode<T> *head;
	LinkNode<T> *tail;
	SORT_STATE sorted;
	Comparator<T> *comparator;

public:
	LinkedList();
	LinkedList(const LinkedList &);
	LinkedList(SORT_STATE);
	LinkedList(const Comparator<T> &comp);
	LinkedList(SORT_STATE, const Comparator<T> &comp);
	virtual ~LinkedList();

	/* Find index of data
	 * Post: index of data in list is returned. -1 if not found
	 */
	int find(const T &data);

	// Adds a node to the list, depends on the SORT_STATE
	// PRE: data - pointer to the data
	// POST: node is allocated and added to the list
	// returns: success message
	int add(const T &data);

	// Removes specified node from the list
	// PRE: node - the number of node you wish to remove
	// POST: node at that index is removed
	// returns: data pointer at that node
	T remove(int node);

	// Returns data at specified node
	// PRE: node - index of node you wish to get dasta from
	// POST: pointer is returned
	// returns: pointer to data
	T getData(int node);

	// Getters for count and sorted state
	int getCount();
	SORT_STATE getSorted();

	// empties the linked list
	// PRE: void
	// POST: the list is emptied and memory is freed
	// returns: success status
	int emptyList();

	template <typename U>
	friend std::ostream &operator<<(std::ostream &, LinkedList<U> &);
};

template <typename T>
LinkedList<T>::~LinkedList() {
	emptyList();
	delete head;
	delete comparator;
}

template <typename T>
LinkedList<T>::LinkedList() {
	count = 0;
	head = new LinkNode<T>(); // sentinel node
	head->next = nullptr;
	tail = head;
	sorted = NO_SORT;
	comparator = new GenericComparator<T>;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList &oldobj) {
	count = oldobj.count;
	head = oldobj.head; // sentinel node
	tail = oldobj.tail;
	sorted = oldobj.sorted;
	comparator = oldobj.comparator;
}

template <typename T>
LinkedList<T>::LinkedList(SORT_STATE a) {
	count = 0;
	head = new LinkNode<T>(); // sentinel node
	head->next = nullptr;
	tail = head;
	sorted = a;
	comparator = new GenericComparator<T>;
}

template <typename T>
LinkedList<T>::LinkedList(const Comparator<T> &comp) {
	count = 0;
	head = new LinkNode<T>(); // sentinel node
	head->next = nullptr;
	tail = head;
	sorted = NO_SORT;
	comparator = comp.clone();
}

template <typename T>
LinkedList<T>::LinkedList(SORT_STATE a, const Comparator<T> &comp) {
	count = 0;
	head = new LinkNode<T>(); // sentinel node
	head->next = nullptr;
	tail = head;
	sorted = a;
	comparator = comp.clone();
}

template <typename T>
int LinkedList<T>::add(const T &data) {
	LinkNode<T> *adding = new LinkNode<T>(data);
	if (count <= 0) {
		head->next = adding;
		tail = adding;
		count = 1;
	} else if (sorted == NO_SORT) {
		tail->next = adding;
		tail = adding;
		count++;
	} else if (sorted == ASCENDING) {
		LinkNode<T> *tempHead = head->next;
		LinkNode<T> *slow = head;
		while (tempHead != nullptr &&
					 comparator->compare(tempHead->data, data) < 0) {
			slow = slow->next;
			tempHead = tempHead->next;
		}
		slow->next = adding;
		adding->next = tempHead;
		count++;
	} else if (sorted == DESCENDING) {
		LinkNode<T> *tempHead = head->next;
		LinkNode<T> *slow = head;
		while (tempHead != nullptr &&
					 comparator->compare(tempHead->data, data) > 0) {
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
int LinkedList<T>::find(const T &data) {
	LinkNode<T> *p = head->next;
	for (int i = 0; i < count; i++) {
		if (comparator->compare(p->data, data) == 0) {
			return i;
		}
		p = p->next;
	}
	return -1;
}

template <typename T>
T LinkedList<T>::remove(int node) {
	int i = 0;
	LinkNode<T> *iterator = head;
	while (i < node) {
		if (iterator->next == nullptr || i > count)
			throw "Index out of bounds";
		iterator = iterator->next;
		i++;
	}
	if (iterator->next == nullptr)
		throw "Index out of bounds";
	LinkNode<T> *remove = iterator->next;
	iterator->next = remove->next;
	if (!iterator->next)
		tail = iterator;
	count--;
	T out = (*remove).data;
	delete remove;
	return out;
}

template <typename T>
T LinkedList<T>::getData(int node) {
	int i = 0;
	LinkNode<T> *iterator = head;
	while (i < node) {
		if (iterator->next == nullptr || i > count)
			throw "Index out of bounds";
		iterator = iterator->next;
		i++;
	}
	if (iterator->next == nullptr)
		throw "Index out of bounds";
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
	while (head->next) {
		LinkNode<T> *temp = head->next;
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
std::ostream &operator<<(std::ostream &out, LinkedList<T> &list) {
	LinkNode<T> *head = list.head->getNext();
	while (head != nullptr) {
		out << head->getData() << ", ";
		head = head->getNext();
	}
	return out;
}
