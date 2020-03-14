#pragma once

#include "../util/comparator.h"

template <typename K, typename T>
class HashtableUnit {
private:
	K key;
	T data;
public:
	HashtableUnit(K, T);
	K getKey() const;
	T getData() const;
	void setKey(K);
	void setData(T);

	friend bool operator == (const HashtableUnit<K,T> &a, const HashtableUnit<K,T> &b) {
		return a.key == b.key;
	}
};


template<typename K, typename T>
class UnitComparator : public Comparator<HashtableUnit<K, T>> { // anonymous generic comparator

//private:
	Comparator<K>* dataComparator;

public:
	UnitComparator()  { //: dataComparator(new GenericComparator<K>)
		dataComparator = new GenericComparator<K>;
	}
	UnitComparator(const Comparator<K>& dataComp) {
		dataComparator = dataComp.clone();
	}
	UnitComparator(const UnitComparator<K,T>& dataComp) {
		dataComparator = dataComp.dataComparator->clone();
	}
	~UnitComparator() { delete dataComparator; }

	int compare(const HashtableUnit<K,T>& a, const HashtableUnit<K, T>& b) override {
		return dataComparator->compare(a.getKey(), b.getKey());
	}
	UnitComparator* clone() const override {
		return new UnitComparator(*this);
	}
};


template<typename K, typename T>
class UnitPointerComparator : public Comparator<const HashtableUnit<K, T>*> { // anonymous generic comparator
private:
	UnitComparator<K, T> unitComparator;
public:
	UnitPointerComparator() : unitComparator(UnitComparator<K,T>()) {}
	UnitPointerComparator(const Comparator<T>& dataComp)
		: unitComparator(new UnitComparator<K, T>(dataComp)) {}

	~UnitPointerComparator() {}

	int compare(const HashtableUnit<K,T>* const & a, const HashtableUnit<K,T>* const & b) override {
		return unitComparator.compare(*a,*b);
	}

	bool strictlyEquals(const HashtableUnit<K, T>* const& a, const HashtableUnit<K, T>* const& b) override {
		return a->getKey() == b->getKey();
	}

	UnitPointerComparator* clone() const override {
		return new UnitPointerComparator(*this);
	}
};



template<typename K, typename T>
HashtableUnit<K, T>::HashtableUnit(K k, T d) : key(k), data(d) {}

template<typename K, typename T>
K HashtableUnit<K, T>::getKey() const { return key; }

template<typename K, typename T>
T HashtableUnit<K, T>::getData() const { return data; }

template<typename K, typename T>
void HashtableUnit<K, T>::setKey(K k) { key = k; }

template<typename K, typename T>
void HashtableUnit<K, T>::setData(T d) { data = d; }
