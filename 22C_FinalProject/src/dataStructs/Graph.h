#ifndef GRAPH_H
#define GRAPH_H

#include "GraphEdge.h"
#include "LinkedList.h"
#include <iomanip>
#include <iostream>
#include <sstream>

enum GRAPH_STYLE { GRAPH_STYLE_ADJ_MATRIX = 0 };

template <typename T>
class Graph {
private:
	LinkedList<const GraphNode<T> *> *nodes;
	LinkedList<const GraphEdge<T> *> *edges;

public:
	Graph();
	Graph(const Comparator<T> &dataComparator);
	~Graph();

	void addNode(const T &data);
	T removeNode(const T &data);
	T removeNodeByIndex(int index);
	bool containsNode(const T &data);
	int findNode(const T &data);

	// throws exception if not found
	T getNode(const T &data);

	void clearNodes();
	int countNodes();

	T getNodeByIndex(int index);

	void addEdge(const T &a, const T &b, bool positive = false);
	void removeEdge(const T &a, const T &b);
	void removeEdgeByIndex(int index);
	bool containsEdge(const T &a, const T &b);
	int findEdge(const T &a, const T &b);

	bool isEdgePositive(const T &a, const T &b);
	bool isEdgePositive(int index);

	void clearEdges();
	int countEdges();

	void clear();

	template <typename U>
	friend std::ostream &operator<<(std::ostream &out, Graph<U> &g);
};

template <typename T>
Graph<T>::Graph() {
	GraphNodePointerComparator<T> nodeComparator;
	GraphEdgePointerComparator<T> edgeComparator;

	nodes = new LinkedList<const GraphNode<T> *>(*nodeComparator);
	edges = new LinkedList<const GraphEdge<T> *>(*edgeComparator);
}

template <typename T>
Graph<T>::Graph(const Comparator<T> &dataComparator) {
	std::cout << "creating comparators\n";
	GraphNodePointerComparator<T> nodeComparator(dataComparator);
	GraphEdgePointerComparator<T> edgeComparator(dataComparator);

	std::cout << "creating lists\n";
	nodes = new LinkedList<const GraphNode<T> *>(nodeComparator);
	edges = new LinkedList<const GraphEdge<T> *>(edgeComparator);
}

template <typename T>
Graph<T>::~Graph() {
	delete nodes;
	delete edges;
}

template <typename T>
void Graph<T>::addNode(const T &data) {
	nodes->add(new GraphNode<T>(data));
}

template <typename T>
T Graph<T>::removeNode(const T &data) {
	GraphNode<T> temp(data);
	int nodeInd = nodes->find(&temp);
	return removeNodeByIndex(nodeInd);
}

template <typename T>
T Graph<T>::removeNodeByIndex(int index) {
	if (index < 0 || index >= nodes->getCount())
		throw "Graph: node index out of bounds exception.";
	const GraphNode<T> *temp = nodes->remove(index);
	T data = temp->data;
	delete temp;
	return data;
}

template <typename T>
bool Graph<T>::containsNode(const T &data) {
	return findNode(data) == -1;
}

template <typename T>
int Graph<T>::findNode(const T &data) {
	GraphNode<T> temp(data);
	return nodes->find(&temp);
}

template <typename T>
T Graph<T>::getNode(const T &data) {
	return getNode(findNode(data));
}

template <typename T>
T Graph<T>::getNodeByIndex(int index) {
	if (index < 0 || index >= nodes->getCount())
		throw "Graph: node index out of bounds exception.";
	return nodes->getData(index)->data;
}

template <typename T>
void Graph<T>::addEdge(const T &a, const T &b, bool positive) {
	int indA = findNode(a), indB = findNode(b);
	if (indA != -1 && indB != -1) {
		GraphEdge<T> *temp =
				new GraphEdge<T>(nodes->getData(indA), nodes->getData(indB), positive);
		edges->add(temp);
	} else {
		throw "Graph: node not found exception.";
	}
}

template <typename T>
void Graph<T>::removeEdge(const T &a, const T &b) {
	removeEdgeByIndex(findEdge(a, b));
}

template <typename T>
void Graph<T>::removeEdgeByIndex(int index) {
	if (index < 0 || index > edges->getCount())
		throw "Graph: edge index out of bounds.";
	const GraphEdge<T> *removed = edges->remove(index);
	delete removed;
}

template <typename T>
bool Graph<T>::containsEdge(const T &a, const T &b) {
	return findEdge(a, b) != -1;
}

template <typename T>
int Graph<T>::findEdge(const T &a, const T &b) {
	const GraphNode<T> *tempNodeA = nodes->getData(findNode(a));
	const GraphNode<T> *tempNodeB = nodes->getData(findNode(b));
	if (!tempNodeA || !tempNodeB)
		return -1;
	GraphEdge<T> temp(tempNodeA, tempNodeB);
	return edges->find(&temp);
}

template <typename T>
bool Graph<T>::isEdgePositive(const T &a, const T &b) {
	return isEdgePositive(findEdge(a, b));
}

template <typename T>
bool Graph<T>::isEdgePositive(int index) {
	if (index < 0 || index > edges->getCount())
		throw "Graph: edge index out of bounds.";
	return edges->getData(index)->isPositive;
}

template <typename T>
void Graph<T>::clearNodes() {
	nodes->emptyList();
}

template <typename T>
int Graph<T>::countNodes() {
	return nodes->getCount();
}

template <typename T>
void Graph<T>::clearEdges() {
	edges->emptyList();
}

template <typename T>
int Graph<T>::countEdges() {
	return edges->getCount();
}

template <typename T>
void Graph<T>::clear() {
	clearNodes();
	clearEdges();
}

template <typename T>
std::ostream &operator<<(std::ostream &out, Graph<T> &g) {
	out << "Nodes\n";
	out << *g.nodes << std::endl;

	out << "Edges\n";
	out << *g.edges << std::endl;

	out << "Graph\n";
	for (int i = 0; i < g.nodes->getCount(); i++) {
		std::stringstream s;
		s << g.getNodeByIndex(i);
		out << std::setw(12) << s.str().substr(0, 12) << " |";
		for (int j = 0; j < g.nodes->getCount(); j++) {
			if (g.containsEdge(g.getNodeByIndex(i), g.getNodeByIndex(j))) {
				if (g.isEdgePositive(g.getNodeByIndex(i), g.getNodeByIndex(j))) {
					out << "+|";
				} else {
					out << "-|";
				}
			} else {
				out << " |";
			}
		}
		out << std::endl;
	}

	int rows = 6;
	for (int i = 0; i < rows; i++) {
		out << std::setw(13 + i * 2) << " ";
		for (int j = i; j < g.countNodes(); j += rows) {
			T el = g.getNodeByIndex(j);
			std::stringstream s;
			s << el;
			out << "|" << std::setw(rows * 2 - 1) << std::left
					<< s.str().substr(0, rows * 2 - 2);
		}
		out << std::endl;
	}

	return out;
}

#endif // GRAPH_H
