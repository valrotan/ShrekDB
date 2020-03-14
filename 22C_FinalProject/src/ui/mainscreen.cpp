#include "mainscreen.h"

#include "../util/color.h"
#include "../util/ioutil.h"

MainScreen::MainScreen(std::istream &tin, std::ostream &tout)
		: Interactive(tin, tout) {

	try {
		table = new HashTable<std::string, Character *>(StringHasher());
		idTable = new HashTable<int, Character *>(IntegerHasher());
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
					 " x [1] Add new data \n"
					 " x [2] Delete data \n"
					 " x [3] Search and display data using the primary key \n"
					 " x [4] List data in hash table sequence \n"
					 "  [5] List data in sorted key sequence \n"
					 " x [6] Print indented tree \n"
					 " x [7] Print pretty graph \n"
					 " x [8] Efficiency \n"
					 "  [9] <Team choice menu option> \n"
					 " x [0] Quit \n"
					 "> ";

		in >> option;
		out << std::endl;
		std::string temp;


		IOUtil::clearScreen();
		switch (option) {
		case 1: // add data
			out << Color(BLUE, BRIGHT_GRAY) << "Add" << Color(RESET) << std::endl << std::endl;
			addData();

			in.ignore();
			getline(in, temp);
			IOUtil::clearScreen();

			break;
		case 2: // delete data
			out << Color(BLUE, BRIGHT_GRAY) << "Delete" << Color(RESET) << std::endl << std::endl;
			removeData();

			in.ignore();
			getline(in, temp);
			IOUtil::clearScreen();

			break;
		case 3: // find data
			out << Color(BLUE, BRIGHT_GRAY) << "Find" << Color(RESET) << std::endl << std::endl;
			findData();

			in.ignore();
			getline(in, temp);
			IOUtil::clearScreen();

			break;
		case 4: // list hash table
			out << Color(BLUE, BRIGHT_GRAY) << "Hashtable" << Color(RESET) << std::endl << std::endl;
			out << *table;

			in.ignore();
			getline(in, temp);
			IOUtil::clearScreen();

			break;
		case 5: // list in sorted key
			out << Color(BLUE, BRIGHT_GRAY) << "Sorted Key" << Color(RESET) << std::endl << std::endl;

			in.ignore();
			getline(in, temp);
			IOUtil::clearScreen();

			break;
		case 6: // print tree
			out << Color(BLUE, BRIGHT_GRAY) << "Tree" << Color(RESET) << std::endl << std::endl;
			Character::setPrintStyle(CHARACTER_STYLE_OCCUPATION);
			bst->setOrder(BST_PRETTY_PREORDER);
			out << *bst << std::endl;

			in.ignore();
			getline(in, temp);
			IOUtil::clearScreen();

			break;
		case 7: // print graph
			out << Color(BLUE, BRIGHT_GRAY) << "Graph" << Color(RESET) << std::endl << std::endl;
			Character::setPrintStyle(CHARACTER_STYLE_NAME);
			out << *graph << std::endl;

			in.ignore();
			getline(in, temp);
			IOUtil::clearScreen();

			break;
		case 8: // print efficiency
			out << Color(BLUE, BRIGHT_GRAY) << "Efficiency" << Color(RESET) << std::endl << std::endl;
			out << Color(WHITE) << "\tHashtable: " << Color(RESET) << std::endl;
			out << Color(BRIGHT_GRAY) << "\t\tLoad Factor: " << Color(RESET) << table->getLoad() << std::endl;
			out << Color(BRIGHT_GRAY) << "\t\tLongest Linked List: " << Color(RESET) << table->getMaxListSize() << std::endl;
			out << Color(BRIGHT_GRAY) << "\t\tAverage number of nodes in linked lists: " <<
										Color(RESET) << table->getAverageNumNodes() << std::endl;
			out << Color(WHITE) << "\tBST: " << Color(RESET) << std::endl;
			out << Color(BRIGHT_GRAY) << "\t\tAverage number of operations in inserts: " << Color(RESET)
																		<< bst->getAverageInsertions()  << std::endl;
			out << Color(BRIGHT_GRAY) << "\t\tAverage number of operations in finds: " << Color(RESET)
																		<< bst->getAverageFinds() << std::endl << std::endl;
			in.ignore();
			getline(in, temp);
			IOUtil::clearScreen();
			break;
		case 0: // done
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
		idTable->insert(c->getId(), c);
		bst->add(c);
		graph->addNode(c);

		c = new Character;
		*db >> *c;
	}
	delete c;
	db->closeReadChars();

	db->openReadPos();
	while (!db->doneReadingPos()) {
		int a, b;
		db->readPos(a, b);
		Character *ca = idTable->find(a);
		Character *cb = idTable->find(b);
		graph->addEdge(ca, cb, true);
	}
	db->closeReadPos();

	db->openReadNeg();
	while (!db->doneReadingNeg()) {
		int a, b;
		db->readNeg(a, b);
		Character *ca = idTable->find(a);
		Character *cb = idTable->find(b);
		graph->addEdge(ca, cb);
	}
	db->closeReadNeg();
}
void MainScreen::addData() {
	out << "Please enter data in the following format, separateed by tabs \n";
	out << Character::getDBHeader();
	out << "\n > ";
	Character *c = new Character;
	in >> *c;

	list->add(c);
	table->insert(c->getName(), c);
	bst->add(c);
	graph->addNode(c);
}

void MainScreen::removeData() {
	out << "Please enter the name of the character to remove. \n> ";
	std::string name;
	in.ignore(1024, '\n');
	getline(in, name);
	if (!table->contains(name)) {
		out << Color(_ERROR)
				<< "Character not found. Please press any button and try again. \n"
				<< Color(RESET);
		std::string buf;
		getline(in, buf);
		IOUtil::clearScreen();
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
		bst->remove(c);
		graph->removeNode(c);
		delete list->remove(list->find(c));
		out << "remove successful\n";
	} else {
		out << "cancelled remove \n";
	}
}

void MainScreen::findData() {
	out << "Please enter the name of the character to find. \n> ";
	std::string name;
	in.ignore(1024, '\n');
	getline(in, name);
	if (!table->contains(name)) {
		out << Color(_ERROR)
				<< "Character not found. Please press any button and try again. \n"
				<< Color(RESET);
		std::string buf;
		getline(in, buf);
		IOUtil::clearScreen();
		return;
	}
	Character::setPrintStyle(CHARACTER_STYLE_SINGLE);

	Character *c = table->find(name);
	out << "Table result: \n";
	out << c;

	c = bst->search(c);
	out << "BST result: \n";
	out << c;

	c = list->getData(list->find(c));
	out << "List result: \n";
	out << c;

	try {
		c = graph->getNode(c);
		out << "Graph result: \n";
		out << c;
	} catch (const char *e) {
		out << e << std::endl;
	}
}
