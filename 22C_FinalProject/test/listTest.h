#pragma once
#include <iostream>
#include "../src/dataStructs/LinkedList.h"

using namespace std;

void runListTests() {
	cout << "running list tests...\n";

	class ReverseComp : public Comparator<int> {
		int compare(const int& a, const int& b) override {
			return b - a;
		}
		ReverseComp* clone() const override {
			return new ReverseComp(*this);
		}
	};
	ReverseComp reversecmp;

	LinkedList<int> list(DESCENDING);
	list.add(1);
	list.add(3);
	list.add(2);
	list.add(1);
	cout << "list\n";
	cout << list << endl;
}