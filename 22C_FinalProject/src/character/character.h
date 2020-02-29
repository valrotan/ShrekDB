#pragma once

#include <iostream>
#include <string>

enum CHARACTER_STYLE { CHARACTER_STYLE_TABLE = 0, CHARACTER_STYLE_ENTRY };

class Character {
protected:
	int id;
	std::string name;
	std::string species;
	std::string gender;
	std::string occupation;
	std::string color;
	double height;
	double mass;
	double bmi;
	int age;
	Character **posRelations; // make linked list
	Character **negRelations; // make linked list
	CHARACTER_STYLE printStyle;

public:
	Character();

	static std::string getTableHeader();

	friend std::istream &operator>>(std::istream &in, Character &c);
	friend std::ostream &operator<<(std::ostream &out, const Character &c);
};
