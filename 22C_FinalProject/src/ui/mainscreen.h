#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "../character/character.h"
#include "../character/database.h"
#include "../dataStructs/dataStructs.h"
#include "interactive.h"

class MainScreen : Interactive {
private:
	HashTable<std::string, Character *> *table;
	LinkedList<Character *> *list;
	BST<Character *> *bst;
	Graph<Character *> *graph;

	Database *db;

	const std::string charPath = "characters.tsv";
	const std::string posPath = "positive.tsv";
	const std::string negPath = "negative.tsv";

	void loadData();
	void clearData();
	void writeData();
	void addData();
	void removeData();

public:
	MainScreen(std::istream &tin, std::ostream &tout);
	~MainScreen();

	void interact() override;
};

#endif // MAINSCREEN_H
