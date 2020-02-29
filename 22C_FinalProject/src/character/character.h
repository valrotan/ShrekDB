#pragma once

#include "../util/comparator.h"
#include <iostream>
#include <string>

// table for printing a table of characters
// entry for printing a single character
enum CHARACTER_STYLE { CHARACTER_STYLE_TABLE = 0, CHARACTER_STYLE_ENTRY };

class Character {
	friend class CharacterComparator;
	friend class CharacterPointerComparator;

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

	friend bool operator==(Character &a, Character &b);

	// Input stream operator
	// Populates a character from an istream
	friend std::istream &operator>>(std::istream &in, Character &c);

	// Output stream operator
	// outputs in a format specified by printStyle property
	friend std::ostream &operator<<(std::ostream &out, const Character &c);

	// Getters and setters
	std::string getName() const;
	void setName(const std::string &value);
	std::string getSpecies() const;
	void setSpecies(const std::string &value);
	std::string getGender() const;
	void setGender(const std::string &value);
	std::string getOccupation() const;
	void setOccupation(const std::string &value);
	std::string getColor() const;
	void setColor(const std::string &value);
	double getHeight() const;
	void setHeight(double value);
	double getMass() const;
	void setMass(double value);
	double getBmi() const;
	void setBmi(double value);
	int getAge() const;
	void setAge(int value);
	void setPrintStyle(const CHARACTER_STYLE &value);
};

enum CHARACTER_PROPERTY {
	CHARACTER_ID = 0,
	CHARACTER_NAME,
	CHARACTER_SPECIES,
	CHARACTER_GENDER,
	CHARACTER_OCCUPATION,
	CHARACTER_COLOR,
	CHARACTER_HEIGHT,
	CHARACTER_MASS,
	CHARACTER_BMI,
	CHARACTER_AGE
};

class CharacterComparator : Comparator<Character> {
private:
	CHARACTER_PROPERTY charProp;

public:
	CharacterComparator() : charProp(CHARACTER_ID) {}
	CharacterComparator(CHARACTER_PROPERTY cp) : charProp(cp) {}
	int compare(const Character &a, const Character &b) override;
};

class CharacterPointerComparator : Comparator<Character *> {
private:
	CHARACTER_PROPERTY charProp;
	CharacterComparator *comparator; // actual comparator used underneath

public:
	CharacterPointerComparator(CHARACTER_PROPERTY cp) : charProp(cp) {
		comparator = new CharacterComparator(charProp);
	}
	int compare(Character *const &a, Character *const &b) override;
};
