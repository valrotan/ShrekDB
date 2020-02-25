#pragma once

#include <string>

class Character
{
protected:
	std::string name;
	std::string species;
	std::string gender;
	std::string color;
	double size;
	long age; // in days
	Character **posRelations; // make linked list
	Character **negRelations; // make linked list
public:
	Character();
};
