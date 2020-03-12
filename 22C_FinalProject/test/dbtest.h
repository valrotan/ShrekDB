#ifndef DBTEST_H
#define DBTEST_H

#include "../src/character/database.h"
#include "../src/dataStructs/HashTable.h"
#include <iostream>

using namespace std;

void dbtests() {
	cout << "db tests \n";
	Database db("characters2.tsv", "positive2.tsv", "negative2.tsv");

	Character *c;
	Character::setPrintStyle(CHARACTER_STYLE_TABLE);

	HashTable<std::string, Character *> table{StringHasher()};
	LinkedList<Character *> list{CharacterPointerComparator(CHARACTER_NAME)};

	db.openReadChars();
	c = new Character;
	db >> *c;
	while (c->getName() != "") {
		list.add(c);
		table.insert(c->getName(), c);
		c = new Character;
		db >> *c;
	}
	db.closeReadChars();

	cout << "Pos \n";

	db.openReadPos();
	while (!db.doneReadingPos()) {
		int a, b;
		db.readPos(a, b);
		cout << a << " " << b << endl;
	}
	db.closeReadPos();

	cout << "Neg \n";

	db.openReadNeg();
	while (!db.doneReadingNeg()) {
		int a, b;
		db.readNeg(a, b);
		cout << a << " " << b << endl;
	}
	db.closeReadNeg();

	cout << "Writing \n";

	db.clearChars();
	db.openWriteChars();
	for (int i = 0; i < list.getCount(); i++) {
		Character *temp = table.find(list.getData(i)->getName());
		cout << temp << endl;
		db << *temp;
	}
	db.closeReadChars();
}

#endif // DBTEST_H
