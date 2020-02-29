#ifndef CHARACTERTEST_H
#define CHARACTERTEST_H

#include "../src/character/character.h"
#include <fstream>
#include <iostream>

using namespace std;

void characterTests() {

	cout << "## character tests\n";

	fstream dataFile("data.tsv");
	dataFile.ignore(1024, '\n'); // header first
	Character c;
	cout << Character::getTableHeader() << endl;
	while (!dataFile.eof()) {
		dataFile >> c;
		cout << c << endl;
	}

	Character a, b;
	a.setName("a");
	a.setMass(12.4);
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
	if (pcmpByHeight.compare(&a, &b) != 0) {
		cout << "ERROR IN COMPARATOR BY HEIGHT\n";
	}

}

#endif
