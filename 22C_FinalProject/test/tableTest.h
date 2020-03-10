#pragma once

#include "../src/dataStructs/HashTable.h"
#include "../src/character/character.h"
#include <iostream>
#include <string>

using namespace std;

void runTableTests() {
	cout << "running hash table tests...\n";
	StringHasher sh;
	HashTable<std::string, Character*> table(10,sh);
	
	Character* shrek = new Character(0, "Shrek", "ogre", "male", "scary", "green", 10.0, 80, 2, 38);
	Character* fiona = new Character(0, "Fiona", "ogre", "male", "mom", "green", 9.0, 60, 1, 35);
	Character* donkey = new Character(0, "Donkey", "donkey", "male", "donkey", "gray", 10.0, 5, 4, 18);
	table.insert("Shrek", shrek);
	table.insert("Fiona", fiona);
	table.insert("Donkey", donkey);

	Character* c = table.find("Fiona");
	cout << *c << endl;
	table.find("Shrek");
	table.find("Donkey");
	//table.insert("one", 50);
	//table.insert("two", 600000000);
	//table.insert("three", -10000);
}
