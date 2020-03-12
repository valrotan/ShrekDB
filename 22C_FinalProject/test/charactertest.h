#ifndef CHARACTERTEST_H
#define CHARACTERTEST_H

#include "../src/character/character.h"
#include "../src/dataStructs/BST.h"
#include <fstream>
#include <iostream>

using namespace std;

void characterTests() {

	cout << "## character tests\n";

	CharacterPointerComparator ccmp(CHARACTER_OCCUPATION);
	BST<Character *> bst(ccmp);
	//	Character::setPrintStyle(CHARACTER_STYLE_NAME);

#ifndef __APPLE__
	fstream dataFile(
			"C:\\Users\\taras\\Source\\Repos\\valrotan\\22C_FinalProject\\data.tsv");
#else
	fstream dataFile("data.tsv");
#endif
	if (!dataFile) {
		cout << "File can't be opened..." << endl;
		return;
	}
	dataFile.ignore(1024, '\n'); // header first
	Character c;
	cout << Character::getTableHeader() << endl;
	while (!dataFile.eof()) {
		dataFile >> c;
		bst.add(new Character(c));
	}

	Character a, b;
	a.setName("a");
	a.setMass(11.4);
	a.setHeight(11);
	b.setName("b");
	b.setMass(11.2);
	b.setHeight(11);
	CharacterComparator cmpByName(CHARACTER_NAME);
	CharacterComparator cmpByMass(CHARACTER_MASS);
	CharacterComparator cmpByHeight(CHARACTER_HEIGHT);

	if (cmpByName.compare(a, b) >= 0) {
		cout << "ERROR IN COMPARATOR BY NAME\n";
	}
	if (cmpByMass.compare(a, b) <= 0) {
		cout << "ERROR IN COMPARATOR BY MASS\n";
	}
	if (cmpByHeight.compare(a, b) != 0) {
		cout << "ERROR IN COMPARATOR BY HEIGHT\n";
	}

	CharacterPointerComparator pcmpByName(CHARACTER_NAME);
	CharacterPointerComparator pcmpByMass(CHARACTER_MASS);
	CharacterPointerComparator pcmpByHeight(CHARACTER_HEIGHT);
	if (pcmpByName.compare(&a, &b) >= 0) {
		cout << "ERROR IN COMPARATOR BY NAME\n";
	}
	if (pcmpByMass.compare(&a, &b) <= 0) {
		cout << "ERROR IN COMPARATOR BY MASS\n";
	}
	if (pcmpByMass.compare(&b, &a) >= 0) {
		cout << "ERROR IN COMPARATOR BY MASS\n";
	}
	if (pcmpByHeight.compare(&a, &b) != 0) {
		cout << "ERROR IN COMPARATOR BY HEIGHT\n";
	}

	bst.setOrder(BST_PRETTY_PREORDER);
	Character::setPrintStyle(CHARACTER_STYLE_OCCUPATION);
	cout << bst;
}

#endif
