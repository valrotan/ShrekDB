#pragma once

#include <string>
#include "../util/comparator.h"
#include "LinkedList.h"
#include "../util/hasher.h"
#include "hashtableUnit.h"


template <typename K, typename T>
class HashTable {
private:
	int size;
	int load;
	int maxList;
	int numNodes;
	int avgNumNodes;
	LinkedList<const HashtableUnit<K, T>*>** table;
	Hasher<K> *hasher;
	Comparator<K>* comparator;

public:
	HashTable(const Hasher<K>&);
	HashTable(int, const Hasher<K>&);
	HashTable(int, const Comparator<T>&, const Hasher<K>&);
	~HashTable();

	// getters/setters
	int getCount() { return load; }
	int getSize() { return size; }
	double getLoad() { return (double)load / size; }
	int getMaxListSize() { return maxList; }
	int getNumNodes() { return numNodes; }
	int getAverageNumNodes(){ return avgNumNodes; }


	bool insert(K, T);
	bool contains(K);
	T remove(K);
	T find(K);

	void clear();

	T operator [](int index);
	
	template<typename U, typename V>
	friend std::ostream& operator << (std::ostream&, HashTable<U, V>&);
};

template <typename K, typename T>
HashTable<K, T>::HashTable(const Hasher<K>& h): load(0), maxList(0), avgNumNodes(0) {
	size = 10;
	comparator = new GenericComparator<K>;
	table = new LinkedList<const HashtableUnit<K,T>*>*[size];
	for (int i = 0; i < size; i++) {
		table[i] = new LinkedList<const HashtableUnit<K, T>*>(ASCENDING, UnitPointerComparator<K, T>{});
	}
	hasher = h.clone();
}

template <typename K, typename T>
HashTable<K, T>::HashTable(int s, const Hasher<K>& h) : load(0), maxList(0), avgNumNodes(0) {
	size = s;
	table = new LinkedList<const HashtableUnit<K, T>*>*[size];
	comparator = new GenericComparator<K>;
	for (int i = 0; i < size; i++) {
		table[i] = new LinkedList<const HashtableUnit<K, T>*>(ASCENDING, UnitPointerComparator<K, T>{});
	}
	hasher = h.clone();
}

template <typename K, typename T>
HashTable<K, T>::HashTable(int s, const Comparator<T>& comp, const Hasher<K>& h) : load(0), maxList(0), avgNumNodes(0) {
	size = s;
	table = new LinkedList<const HashtableUnit<K, T>*>*[size];
	comparator = comp.clone();

	for (int i = 0; i < size; i++) {
		table[i] = new LinkedList<const HashtableUnit<K, T>*>(ASCENDING, UnitPointerComparator<K, T>{});
	}
	hasher = h.clone();
}

template <typename K, typename T>
HashTable<K, T>::~HashTable() {

}

template <typename K, typename T>
bool HashTable<K, T>::insert(K k, T data) {
	long key = hasher->hash(k,this->size);
	LinkedList<const HashtableUnit<K, T>*>* l = table[key];
	if (l->getCount() <= 0)
		load++;
	else {
		if (maxList < l->getCount())
			maxList = l->getCount();
	}
	numNodes++;
	l->add(new HashtableUnit<K,T>(k,data));
	return true;
}


template <typename K, typename T>
T HashTable<K, T>::remove(K k) {
	long key = hasher->hash(k, this->size);
	LinkedList<const HashtableUnit<K, T>*>* l = table[key];

	for (int i = 0; i < l->getCount(); i++) {
		if (comparator->compare(l->getData(i)->getKey(), k) == 0) {
			if (l->getCount() <= 0)
				load--;
			else {
				if (maxList < l->getCount())
					maxList = l->getCount();
			}
			numNodes--;
			return l->remove(i)->getData();
		}
	};
	return false;
}

template <typename K, typename T>
T HashTable<K, T>::find(K k) {
	long key = hasher->hash(k, this->size);
	LinkedList<const HashtableUnit<K, T>*>* l = table[key];
	for (int i = 0; i < l->getCount(); i++) {
		if (comparator->compare(l->getData(i)->getKey(),k) == 0) {
			return l->getData(i)->getData();
		}
	};
	throw "Expection: element not found";
}

template <typename K, typename T>
bool HashTable<K, T>::contains(K k) {
	long key = hasher->hash(k, this->size);
	LinkedList<const HashtableUnit<K, T>*>* l = table[key];
	for (int i = 0; i < l->getCount(); i++) {
		if (comparator->compare(l->getData(i)->getKey(), k) == 0) {
			return true;
		}
	};
	return false;
}

template <typename K, typename T>
T HashTable<K, T>::operator [](int index) {
	LinkedList<const HashtableUnit<K, T>*>* l = table[key];
	for (int i = 0; i < l->getCount(); i++) {
		if (comparator->compare(l->getData(i)->getKey(), k) == 0) {
			return l->getData(i)->getData();
		}
	};
}

template<typename K, typename T>
std::ostream& operator << (std::ostream& out, HashTable<K, T>& hashtable) {
	for (int i = 0; i < hashtable.size; i++) {
		LinkedList<const HashtableUnit<K, T>*>* l = hashtable.table[i];
		out << "Bucket " << i << ": " << std::endl;
		for (int j = 0; j < l->getCount(); j++) {
			out << "\t" << l->getData(j)->getData() << std::endl;
		}
	}
	
	return out;
}