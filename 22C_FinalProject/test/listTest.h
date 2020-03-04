#pragma once
#include "../src/dataStructs/LinkedList.h"
#include <iostream>

using namespace std;

void runListTests() {
	cout << "running list tests...\n";

	class ReverseComp : public Comparator<int> {
		int compare(const int &a, const int &b) override { return b - a; }
		ReverseComp *clone() const override { return new ReverseComp(*this); }
	};
	ReverseComp reversecmp;

	LinkedList<int> list(DESCENDING);
	list.add(1);
	list.emptyList();
	list.add(1);
	list.add(3);
	list.add(2);
	list.add(1);
	for (int i = 0; i < list.getCount(); i++) {
		cout << list.getData(i) << endl;
	}
	cout << "list\n";
	cout << list << endl;
}
