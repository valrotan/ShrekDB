#ifndef BSTTEST_H
#define BSTTEST_H

#include <iostream>
#include "../src/dataStructs/BST.h"
#include "../src/character/character.h"

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
}

#endif // BSTTEST_H
