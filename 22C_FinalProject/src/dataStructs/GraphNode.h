#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include "Graph.h"

template <typename T>
class GraphNode {
	template <typename U>
	friend class Graph;
	template <typename U>
	friend class GraphEdge;

private:
	T data;

public:
	GraphNode(const T &data);
	GraphNode() {}

	T getData() const;
	void setData(const T &value);

	// only really need == for graph nodes
	friend bool operator==(const GraphNode<T> &a, const GraphNode<T> &b) {
		return a.data == b.data;
	}

	friend bool operator>(const GraphNode<T> &a, const GraphNode<T> &b) {
		return false;
	}
	friend bool operator<(const GraphNode<T> &a, const GraphNode<T> &b) {
		return false;
	}

	friend std::ostream &operator<<(std::ostream &out, const GraphNode<T> &n) {
		out << n.data;
		return out;
	}
	friend std::ostream &operator<<(std::ostream &out, const GraphNode<T> *n) {
		out << n->data;
		return out;
	}
};

template <typename T>
GraphNode<T>::GraphNode(const T &data) : data(data) {}

template <typename T>
T GraphNode<T>::getData() const {
	return data;
}

template <typename T>
void GraphNode<T>::setData(const T &value) {
	data = value;
}

// TODO could add T comparator here
template <typename T>
class GraphNodeComparator : public Comparator<GraphNode<T>> {

public:
	GraphNodeComparator() {}

	int compare(const GraphNode<T> &a, const GraphNode<T> &b) override {
		return a == b ? 0 : 1;
	}
	GraphNodeComparator *clone() const override {
		return new GraphNodeComparator(*this);
	}
};

template <typename T>
class GraphNodePointerComparator : public Comparator<const GraphNode<T> *> {
private:
	GraphNodeComparator<T> comparator; // actual comparator used underneath

public:
	GraphNodePointerComparator() { comparator = GraphNodeComparator<T>(); }
	virtual int compare(const GraphNode<T> *const &a,
											const GraphNode<T> *const &b) override {
		return *a == *b ? 0 : 1;
	}

	virtual GraphNodePointerComparator<T> *clone() const override {
		return new GraphNodePointerComparator<T>(*this);
	}
};

#endif // GRAPHNODE_H
