#ifndef DBTEST_H
#define DBTEST_H

#include "../src/character/database.h"
#include <iostream>

using namespace std;

void dbtests() {
	cout << "db tests \n";
	Database db("data2.tsv", "positive2.tsv", "negative2.tsv");

	Character c;
	Character::setPrintStyle(CHARACTER_STYLE_TABLE);

	db.openReadChars();
	while (!db.doneReadingChars()) {
		db >> c;
		cout << c << endl;
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
}

#endif // DBTEST_H
