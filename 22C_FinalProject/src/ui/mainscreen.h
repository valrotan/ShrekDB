#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "interactive.h"
#include "../character/character.h"
#include "../dataStructs/dataStructs.h"

class MainScreen : Interactive {
private:
	BST<Character *> *bst;
	Graph<Character *> *graph;
public:
	MainScreen();

	void interact(std::istream &in, std::ostream &out);
};

#endif // MAINSCREEN_H
