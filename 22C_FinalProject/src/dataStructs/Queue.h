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
	T dequeue();

	// Enqueues list item to the end
	// Pre: data to be inserted
	// Post: data is added to the back
	// returns: void
	void enqueue(T data);

	// Shows the item at the front of the queue
	// Pre: void
	// Post: data is retured
	// returns: pointer to the data at the front
	T front();

	// Shows the item at the rear of the queue
	// Pre: void
	// Post: data is retured
	// returns: pointer to the data at the rear
	T rear();

	// Empties the queue and frees the nodes
	// Pre: void
	// Post: all nodes are removed and freed
	// returns: void
	void empty();

	//returns the number of elements in the queue
	int count();

	//check if queue is empty
	bool isEmpty();

	template <typename U>
	friend std::ostream& operator <<(std::ostream& out, Queue<U>& queue);
};

template<typename T>
T Queue<T>::front()
{
	return this->getData(0);
}

template<typename T>
bool Queue<T>::isEmpty() {
	return this->getCount() <= 0;
}


template<typename T>
int Queue<T>::count() {
	return this->getCount();
}


template<typename T>
T Queue<T>::rear()
{
	return this->getData(this->getCount() - 1);
}

template<typename T>
void Queue<T>::empty()
{
	this->emptyList();
}

template<typename T>
Queue<T>::~Queue(){}

template<typename T>
T Queue<T>::dequeue()
{
	return this->remove(0);
}

template<typename T>
void Queue<T>::enqueue(T data)
{
	this->add(data);
}


template <typename T>
std::ostream& operator <<(std::ostream& out, Queue<T>& list) {
	for (int i = 0; i < list.getCount(); i++) {
		out << list.getData(i) << " ";
	}
	return out;
}