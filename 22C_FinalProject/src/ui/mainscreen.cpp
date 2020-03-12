#include "mainscreen.h"

#include "../util/color.h"
#include "../util/ioutil.h"

MainScreen::MainScreen() {}

void MainScreen::interact(std::istream &in, std::ostream &out) {

	out << "Welcome to " << Color(GREEN) << "ShrekDB" << Color(RESET) << "! \n\n";

	int option;
	bool done = false;
	while (!done) {

		out << "Please select an option from the menu below: \n"
					 "  [1] Add new data \n"
					 "  [2] Delete data \n"
					 "  [3] Search and display data using the primary key \n"
					 "  [4] List data in hash table sequence \n"
					 "  [5] List data in sorted key sequence \n"
					 "  [6] Print indented tree \n"
					 "  [7] Efficiency \n"
					 "  [8] <Team choice menu option> \n"
					 "  [9] Quit \n"
					 "> ";

		in >> option;

		switch (option) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			done = true;
			out << "Thanks for using " << Color(GREEN) << "ShrekDB" << Color(RESET)
					<< "! \n";

			break;
		default:
			out << Color(_ERROR)
					<< "Invalid option. Please press any button and try again. \n"
					<< Color(RESET);
			std::string buf;
			in.ignore();
			getline(in, buf);
			IOUtil::clearScreen();
			break;
		}
	}
}
