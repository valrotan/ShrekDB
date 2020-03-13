#include "mainscreen.h"

#include "../util/color.h"
#include "../util/ioutil.h"

MainScreen::MainScreen(std::istream &tin, std::ostream &tout)
		: Interactive(tin, tout) {

	try {
		table = new HashTable<std::string, Character *>(StringHasher());
		list = new LinkedList<Character *>(
				CharacterPointerComparator(CHARACTER_COLOR));
		bst =
				new BST<Character *>(CharacterPointerComparator(CHARACTER_OCCUPATION));
		graph = new Graph<Character *>(CharacterPointerComparator(CHARACTER_ID));

		db = new Database(charPath, posPath, negPath);

		loadData();
	} catch (const char *e) {
		out << e;
	}
}

MainScreen::~MainScreen() {
	delete table;
	delete bst;
	delete graph;

	while (list->getCount() > 0) {
		delete list->remove(0);
	}

	delete list;
}

void MainScreen::interact() {

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
					 "  [7] Print pretty graph \n"
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
			out << *table;
			break;
		case 5:
			break;
		case 6:
			Character::setPrintStyle(CHARACTER_STYLE_OCCUPATION);
			bst->setOrder(BST_PRETTY_PREORDER);
			out << *bst << std::endl;
			break;
		case 7:
			Character::setPrintStyle(CHARACTER_STYLE_NAME);
			out << *graph << std::endl;
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

void MainScreen::loadData() {
	db->openReadChars();
	Character *c = new Character;
	*db >> *c;
	while (c->getName() != "") {
		list->add(c);
		table->insert(c->getName(), c);
		bst->add(c);
		graph->addNode(c);

		c = new Character;
		*db >> *c;
	}
	db->closeReadChars();

	db->openReadPos();
	while (!db->doneReadingPos()) {
		int a, b;
		db->readPos(a, b);
		Character tempA(a), tempB(b);
		graph->addEdge(&tempA, &tempB, true);
	}
	db->closeReadPos();

	db->openReadNeg();
	while (!db->doneReadingNeg()) {
		int a, b;
		db->readNeg(a, b);
		Character tempA(a), tempB(b);
		graph->addEdge(&tempA, &tempB);
	}
	db->closeReadNeg();
}
void MainScreen::clearData() {}
void MainScreen::addData() {}
void MainScreen::removeData() {}
