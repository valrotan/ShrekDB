
#include "converter.h"

void Converter::interact() {
	out << "What do you wish to convert?" << std::endl;
	out << "length(" << Color(GREEN) << "1" << Color(RESET) << "), mass("
		<< Color(GREEN) << 2 << Color(RESET) << "), bmi(" << Color(GREEN) << 3
		<< Color(RESET) << "), age(" << Color(GREEN) << 4 << Color(RESET)
		<< ")\n> ";
	int selection = 0;
	in >> selection;
	if (in.fail()) {
		out << Color(_ERROR) << "Invalid selection. \n" << Color(RESET);
		in.clear();
		in.ignore(1024, '\n');
		return;
	}
	if (selection >= 1 && selection <= 4) {
		out << "Enter the amount to convert:\n> ";
		double input = 0;
		in >> input;
		if (in.fail()) {
			out << Color(_ERROR) << "Invalid amount. \n" << Color(RESET);
			in.clear();
			in.ignore(1024, '\n');
			return;
		}
		out << "Enter a name to convert to:\n> ";
		std::string name;
		in.ignore();
		in.clear();
		getline(in, name);
		Character* c;
		try {
			c = this->table->find(name);
		}
		catch (...) {
			out << Color(_ERROR) << "Character not found." << Color(RESET)
				<< std::endl;
			in.ignore(1024, '\n');
			in.clear();
			return;
		}
		CHARACTER_PROPERTY prop = CHARACTER_HEIGHT;
		switch (selection) {
		case 1:
			prop = CHARACTER_HEIGHT;
			break;
		case 2:
			prop = CHARACTER_MASS;
			break;
		case 3:
			prop = CHARACTER_BMI;
			break;
		case 4:
			prop = CHARACTER_AGE;
			break;
		default:
			out << Color(_ERROR) << "Invalid selection. \n" << Color(RESET);
			return;
		}
		double resp = convert(prop, input, c);
		out << std::endl
			<< Color(BLUE, BRIGHT_GRAY) << "Conversion results: " << Color(RESET)
			<< std::endl;
		switch (prop) {
		case CHARACTER_HEIGHT:
			out << "Result: " << resp << " " << Color(GREEN) << c->getName()
				<< "ometers" << Color(RESET) << std::endl;
			break;
		case CHARACTER_MASS:
			out << "Result: " << resp << " " << Color(GREEN) << c->getName()
				<< "ograms" << Color(RESET) << std::endl;
			break;
		case CHARACTER_BMI:
			out << "Result: " << resp << " " << Color(GREEN) << c->getName()
				<< "o bmi" << Color(RESET) << std::endl;
			break;
		case CHARACTER_AGE:
			out << "Result: " << resp << " " << Color(GREEN) << c->getName()
				<< "o years" << Color(RESET) << std::endl;
			break;
		}

	}
	else {
		out << Color(_ERROR) << "Invalid Selection." << Color(RESET) << std::endl;
		in.ignore(1024, '\n');
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
		return (double)from / to->getAge();
	default:
		throw "Conversion error: can't convert this type!\n";
	}
}
