// CIS22CH
// Lab 3B: Stacks and queues
// Taras Priadka
#pragma once

#include "LinkedList.h"

template <typename T>
class Queue : protected LinkedList<T> {
public:
	~Queue();

	// Dequeues list item from the front
	// Pre: void
	// Post: first item is removed
	// returns: the item dequeued or nullptr if it isn't present
	T* dequeue();

	// Enqueues list item to the end
	// Pre: data to be inserted
	// Post: data is added to the back
	// returns: void
	void enqueue(T* data);

	// Shows the item at the front of the queue
	// Pre: void
	// Post: data is retured
	// returns: pointer to the data at the front
	T* front();

	// Shows the item at the rear of the queue
	// Pre: void
	// Post: data is retured
	// returns: pointer to the data at the rear
	T* rear();

	// Empties the queue and frees the nodes
	// Pre: void
	// Post: all nodes are removed and freed
	// returns: void
	void empty();
};

template<typename T>
T* Queue<T>::front()
{
	return this->getData(0);
}

template<typename T>
T* Queue<T>::rear()
{
	return this->getData(this->getCount() - 1);
}

template<typename T>
void Queue<T>::empty()
{
	this->emptyList();
}

template<typename T>
Queue<T>::~Queue()
{
	this->emptyList();
}

template<typename T>
T* Queue<T>::dequeue()
{
	return this->remove(0);
}

template<typename T>
void Queue<T>::enqueue(T* data)
{
	this->add(data);
}