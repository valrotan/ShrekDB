#pragma once
#include <iostream>
#include "../src/dataStructs/HashTable.h"

using namespace std;

void runHashTests() {
	cout << "running hash tests...\n";
	StringHasher hasher;
	HashTable<string,Character*> hashTable(hasher);

	Character* c1 = new Character(1, "john doe", "dog", "male", "c teacher",
		"orange", 1.34, 34, 0, 4);
	Character* c2 = new Character(2, "john d", "dog", "male", "c teacher",
		"orange", 1.34, 34, 0, 4);


	hashTable.insert("one", c1);
	hashTable.insert("two", c2);
	hashTable.insert("three", c1);
	hashTable.insert("four", c2);


	//hashTable.insert("one", 10);
	//hashTable.insert("two", 7);
	//hashTable.insert("three", 11);
	//hashTable.insert("four", 13);
	//hashTable.insert("five", 17);
	//hashTable.insert("six", 6);
	//hashTable.insert("seven", 3);
	cout << hashTable;
}