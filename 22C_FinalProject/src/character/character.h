#pragma once

#include "../util/comparator.h"
#include <iostream>
#include <string>

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
	CHARACTER_AGE,
	CHARACTER_ALL
};

// table for printing a table of characters
// entry for printing a single character
enum CHARACTER_STYLE {
	CHARACTER_STYLE_ID = 0,
	CHARACTER_STYLE_NAME,
	CHARACTER_STYLE_SPECIES,
	CHARACTER_STYLE_GENDER,
	CHARACTER_STYLE_OCCUPATION,
	CHARACTER_STYLE_COLOR,
	CHARACTER_STYLE_HEIGHT,
	CHARACTER_STYLE_MASS,
	CHARACTER_STYLE_BMI,
	CHARACTER_STYLE_AGE,
	CHARACTER_STYLE_TABLE,
	CHARACTER_STYLE_DB,
	CHARACTER_STYLE_SINGLE
};

class Character {
	friend class CharacterComparator;
	friend class CharacterPointerComparator;

protected:
	static CHARACTER_STYLE printStyle;

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

public:
	Character(int id = 0,                  //
						std::string name = "",       //
						std::string species = "",    //
						std::string gender = "",     //
						std::string occupation = "", //
						std::string color = "",      //
						double height = 0,           //
						double mass = 0,             //
						int age = 0);

	static std::string getTableHeader();
	static std::string getDBHeader() {
		return "id	name	species	sex	occupation	color	age	size	mass";
	}

	friend bool operator==(const Character &a, const Character &b);

	// Input stream operator
	// Populates a character from an istream
	friend std::istream &operator>>(std::istream &in, Character &c);

	// Output stream operator
	// outputs in a format specified by printStyle property
	friend std::ostream &operator<<(std::ostream &out, const Character &c);
	friend std::ostream &operator<<(std::ostream &out, const Character *c);

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
	void calcBmi();
	int getAge() const;
	void setAge(int value);
	static void setPrintStyle(const CHARACTER_STYLE &value);
	int getId() const;
	void setId(int value);
};

class CharacterComparator : public Comparator<Character> {
private:
	CHARACTER_PROPERTY charProp;

public:
	CharacterComparator() : charProp(CHARACTER_ID) {}
	CharacterComparator(CHARACTER_PROPERTY cp) : charProp(cp) {}
	int compare(const Character &a, const Character &b) override;
	CharacterComparator *clone() const override {
		return new CharacterComparator(*this);
	}
};

class CharacterPointerComparator : public Comparator<Character *> {
private:
	CharacterComparator comparator; // actual comparator used underneath

public:
	CharacterPointerComparator(CHARACTER_PROPERTY cp)
			: comparator(CharacterComparator(cp)) {}
	int compare(Character *const &a, Character *const &b) override;

	CharacterPointerComparator *clone() const override {

		CharacterPointerComparator *cpc = new CharacterPointerComparator(*this);
		return cpc;
	}

	bool strictlyEquals(Character *const &a, Character *const &b) override {
		return *a == *b;
	}
};
