
#include "../src/util/converter.h"
#include "../src/dataStructs/HashTable.h"
#include <iostream>
#include <string>

using namespace std;

void testConverter() {
	HashTable<string, Character*> table;
	Character* shrek = new Character(1, "Shrek", "", "", "", "", 50, 50, 40, 1);
	table.insert("Shrek", shrek);
	Converter conv(cin, cout, &table);
}