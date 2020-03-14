#pragma once

#include "../util/comparator.h"
#include "../util/hasher.h"
#include "LinkedList.h"
#include "hashtableUnit.h"
#include <string>

template <typename K, typename T>
class HashTable {
private:
	int size;
	LinkedList<const HashtableUnit<K, T> *> **table; // table of linked lists
	int *listLengths;          // lengths of linked lists in the table
	Hasher<K> *hasher;         // used to generically hash keys
	Comparator<K> *comparator; // used to generically compare keys in the table

public:
	HashTable(const Hasher<K> &);
	HashTable(int, const Hasher<K> &);
	HashTable(int, const Comparator<T> &, const Hasher<K> &);
	~HashTable();

	// stats getters
	int getSize() { return size; }
	int getCount();
	double getLoad();
	int getMaxListSize();
	int getNumNodes();
	int getAverageNumNodes();

	// Insert an element into the table
	// Pre: K - key with datatype of K
	//		T - data to be inserted
	// Post: item is inserted into the table
	// Returns: success value
	bool insert(K, T);

	// Checks if the data exists in the table
	// Pre: K - key with datatype of K
	// Post: item is looked up in the table
	// Returns: existance value
	bool contains(K);

	// Removes element from the table
	// Pre: K - key with datatype of K
	// Post: item is deleted from the table
	// Returns: data that was deleted
	T remove(K);

	// Finds data in the table
	// Pre: K - key with datatype of K
	// Post: item is looked up in the table
	// Returns: data in the table
	T find(K);

	// Clear the list from all of the values
	void clear();

	// Prints in database format (only data line by line)
	void dbPrint(std::ostream &out);

	template <typename U, typename V>
	friend std::ostream &operator<<(std::ostream &, HashTable<U, V> &);
};

template <typename K, typename T>
HashTable<K, T>::HashTable(const Hasher<K> &h) {
	size = 10;
	listLengths = new int[size]{};
	comparator = new GenericComparator<K>;
	table = new LinkedList<const HashtableUnit<K, T> *> *[size];
	for (int i = 0; i < size; i++) {
		table[i] = new LinkedList<const HashtableUnit<K, T> *>(
				ASCENDING, UnitPointerComparator<K, T>{});
	}
	hasher = h.clone();
}

template <typename K, typename T>
HashTable<K, T>::HashTable(int s, const Hasher<K> &h) {
	size = s;
	listLengths = new int[size]{};
	table = new LinkedList<const HashtableUnit<K, T> *> *[size];
	comparator = new GenericComparator<K>;
	for (int i = 0; i < size; i++) {
		table[i] = new LinkedList<const HashtableUnit<K, T> *>(
				ASCENDING, UnitPointerComparator<K, T>{});
	}
	hasher = h.clone();
}

template <typename K, typename T>
HashTable<K, T>::HashTable(int s, const Comparator<T> &comp,
													 const Hasher<K> &h) {
	size = s;
	listLengths = new int[size]{};
	table = new LinkedList<const HashtableUnit<K, T> *> *[size];
	comparator = comp.clone();

	for (int i = 0; i < size; i++) {
		table[i] = new LinkedList<const HashtableUnit<K, T> *>(
				ASCENDING, UnitPointerComparator<K, T>{});
	}
	hasher = h.clone();
}

template <typename K, typename T>
HashTable<K, T>::~HashTable() {
	delete hasher;
	delete comparator;
	delete listLengths;
	for (int i = 0; i < this->size; i++) {
		LinkedList<const HashtableUnit<K, T> *> *l = this->table[i];
		for (int j = 0; j < l->getCount(); j++) {
			delete l->getData(j);
		}
		delete l;
	}
}

template <typename K, typename T>
bool HashTable<K, T>::insert(K k, T data) {
	long key = hasher->hash(k, this->size);

	LinkedList<const HashtableUnit<K, T> *> *l = table[key];
	HashtableUnit<K, T> *in = new HashtableUnit<K, T>(k, data);
	if (l->find(in) != -1)
		throw "Exception: Duplicate key";
	listLengths[key]++;
	l->add(new HashtableUnit<K, T>(k, data));
	return true;
}

template <typename K, typename T>
T HashTable<K, T>::remove(K k) {
	long key = hasher->hash(k, this->size);
	LinkedList<const HashtableUnit<K, T> *> *l = table[key];
	for (int i = 0; i < l->getCount(); i++) {
		if (comparator->compare(l->getData(i)->getKey(), k) == 0) {
			return l->remove(i)->getData();
			listLengths[key]--;
		}
	};
	throw "Exception: element not found";
}

template <typename K, typename T>
T HashTable<K, T>::find(K k) {
	long key = hasher->hash(k, this->size);
	LinkedList<const HashtableUnit<K, T> *> *l = table[key];
	for (int i = 0; i < l->getCount(); i++) {
		if (comparator->compare(l->getData(i)->getKey(), k) == 0) {
			return l->getData(i)->getData();
		}
	};
	throw "Exception: element not found";
}

template <typename K, typename T>
bool HashTable<K, T>::contains(K k) {
	long key = hasher->hash(k, this->size);
	LinkedList<const HashtableUnit<K, T> *> *l = table[key];
	for (int i = 0; i < l->getCount(); i++) {
		if (comparator->compare(l->getData(i)->getKey(), k) == 0) {
			return true;
		}
	};
	return false;
}

template <typename K, typename T>
void HashTable<K, T>::clear() {
	for (int i = 0; i < this->size; i++) {
		listLengths[i] = 0;
		LinkedList<const HashtableUnit<K, T> *> *l = this->table[i];
		for (int j = 0; j < l->getCount(); j++) {
			delete l->getData(j);
		}
		l->emptyList();
	}
}

template <typename K, typename T>
std::ostream &operator<<(std::ostream &out, HashTable<K, T> &hashtable) {
	for (int i = 0; i < hashtable.size; i++) {
		LinkedList<const HashtableUnit<K, T> *> *l = hashtable.table[i];
		out << "Bucket " << i << ": " << std::endl;
		for (int j = 0; j < l->getCount(); j++) {
			out << "\t" << l->getData(j)->getData() << std::endl;
		}
	}

	return out;
}

template <typename K, typename T>
int HashTable<K, T>::getMaxListSize() {
	int max = -1;
	for (int i = 0; i < this->size; i++)
		if (listLengths[i] > max)
			max = listLengths[i];
	return max;
}

template <typename K, typename T>
int HashTable<K, T>::getCount() {
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (listLengths[i] > 0)
			count++;
	}

	return count;
}

template <typename K, typename T>
double HashTable<K, T>::getLoad() {
	return (double)this->getCount() / size;
}

template <typename K, typename T>
int HashTable<K, T>::getNumNodes() {
	int count = 0;
	for (int i = 0; i < size; i++) {
		count += listLengths[i];
	}

	return count;
}

template <typename K, typename T>
int HashTable<K, T>::getAverageNumNodes() {
	return this->getNumNodes() / this->getCount();
}

template<typename K, typename T>
void HashTable<K, T>::dbPrint(std::ostream &out) {
	for (int i = 0; i < size; i++) {
		LinkedList<const HashtableUnit<K, T> *> *l = table[i];
		for (int j = 0; j < l->getCount(); j++) {
			out << l->getData(j)->getData() << std::endl;
		}
	}
}
