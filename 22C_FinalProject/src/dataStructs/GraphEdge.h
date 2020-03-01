#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H

#include "GraphNode.h"

template <typename T>
class GraphEdge {

	template <typename U>
	friend class Graph;

private:
	const GraphNode<T> *a, *b;
	bool positive;

public:
	GraphEdge(const GraphNode<T> *a, const GraphNode<T> *b) : a(a), b(b) {}
	GraphEdge(const GraphNode<T> *a, const GraphNode<T> *b, bool positive)
			: a(a), b(b), positive(positive) {}
	GraphEdge() {}

	const GraphNode<T> *getA() const;
	void setA(const GraphNode<T> *value);
	const GraphNode<T> *getB() const;
	void setB(const GraphNode<T> *value);
	bool getPositive() const;
	void setPositive(bool value);

	// only really need == for graph edges
	template <typename U>
	friend bool operator==(const GraphEdge<U> &a, const GraphEdge<U> &b);

	friend bool operator>(const GraphEdge<T> &a, const GraphEdge<T> &b) {
		return false;
	}
	friend bool operator<(const GraphEdge<T> &a, const GraphEdge<T> &b) {
		return false;
	}

	friend std::ostream &operator<<(std::ostream &out, const GraphEdge<T> &e) {
		out << e.a << " - " << e.b;
		return out;
	}
	friend std::ostream &operator<<(std::ostream &out, const GraphEdge<T> *e) {
		out << e->a << " - " << e->b;
		return out;
	}
};

template <typename T>
const GraphNode<T> *GraphEdge<T>::getA() const {
	return a;
}

template <typename T>
void GraphEdge<T>::setA(const GraphNode<T> *value) {
	a = value;
}

template <typename T>
const GraphNode<T> *GraphEdge<T>::getB() const {
	return b;
}

template <typename T>
void GraphEdge<T>::setB(const GraphNode<T> *value) {
	b = value;
}

template <typename T>
bool GraphEdge<T>::getPositive() const {
	return positive;
}

template <typename T>
void GraphEdge<T>::setPositive(bool value) {
	positive = value;
}

template <typename T>
bool operator==(const GraphEdge<T> &a, const GraphEdge<T> &b) {
	if (*a.a == *b.a && *a.b == *b.b) {
		return true;
	} else if (*a.a == *b.b && *a.b == *b.a) {
		return true;
	}
	return false;
}

template <typename T>
class GraphEdgeComparator : public Comparator<GraphEdge<T>> {

public:
	GraphEdgeComparator() {}

	int compare(const GraphEdge<T> &a, const GraphEdge<T> &b) override {
		return a == b ? 0 : 1;
	}
	GraphEdgeComparator<T> *clone() const override {
		return new GraphEdgeComparator<T>(*this);
	}
};

template <typename T>
class GraphEdgePointerComparator : public Comparator<const GraphEdge<T> *> {
private:
	GraphEdgeComparator<T> comparator; // actual comparator used underneath

public:
	GraphEdgePointerComparator() { comparator = GraphEdgeComparator<T>(); }
	virtual int compare(const GraphEdge<T> *const &a,
											const GraphEdge<T> *const &b) override {
		return *a == *b ? 0 : 1;
	}

	virtual GraphEdgePointerComparator<T> *clone() const override {
		return new GraphEdgePointerComparator<T>(*this);
	}
};

#endif // GRAPHEDGE_H
