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
	GraphNode(const T &data) : data(data) {}
	GraphNode() {}

	T getData() const;
	void setData(const T &value);

	// these are not to be used. Use comparators instead
	friend bool operator==(const GraphNode<T> &a, const GraphNode<T> &b) {
		return a.data == b.data;
	}

	friend bool operator>(const GraphNode<T> &a, const GraphNode<T> &b) {
		return true; // ok as long as not ==
	}
	friend bool operator<(const GraphNode<T> &a, const GraphNode<T> &b) {
		return true; // ok as long as not ==
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

protected:
	Comparator<T> *dataComparator;

public:
	GraphNodeComparator() : dataComparator(new GenericComparator<T>) {}
	GraphNodeComparator(const Comparator<T> &dataComp) {
		dataComparator = dataComp.clone();
	}
	GraphNodeComparator(const GraphNodeComparator<T> &dataComp) {
		dataComparator = dataComp.dataComparator->clone();
	}
	~GraphNodeComparator() { delete dataComparator; }

	int compare(const GraphNode<T> &a, const GraphNode<T> &b) override {
		return dataComparator->compare(a.getData(), b.getData());
	}
	GraphNodeComparator *clone() const override {
		return new GraphNodeComparator(*this);
	}
	bool strictlyEquals(const GraphNode<T> &a, const GraphNode<T> &b) override {
		return dataComparator->strictlyEquals(a.getData(), b.getData());
	}
};

template <typename T>
class GraphNodePointerComparator : public Comparator<const GraphNode<T> *> {
private:
	GraphNodeComparator<T> comparator; // actual comparator used underneath

public:
	GraphNodePointerComparator() : comparator(GraphNodeComparator<T>()) {}
	GraphNodePointerComparator(const Comparator<T> &dataComp)
			: comparator(GraphNodeComparator<T>(dataComp)) {}
	virtual int compare(const GraphNode<T> *const &a,
											const GraphNode<T> *const &b) override {
		return comparator.compare(*a, *b);
	}

	virtual GraphNodePointerComparator<T> *clone() const override {
		return new GraphNodePointerComparator<T>(*this);
	}

	bool strictlyEquals(const GraphNode<T> *const &a,
											const GraphNode<T> *const &b) override {
		return comparator.strictlyEquals(*a, *b);
	}
};

#endif // GRAPHNODE_H
