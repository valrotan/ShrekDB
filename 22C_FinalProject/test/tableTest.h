#pragma once

#include "../src/character/character.h"
#include "../src/dataStructs/HashTable.h"
#include <iostream>
#include <string>

using namespace std;

void runTableTests() {
	cout << "running hash table tests...\n";
	StringHasher sh;
	HashTable<std::string, Character *> table(10, sh);

	Character *shrek =
			new Character(0, "Shrek", "ogre", "male", "scary", "green", 10.0, 80, 38);
	Character *fiona =
			new Character(0, "Fiona", "ogre", "male", "mom", "green", 9.0, 60, 35);
	Character *donkey = new Character(0, "Donkey", "donkey", "male", "donkey",
																		"gray", 10.0, 5, 18);
	table.insert("Shrek", shrek);
	table.insert("Fiona", fiona);
	table.insert("Donkey", donkey);
	try {
		table.insert("Shrek", shrek);
	} catch (const char *e) {
		cout << e << endl;
	}

	cout << "Size: " << table.getSize() << endl;
	cout << "Count filled: " << table.getCount() << endl;
	cout << "Load: " << table.getLoad() << endl;
	cout << "Max list size: " << table.getMaxListSize() << endl;
	cout << "Number of List Nodes: " << table.getNumNodes() << endl;
	cout << "Average Number of Nodes: " << table.getAverageNumNodes() << endl
			 << endl;

	Character *c = table.find("Fiona");
	// cout << *c << endl;

	cout << table;

	table.remove("Fiona");

	try {
		c = table.find("Fiona");

		if (!c)
			cout << "Deleted" << endl;
	} catch (...) {
	}

	cout << endl << table;

	table.clear();

	cout << endl << table;

	/*table.find("Shrek");
	table.find("Donkey");*/
	// table.insert("one", 50);
	// table.insert("two", 600000000);
	// table.insert("three", -10000);
}
