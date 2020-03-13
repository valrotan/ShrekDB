#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H

#include "GraphNode.h"

template <typename T>
class GraphEdge {

	template <typename U>
	friend class Graph;

private:
	const GraphNode<T> *a, *b;
	bool isPositive;

public:
	GraphEdge(const GraphNode<T> *a, const GraphNode<T> *b) : a(a), b(b) {}
	GraphEdge(const GraphNode<T> *a, const GraphNode<T> *b, bool isPositive)
			: a(a), b(b), isPositive(isPositive) {}
	GraphEdge() {}

	const GraphNode<T> *getA() const;
	void setA(const GraphNode<T> *value);
	const GraphNode<T> *getB() const;
	void setB(const GraphNode<T> *value);
	bool getIsPositive() const;
	void setIsPositive(bool value);

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
		if (e.isPositive)
			out << e.a << " + " << e.b;
		else
			out << e.a << " - " << e.b;
		return out;
	}
	friend std::ostream &operator<<(std::ostream &out, const GraphEdge<T> *e) {
		if (e->isPositive)
			out << e->a << " + " << e->b;
		else
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
bool GraphEdge<T>::getIsPositive() const {
	return isPositive;
}

template <typename T>
void GraphEdge<T>::setIsPositive(bool value) {
	isPositive = value;
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

private:
	Comparator<T> *dataComparator;

public:
	GraphEdgeComparator() : dataComparator(new GenericComparator<T>) {}
	GraphEdgeComparator(const Comparator<T> &comparator)
			: dataComparator(comparator.clone()) {}
	~GraphEdgeComparator() { delete dataComparator; }
	GraphEdgeComparator(const GraphEdgeComparator<T> &old) {
		dataComparator = old.dataComparator->clone();
	}

	int compare(const GraphEdge<T> &a, const GraphEdge<T> &b) override;
	GraphEdgeComparator<T> *clone() const override {
		return new GraphEdgeComparator<T>(*dataComparator);
	}
};

template <typename T>
int GraphEdgeComparator<T>::compare(const GraphEdge<T> &a,
																		const GraphEdge<T> &b) {
	if (dataComparator->compare(a.getA()->getData(), b.getA()->getData()) == 0 &&
			dataComparator->compare(a.getB()->getData(), b.getB()->getData()) == 0) {
		if (a.getIsPositive() == b.getIsPositive()) {
			return 0;
		} else {
			return 0; // dont check sign
		}
	}
	if (dataComparator->compare(a.getA()->getData(), b.getB()->getData()) == 0 &&
			dataComparator->compare(a.getB()->getData(), b.getA()->getData()) == 0) {
		if (a.getIsPositive() == b.getIsPositive()) {
			return 0;
		} else {
			return 0; // dont check sign
		}
	}
	return 1;
}

template <typename T>
class GraphEdgePointerComparator : public Comparator<const GraphEdge<T> *> {
private:
	GraphEdgeComparator<T> comparator; // actual comparator used underneath

public:
	GraphEdgePointerComparator() { comparator = GraphEdgeComparator<T>(); }
	GraphEdgePointerComparator(const Comparator<T> &comparator)
			: comparator(GraphEdgeComparator<T>(comparator)) {}

	int compare(const GraphEdge<T> *const &a,
							const GraphEdge<T> *const &b) override {
		return comparator.compare(*a, *b);
	}

	GraphEdgePointerComparator<T> *clone() const override {
		return new GraphEdgePointerComparator<T>(*this);
	}

	bool strictlyEquals(const GraphEdge<T> *const &a,
											const GraphEdge<T> *const &b) override {
		return *a == *b;
	}
};

#endif // GRAPHEDGE_H
