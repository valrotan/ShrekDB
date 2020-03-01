#ifndef BSTTEST_H
#define BSTTEST_H

#include <iostream>
#include "../src/dataStructs/BST.h"

using namespace std;

void runBSTTests() {
	cout << "running bst tests...\n";

	class ReverseComp : public Comparator<int> {
		int compare(const int &a, const int &b) override {
			return b - a;
		}
		ReverseComp *clone() const override {
			return new ReverseComp(*this);
		}
	};
	ReverseComp reversecmp;

	BST<int> bst(reversecmp);

	bst.add(1);
	bst.add(2);
	bst.add(0);
	bst.remove(1);
	bst.setOrder(BST_INORDER);
	cout << "BST\n";
	cout << bst << endl;
}

#endif // BSTTEST_H
