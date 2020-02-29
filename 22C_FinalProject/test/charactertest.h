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
}

#endif
