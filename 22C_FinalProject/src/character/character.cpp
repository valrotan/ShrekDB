#include "character.h"

#include <stdio.h>

CHARACTER_STYLE Character::printStyle = CHARACTER_STYLE_TABLE;

int Character::getId() const { return id; }

void Character::setId(int value) { id = value; }

Character::Character(int id,                 //
										 std::string name,       //
										 std::string species,    //
										 std::string gender,     //
										 std::string occupation, //
										 std::string color,      //
										 double height,          //
										 double mass,            //
										 double bmi,             //
										 int age)
		: id(id), name(name), species(species), gender(gender),
			occupation(occupation), color(color), height(height), mass(mass),
			bmi(bmi), age(age) {}

std::string Character::getTableHeader() {
	return "    ID |                     NAME |          SPECIES |      "
				 "     GENDER |       OCCUPATION |        COLOR |  AGE | "
				 "  MASS | HEIGHT |    BMI ";
}

bool operator==(const Character &a, const Character &b) {
	return a.id == b.id &&                 //
				 a.name == b.name &&             //
				 a.species == b.species &&       //
				 a.gender == b.gender &&         //
				 a.occupation == b.occupation && //
				 a.color == b.color &&           //
				 a.age == b.age &&               //
				 a.mass - b.mass < .0001 &&      //
				 a.height - b.height < .0001;
}

std::ostream &operator<<(std::ostream &out, const Character &c) {
	switch (Character::printStyle) {
	case CHARACTER_STYLE_DB:
		out << c.id << "\t"         //
				<< c.name << "\t"       //
				<< c.species << "\t"    //
				<< c.gender << "\t"     //
				<< c.occupation << "\t" //
				<< c.color << "\t"      //
				<< c.age << "\t"        //
				<< c.height << "\t"     //
				<< c.mass << "\t"       //
				<< c.bmi;               //

		break;
	case CHARACTER_STYLE_TABLE: {
		char buf[512];
		sprintf(buf,
						"  %04d | %24.24s | %16.16s | %16.16s | %16.16s | %12.12s | %4d | "
						"%6.1f | %6.1f | %6.1f ",
						c.id, c.name.c_str(), c.species.c_str(), c.gender.c_str(),
						c.occupation.c_str(), c.color.c_str(), c.age, c.mass, c.height,
						c.bmi);
		out << buf;
	} break;
	case CHARACTER_STYLE_SINGLE:
		char buf[512];
		sprintf(buf,
						"ID:           %04d \n"
						"NAME:         %s \n"
						"SPECIES:      %s \n"
						"GENDER:       %s \n"
						"OCCUPATION:   %s \n"
						"COLOR:        %s \n"
						"AGE           %d  \n"
						"MASS          %6.1f \n"
						"HEIGHT        %6.1f \n"
						"BMI:          %6.1f \n",
						c.id, c.name.c_str(), c.species.c_str(), c.gender.c_str(),
						c.occupation.c_str(), c.color.c_str(), c.age, c.mass, c.height,
						c.bmi);
		out << buf;
		break;
	case CHARACTER_STYLE_ID:
		out << c.id;
		break;
	case CHARACTER_STYLE_NAME:
		out << c.name;
		break;
	case CHARACTER_STYLE_SPECIES:
		out << c.species;
		break;
	case CHARACTER_STYLE_GENDER:
		out << c.gender;
		break;
	case CHARACTER_STYLE_OCCUPATION:
		out << c.occupation;
		break;
	case CHARACTER_STYLE_COLOR:
		out << c.color;
		break;
	case CHARACTER_STYLE_HEIGHT:
		out << c.height;
		break;
	case CHARACTER_STYLE_MASS:
		out << c.mass;
		break;
	case CHARACTER_STYLE_BMI:
		out << c.bmi;
		break;
	case CHARACTER_STYLE_AGE:
		out << c.age;
		break;
	}
	return out;
}

std::ostream &operator<<(std::ostream &out, const Character *c) {
	return out << *c;
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
	//	in.ignore(256, '\n');
	return in;
}

// Getters and setters
std::string Character::getName() const { return name; }

void Character::setName(const std::string &value) { name = value; }

std::string Character::getSpecies() const { return species; }

void Character::setSpecies(const std::string &value) { species = value; }

std::string Character::getGender() const { return gender; }

void Character::setGender(const std::string &value) { gender = value; }

std::string Character::getOccupation() const { return occupation; }

void Character::setOccupation(const std::string &value) { occupation = value; }

std::string Character::getColor() const { return color; }

void Character::setColor(const std::string &value) { color = value; }

double Character::getHeight() const { return height; }

void Character::setHeight(double value) { height = value; }

double Character::getMass() const { return mass; }

void Character::setMass(double value) { mass = value; }

double Character::getBmi() const { return bmi; }

void Character::setBmi(double value) { bmi = value; }

int Character::getAge() const { return age; }

void Character::setAge(int value) { age = value; }

void Character::setPrintStyle(const CHARACTER_STYLE &value) {
	printStyle = value;
}

int CharacterComparator::compare(const Character &a, const Character &b) {
	switch (charProp) {
	case CHARACTER_ID:
		return a.id - b.id;
	case CHARACTER_NAME:
		return a.name.compare(b.name);
	case CHARACTER_SPECIES:
		return a.species.compare(b.species);
	case CHARACTER_GENDER:
		return a.gender.compare(b.gender);
	case CHARACTER_OCCUPATION:
		return a.occupation.compare(b.occupation);
	case CHARACTER_COLOR:
		return a.color.compare(b.color);
	case CHARACTER_HEIGHT:
		if (a.height > b.height)
			return 1;
		if (a.height < b.height)
			return -1;
		else
			return 0;
	case CHARACTER_MASS:
		if (a.mass > b.mass)
			return 1;
		if (a.mass < b.mass)
			return -1;
		else
			return 0;
	case CHARACTER_BMI:
		if (a.bmi > b.bmi)
			return 1;
		if (a.bmi < b.bmi)
			return -1;
		else
			return 0;
	case CHARACTER_AGE:
		return a.age - b.age;
	case CHARACTER_ALL:
		if (a == b) {
			return 0;
		}
		return 1;
	}
}

int CharacterPointerComparator::compare(Character *const &a,
																				Character *const &b) {
	return comparator.compare(*a, *b);
}
