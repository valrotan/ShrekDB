#include "character.h"

Character::Character() {}

std::ostream &operator<<(std::ostream &out, const Character &c) {
	out << c.name;
	return out;
}

std::istream &operator>>(std::istream &in, Character &c) {
	in >> c.id;
	in.ignore(256, '\t');
	std::getline(in, c.name, '\t');
	std::getline(in, c.species, '\t');
	std::getline(in, c.gender, '\t');
	std::getline(in, c.occupation, '\t');
	std::getline(in, c.color, '\t');
	in >> c.age >> c.height >> c.mass >> c.bmi;
	// TODO scan relationships
	in.ignore(256, '\n');
	return in;
}
