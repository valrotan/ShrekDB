#ifndef BSTTEST_H
#define BSTTEST_H

#include "../src/character/character.h"
#include "../src/dataStructs/BST.h"
#include <iostream>

using namespace std;

void runBSTTests() {
	cout << "running bst tests...\n";

	CharacterPointerComparator ccmp(CHARACTER_MASS);

	Character a, b;
	a.setName("a");
	a.setMass(11.4);
	a.setHeight(11);

	b.setName("b");
	b.setMass(11.2);
	b.setHeight(11);
	cout << &a << endl << &b << endl;

	BST<Character *> bst(ccmp);

	bst.add(&a);
	bst.add(&b);
	bst.setOrder(BST_INORDER);
	cout << "BST\n";

	Character::setPrintStyle(CHARACTER_STYLE_NAME);
	cout << bst << endl;

	BST<int> bs;

	// add/remove data into the tree
	bs.add(2);
	bs.add(1);
	bs.add(3);
	int count = 0;
	bs.add(4, count);
	cout << "nOps to add 4: " << count << endl;
	bs.add(5, count);
	cout << "nOps to add 5: " << count << endl;

	cout << "tree contains 4: " << bs.contains(4) << endl;

	bs.search(4);
	bs.search(4, count);
	cout << "nOps to search for 4: " << count << endl;

	cout << "max/min: " << bs.findLargestData() << " / " << bs.findSmallestData()
			 << endl;

	// removes value from the tree and returns it
	bs.remove(3);

	cout << "tree nElems: " << bs.count() << endl;
	cout << "tree empty: " << bs.isEmpty() << endl;
	bs.empty();
	cout << "tree empty: " << bs.isEmpty() << endl;
	cout << "tree nElems: " << bs.count() << endl;

	cout << "tree contains 4: " << bs.contains(4) << endl;
}

#endif // BSTTEST_H
