#pragma once

#include "../character/character.h"
#include "../ui/interactive.h"
#include "../util/color.h"
#include "../dataStructs/HashTable.h"
#include <iostream>

class Converter: Interactive{
private:
	HashTable<std::string, Character*>* table;
public:
	Converter(std::istream& in, std::ostream& out, HashTable<std::string, Character*>* t) : Interactive(in, out), table(t) {}
	double convert(CHARACTER_PROPERTY,double, Character*);
	void interact();
};