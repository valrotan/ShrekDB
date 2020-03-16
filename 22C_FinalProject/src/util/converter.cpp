
#include "converter.h"


void Converter::interact() {
	out << "What do you wish to convert?" << std::endl;
	out << "length(" << Color(GREEN) << "1" << Color(RESET) << "), mass(" << Color(GREEN)
		<< 2 << Color(RESET) << "), bmi(" << Color(GREEN) << 3 << Color(RESET) << "), age(" << Color(GREEN) << 4 << Color(RESET) << ")\n> ";
	int selection = 0;
	in >> selection;
	if (selection >= 1 && selection <= 4) {
		out << "Enter the amount to convert:\n> ";
		double input = 0;
		in >> input;
		out << "Enter a name to convert to:\n> ";
		std::string name;
		in >> name;
		Character* c = this->table->find(name);
		CHARACTER_PROPERTY prop = CHARACTER_HEIGHT;
		switch (selection) {
		case 1:
			prop = CHARACTER_HEIGHT;
		case 2:
			prop = CHARACTER_MASS;
		case 3:
			prop = CHARACTER_BMI;
		case 4:
			prop = CHARACTER_AGE;
		}
		convert(prop, input, c);

	}
	else {
		out << Color(_ERROR) << "Invalid Selection, Try again..." << Color(RESET) << std::endl;
		return;
	}
}

double Converter::convert(CHARACTER_PROPERTY prop, double from, Character* to) {
	switch (prop) {
	case CHARACTER_HEIGHT:
		return from / to->getHeight();
	case CHARACTER_MASS:
		return from / to->getMass();
	case CHARACTER_BMI:
		return from / to->getBmi();
	case CHARACTER_AGE:
		return (int)from / to->getAge();
	default:
		throw "Conversion error: can't convert this type!\n";
	}
}