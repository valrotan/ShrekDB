#include "mainscreen.h"

#include "../util/color.h"
#include "../util/ioutil.h"

MainScreen::MainScreen(std::istream &tin, std::ostream &tout)
		: Interactive(tin, tout) {

	try {
		table = new HashTable<std::string, Character *>(StringHasher());
		idTable = new HashTable<int, Character *>(IntegerHasher());
		list = new LinkedList<Character *>(
				ASCENDING, CharacterPointerComparator(CHARACTER_AGE));
		bst =
				new BST<Character *>(CharacterPointerComparator(CHARACTER_OCCUPATION));
		graph = new Graph<Character *>(CharacterPointerComparator(CHARACTER_ID));

		db = new Database(charPath, posPath, negPath);

		converter = new Converter(tin, tout, table);

		loadData();
	} catch (const char *e) {
		out << Color(_ERROR) << e << Color(RESET) << std::endl;
	}
}

MainScreen::~MainScreen() {
	writeData();

	delete table;
	delete idTable;
	delete bst;
	delete graph;

	while (list->getCount() > 0) {
		delete list->remove(0);
	}

	delete list;
}

void MainScreen::interact() {

	IOUtil::clearScreen();
	out << "Welcome to " << Color(GREEN) << "ShrekDB" << Color(RESET) << "! \n\n";

	int option;
	bool done = false;
	while (!done) {

		out << "Please select an option from the menu below: \n"
					 " x [1] Add new data \n"
					 " x [2] Delete data \n"
					 " x [3] Find characters by name \n"
					 " x [4] Display hash table by name \n"
					 " x [5] List characters by age \n"
					 " x [6] Display BST by occupation \n"
					 " x [7] Display relationship graph \n"
					 " x [8] Show algorithm efficiency \n"
					 " x [9] SHREK Converter \n"
					 " x [0] Quit \n"
					 "> ";

		in >> option;
		if (in.fail()) {
			option = -1;
			in.clear();
		}
		std::string temp;

		switch (option) {

		case 1: // add data
			IOUtil::clearScreen();
			out << Color(BLUE, BRIGHT_GRAY) << "Add" << Color(RESET) << std::endl
					<< std::endl;
			addData();

			in.ignore(1024, '\n');
			IOUtil::clearScreen();
			break;

		case 2: // delete data
			IOUtil::clearScreen();
			out << Color(BLUE, BRIGHT_GRAY) << "Delete" << Color(RESET) << std::endl
					<< std::endl;
			removeData();

			in.ignore(1024, '\n');
			IOUtil::clearScreen();
			break;

		case 3: // find data
			IOUtil::clearScreen();
			out << Color(BLUE, BRIGHT_GRAY) << "Find" << Color(RESET) << std::endl
					<< std::endl;
			findData();

			in.ignore(1024, '\n');
			IOUtil::clearScreen();
			break;

		case 4: // list hash table
			IOUtil::clearScreen();
			out << Color(BLUE, BRIGHT_GRAY) << "Hashtable" << Color(RESET)
					<< std::endl
					<< std::endl;
			Character::setPrintStyle(CHARACTER_STYLE_NAME);
			out << *table;

			in.ignore(1024, '\n');
			in.ignore(1024, '\n');
			IOUtil::clearScreen();
			break;

		case 5: // list in sorted key
			IOUtil::clearScreen();
			out << Color(BLUE, BRIGHT_GRAY) << "Sorted Key - Age" << Color(RESET)
					<< std::endl
					<< std::endl;

			Character::setPrintStyle(CHARACTER_STYLE_TABLE);
			out << Character::getTableHeader() << "\n";
			{
				int l = Character::getTableHeader().length();
				for (int i = 0; i < l; i++) {
					out << "-";
				}
			}
			out << "\n";
			out << *list;

			in.ignore(1024, '\n');
			in.ignore(1024, '\n');
			IOUtil::clearScreen();
			break;

		case 6: // print tree
			IOUtil::clearScreen();
			out << Color(BLUE, BRIGHT_GRAY) << "Tree - Occupation" << Color(RESET)
					<< std::endl
					<< std::endl;
			Character::setPrintStyle(CHARACTER_STYLE_OCCUPATION);
			bst->setOrder(BST_PRETTY_PREORDER);
			out << *bst << std::endl;

			in.ignore(1024, '\n');
			in.ignore(1024, '\n');
			IOUtil::clearScreen();
			break;

		case 7: // print graph
			IOUtil::clearScreen();
			out << Color(BLUE, BRIGHT_GRAY) << "Graph" << Color(RESET) << std::endl
					<< std::endl;
			Character::setPrintStyle(CHARACTER_STYLE_NAME);
			out << *graph;

			in.ignore(1024, '\n');
			in.ignore(1024, '\n');
			IOUtil::clearScreen();
			break;

		case 8: // print efficiency
			IOUtil::clearScreen();
			out << Color(BLUE, BRIGHT_GRAY) << "Efficiency" << Color(RESET)
					<< std::endl
					<< std::endl;
			out << Color(WHITE) << "Number of characters: " << Color(RESET)
					<< this->list->getCount() << std::endl
					<< std::endl;
			out << Color(WHITE) << "\tHashtable: " << Color(RESET) << std::endl;
			out << Color(BRIGHT_GRAY) << "\t\tLoad Factor: " << Color(GREEN)
					<< table->getLoad() << Color(RESET) << std::endl;
			out << Color(BRIGHT_GRAY) << "\t\tLongest Linked List: " << Color(GREEN)
					<< table->getMaxListSize() << Color(RESET) << std::endl;
			out << Color(BRIGHT_GRAY)
					<< "\t\tAverage number of nodes in linked lists: " << Color(GREEN)
					<< table->getAverageNumNodes() << Color(RESET) << std::endl;
			out << Color(WHITE) << "\tBST: " << Color(RESET) << std::endl;
			out << Color(BRIGHT_GRAY)
					<< "\t\tAverage number of operations in inserts: " << Color(GREEN)
					<< bst->getAverageInsertions() << Color(RESET) << std::endl;
			out << Color(BRIGHT_GRAY)
					<< "\t\tAverage number of operations in finds: " << Color(GREEN)
					<< bst->getAverageFinds() << Color(RESET) << std::endl
					<< std::endl;

			in.ignore(1024, '\n');
			in.ignore(1024, '\n');
			IOUtil::clearScreen();
			break;

		case 9: // list hash table
			IOUtil::clearScreen();
			out << Color(GREEN, BRIGHT_GRAY) << "SHREK" << Color(BLUE, BRIGHT_GRAY)
					<< " Converter" << Color(RESET) << std::endl
					<< std::endl;

			try {
				converter->interact();
			} catch (const char *e) {
				out << Color(_ERROR) << e << Color(RESET);
				in.ignore(1024, '\n');
				IOUtil::clearScreen();
				continue;
			}

			in.ignore(1024, '\n');
			IOUtil::clearScreen();
			break;

		case 0: // done
			IOUtil::clearScreen();
			done = true;
			out << "\n\nThanks for using " << Color(GREEN) << "ShrekDB"
					<< Color(RESET) << "! \n\n";
			in.ignore(1024, '\n');
			in.ignore(1024, '\n');
			break;

		default:
			in.ignore(1024, '\n');
			out << Color(_ERROR)
					<< "Invalid option. Please press any button and try again. \n"
					<< Color(RESET);
			in.ignore(1024, '\n');
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
		idTable->insert(c->getId(), c);
		bst->add(c);
		graph->addNode(c);

		c = new Character;
		*db >> *c;
	}
	delete c;
	db->closeReadChars();

	db->openReadPos();
	int a, b;
	while (db->readPos(a, b)) {
		Character *ca = idTable->find(a);
		Character *cb = idTable->find(b);
		graph->addEdge(ca, cb, true);
	}
	db->closeReadPos();

	db->openReadNeg();
	while (db->readNeg(a, b)) {
		Character *ca = idTable->find(a);
		Character *cb = idTable->find(b);
		graph->addEdge(ca, cb, false);
	}
	db->closeReadNeg();
}

void MainScreen::addData() {
	out << "Would you like to add a new [c]haracter or [p]ositive/[n]egative "
				 "relationship? \n> ";
	char c;
	in >> c;
	c = std::tolower(c);
	if (c == 'c') {
		out << "Please enter data in the following format, separated by tabs \n";
		out << Character::getDBHeader();
		out << "\n > ";
		Character *c = new Character;
		in >> *c;

		if (table->contains(c->getName())) {
			out << Color(_ERROR) << "Duplicate name not allowed." << Color(RESET)
					<< std::endl;
			in.ignore(1024, '\n');
			return;
		}
		if (idTable->contains(c->getId())) {
			out << Color(_ERROR) << "Duplicate id not allowed." << Color(RESET)
					<< std::endl;
			in.ignore(1024, '\n');
			return;
		}

		Character::setPrintStyle(CHARACTER_STYLE_SINGLE);
		out << c << std::endl;

		out << "Confirm? \n[Y/n]: ";
		char confirm;
		in >> confirm;
		if (std::tolower(confirm) == 'y') {

			list->add(c);
			table->insert(c->getName(), c);
			idTable->insert(c->getId(), c);
			bst->add(c);
			graph->addNode(c);
			out << Color(SUCCESS) << "Character added successfully. \n"
					<< Color(RESET);
		} else {
			out << "Operation cancelled\n";
		}
	} else if (c == 'p' || c == 'n') {
		out << "Please enter the two character names on two separate lines. \n> ";
		std::string namea;
		in.ignore(1024, '\n');
		getline(in, namea);
		out << "> ";
		std::string nameb;
		getline(in, nameb);

		if (!table->contains(namea) || !table->contains(nameb)) {
			out << "Characters not found.\n";
			return;
		}

		Character *charA = table->find(namea);
		Character *charB = table->find(nameb);

		Character::setPrintStyle(CHARACTER_STYLE_SINGLE);
		out << charA << std::endl << charB << std::endl;

		out << "Confirm? \n[Y/n]: ";
		char confirm;
		in >> confirm;
		if (std::tolower(confirm) == 'y') {
			try {
				graph->addEdge(charA, charB, c == 'p' ? true : false);
				out << Color(SUCCESS) << "Relationship added successfully. \n"
						<< Color(RESET);
			} catch (const char *e) {
				out << Color(_ERROR) << e << Color(RESET) << std::endl;
			}
		} else {
			out << "Operation cancelled. \n";
		}
	} else {
		out << Color(_ERROR) << "Invalid option.\n" << Color(RESET);
	}
	writeData();
	in.ignore(1024, '\n');
}

void MainScreen::writeRelationshipData() {
	db->clearPos();
	db->clearNeg();
	db->openWritePos();
	db->openWriteNeg();

	int c = graph->countEdges();
	for (int i = 0; i < c; i++) {
		Character *a, *b;
		graph->getEdgeByIndex(i, &a, &b);
		if (graph->isEdgePositive(i)) {
			db->writePos(a->getId(), b->getId());
		} else {
			db->writeNeg(a->getId(), b->getId());
		}
	}
	db->closeWritePos();
	db->closeWriteNeg();
}

void MainScreen::writeData() {
	Character::setPrintStyle(CHARACTER_STYLE_DB);
	db->clearChars();
	db->openWriteChars();
	table->dbPrint(db->getCharOStream());
	db->closeWriteChars();
	writeRelationshipData();
}

void MainScreen::removeData() {
	out << "Would you like to remove a [" << Color(GREEN) << "c" << Color(RESET)
			<< "]haracter or [" << Color(GREEN) << "r" << Color(RESET)
			<< "]elationship? \n> ";
	char c;
	in >> c;
	c = std::tolower(c);
	if (c == 'c') {
		out << "Please enter the name of the character to remove. \n> ";
		std::string name;
		in.ignore(1024, '\n');
		getline(in, name);

		if (!table->contains(name)) {
			out << Color(_ERROR) << "Character not found. \n" << Color(RESET);
			return;
		}
		Character *c = table->find(name);
		Character::setPrintStyle(CHARACTER_STYLE_SINGLE);
		out << c;
		out << "Confirm remove?\n [Y/n]: ";
		char confirm;
		in >> confirm;
		if (confirm == 'y' || confirm == 'Y') {
			table->remove(c->getName());
			idTable->remove(c->getId());
			bst->remove(c);
			graph->removeNode(c);
			delete list->remove(list->find(c));
			out << Color(SUCCESS) << "Character removed successfully. \n"
					<< Color(RESET);
		} else {
			out << "Operation cancelled. \n";
		}
	} else if (c == 'r') {
		out << "Please enter the two character names on two separate lines. \n> ";
		std::string namea;
		in.ignore(1024, '\n');
		getline(in, namea);
		out << "> ";
		std::string nameb;
		getline(in, nameb);

		if (!table->contains(namea) || !table->contains(nameb)) {
			out << Color(RESET) << "Characters not found.\n" << Color(RESET);
			return;
		}

		Character *charA = table->find(namea);
		Character *charB = table->find(nameb);

		Character::setPrintStyle(CHARACTER_STYLE_SINGLE);
		out << charA << std::endl << charB << std::endl;

		out << "Confirm remove relationship? \n[Y/n]: ";
		char confirm;
		in >> confirm;
		if (std::tolower(confirm) == 'y') {
			try {
				graph->removeEdge(charA, charB);
				out << Color(SUCCESS) << "Relationship removed successfully. \n"
						<< Color(RESET);
			} catch (const char *e) {
				out << Color(_ERROR) << e << Color(RESET) << std::endl;
			}
		} else {
			out << "Operation cancelled. \n";
		}
	} else {
		out << Color(_ERROR) << "Invalid option. \n" << Color(RESET);
	}
	writeData();
	in.ignore(1024, '\n');
}

void MainScreen::findData() {
	out << "Please enter the name of the character to find. \n> ";
	std::string name;
	in.ignore(1024, '\n');
	getline(in, name);
	if (!table->contains(name)) {
		out << Color(_ERROR) << "Character not found. \n" << Color(RESET);
		return;
	}
	Character::setPrintStyle(CHARACTER_STYLE_SINGLE);

	Character *c = table->find(name);
	out << "Search result: \n";
	out << c;
}
