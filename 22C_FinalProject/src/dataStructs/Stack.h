#pragma once

#include "LinkedList.h"

template <typename T>
class Stack : protected LinkedList<T> {
public:
	~Stack();

	// Pops the list item at the front of the stack
	// Pre: void
	// Post: stack's top item is removed
	// returns: top data
	T pop();

	// Pushes data to the top of the stack
	// Pre: data to be inserted
	// Post: data is added to the top of the stack
	// returns: void
	void push(T data);

	// Shows the item at the top of the stack
	// Pre: void
	// Post: data is retured
	// returns: pointer to the data at the top
	T top();

	// Empties the stack and frees the nodes
	// Pre: void
	// Post: all nodes are removed and freed
	// returns: void
	void empty();

	//check if stack is empty
	bool isEmpty();

	template <typename U>
	friend std::ostream& operator <<(std::ostream& out, Stack<U>& queue);
};

template<typename T>
bool Stack<T>::isEmpty() {
	return this->getCount() <= 0;
}


template<typename T>
T Stack<T>::top()
{
	return this->getData(this->getCount() - 1);
}

template<typename T>
void Stack<T>::empty()
{
	this->emptyList();
}

template<typename T>
Stack<T>::~Stack(){}

template<typename T>
T Stack<T>::pop()
{
	return this->remove(this->getCount()-1);
}

template<typename T>
void Stack<T>::push(T data)
{
	this->add(data);
}

template <typename T>
std::ostream& operator <<(std::ostream& out, Stack<T>& list) {
	for (int i = 0; i < list.getCount(); i++) {
		out << list.getData(i) << " ";
	}
	return out;
}