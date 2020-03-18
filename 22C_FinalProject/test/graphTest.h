#ifndef GRAPHTEST_H
#define GRAPHTEST_H

#include "../src/character/character.h"
#include "../src/dataStructs/Graph.h"
#include <fstream>
#include <iostream>

using namespace std;

void utilTest() {
	cout << "running util tests...\n";

	Character *c1 = new Character(1, "john doe", "dog", "male", "c teacher",
																"orange", 1.34, 34, 4);
	Character *c2 = new Character(1, "john doe", "dog", "male", "c teacher",
																"orange", 1.34, 34, 4);
	cout << "Character == " << (*c1 == *c2) << endl;
	Character *c3 = new Character(2, "john d", "dog", "male", "c teacher",
																"orange", 1.34, 34, 4);
	CharacterPointerComparator cpc(CHARACTER_ID);
	GraphNodePointerComparator<Character *> gnpc(cpc);

	GraphNode<Character *> *a = new GraphNode<Character *>(c1);
	GraphNode<Character *> *b = new GraphNode<Character *>(c2);
	GraphNode<Character *> *c = new GraphNode<Character *>(c3);
	cout << "Comparator == 0 : " << gnpc.compare(a, b) << endl;
	cout << "Comparator == 1 : " << gnpc.compare(a, c) << endl;
	cout << "Comparator == 1 : " << gnpc.strictlyEquals(a, b) << endl;
	cout << "Comparator == 0 : " << gnpc.strictlyEquals(b, c) << endl;

	Graph<Character *> g(cpc);
	g.addNode(c1);
	g.addNode(c3);
	cout << "contains " << g.findNode(c2) << endl;
	g.addEdge(c2, c3);
	cout << "edge count " << g.countEdges() << endl;
	g.removeNode(c2);
	cout << "edge count " << g.countEdges() << endl;

	delete a;
	delete b;
	delete c1;
	delete c2;
}

void graphTest() {
	cout << "running graph test...\n";

	CharacterPointerComparator cpc2(CHARACTER_ID);
	Graph<Character *> g(cpc2);

// read characters
#ifndef __APPLE__
	fstream dataFile(
			"C:\\Users\\taras\\source\\repos\\valrotan\\22C_FinalProject\\data.tsv");
#else
	fstream dataFile("characters.tsv");
#endif
	if (!dataFile) {
		cout << "File can't be opened..." << endl;
		return;
	}
	dataFile.ignore(1024, '\n'); // header first
	cout << Character::getTableHeader() << endl;
	while (!dataFile.eof()) {
		Character *c = new Character;
		dataFile >> *c;
		cout << c << endl;
		g.addNode(c);
	}
	dataFile.close();

	cout << g.countNodes() << endl;

	// read relationships
#ifndef __APPLE__
	fstream posFile(
			"C:\\Users\\taras\\source\\repos\\22C_FinalProject\\positive.tsv");
#else
	ifstream posFile("positive.tsv");
#endif
#ifndef __APPLE__
	fstream negFile(
			"C:\\Users\\taras\\source\\repos\\22C_FinalProject\\negative.tsv");
#else
	ifstream negFile("negative.tsv");
#endif
	if (!negFile || !posFile) {
		cout << "File can't be opened..." << endl;
		return;
	}

	int a, b;
	while (!posFile.eof()) {
		posFile >> a >> b;
		cout << a << " " << b << endl;
		try {
			g.addEdge(g.getNodeByIndex(a - 1), g.getNodeByIndex(b - 1), true);
		} catch (const char *e) {
			cout << e << " " << a << " " << b << endl;
		}
	}
	posFile.close();
	cout << "Negatives\n";
	while (!negFile.eof()) {
		negFile >> a >> b;
		cout << a << " " << b << endl;
		try {
			g.addEdge(g.getNodeByIndex(a - 1), g.getNodeByIndex(b - 1));
		} catch (const char *e) {
			cout << e << " " << a << " " << b << endl;
		}
	}
	negFile.close();
	cout << g.countEdges() << endl;
	cout << g.containsEdge(g.getNodeByIndex(0), g.getNodeByIndex(15)) << endl;

	Character::setPrintStyle(CHARACTER_STYLE_NAME);
	cout << g;

	for (int i = 0; i < g.countNodes(); i++) {
		delete g.getNodeByIndex(i);
	}

	//	cout << "\nokay\n";
}

void runGraphTests() {
	cout << "running graph tests...\n\n";
	utilTest();
	graphTest();
}

#endif // GRAPHTEST_H
