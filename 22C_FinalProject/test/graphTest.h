#ifndef GRAPHTEST_H
#define GRAPHTEST_H

#include "../src/character/character.h"
#include "../src/dataStructs/Graph.h"
#include <iostream>

using namespace std;

void runGraphTests() {
	cout << "running graph tests...\n";

	try {
		Graph<int> g;
		g.addNode(1);
		g.addNode(2);
		g.addNode(3);
		g.addNode(4);
		g.removeNode(4);
		g.addNode(4);
		g.addNode(5);
		g.addNode(6);
		cout << g.findNode(3) << endl;

		g.addEdge(1, 2);
		g.addEdge(2, 3);
		g.addEdge(4, 6);
		g.addEdge(4, 5);
		g.addEdge(1, 4);
		g.removeEdge(1, 4);
		try {
			g.addEdge(1, -1);
		} catch (...) {
			cout << "edge checking ok" << endl;
		}

		cout << g;
		g.clear();
	} catch (const char *e) {
		cout << e << endl;
	}
}

#endif // GRAPHTEST_H
