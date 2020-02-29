#ifndef CHARACTERTEST_H
#define CHARACTERTEST_H

#include <iostream>
#include <fstream>
#include "../src/character/character.h"

using namespace std;

void characterTests() {

	cout << "character tests\n";

	fstream dataFile("data.tsv");
	dataFile.ignore(1024, '\n');
	Character c;
	dataFile >> c;
	cout << c << endl;
	dataFile >> c;
	cout << c << endl;
}

#endif
