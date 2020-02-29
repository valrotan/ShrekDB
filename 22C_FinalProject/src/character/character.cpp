#include "character.h"

#include <stdio.h>

Character::Character() : printStyle(CHARACTER_STYLE_TABLE) {}

std::string Character::getTableHeader() {
	return "    ID |                             NAME |          SPECIES |      "
				 "     GENDER |       OCCUPATION |        COLOR |  AGE | "
				 "  MASS |    BMI ";
}

std::ostream &operator<<(std::ostream &out, const Character &c) {
	switch (c.printStyle) {
	case CHARACTER_STYLE_ENTRY:
		break;
	case CHARACTER_STYLE_TABLE: {
		char buf[512];
		sprintf(buf,
						"  %04d | %32.32s | %16.16s | %16.16s | %16.16s | %12.12s | %4d | "
						"%6.1f | %6.1f ",
						c.id, c.name.c_str(), c.species.c_str(), c.gender.c_str(),
						c.occupation.c_str(), c.color.c_str(), c.age, c.mass, c.bmi);
		out << buf;
	}
	}
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
