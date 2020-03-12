#pragma once

#include "../util/comparator.h"
#include "BST_Node.h"
#include "LinkedList.h"
#include "Queue.h"
#include <iomanip>
#include <iostream>
#include <string>

enum BST_TRAVERSAL {
	BST_BREADTH_FIRST = 0,
	BST_PREORDER,
	BST_INORDER,
	BST_POSTORDER,
	BST_PRETTY_BREADTH_FIRST,
	BST_PRETTY_INORDER,
	BST_PRETTY_PREORDER
};

template <typename T>
class BST {
private:
	BST_Node<T> *root;

	BST_TRAVERSAL traversalOrder;

	Comparator<T> *comparator;

	// private helper functions
	BST_Node<T> *createNode(T data);

	BST_Node<T> *findLargest(BST_Node<T> *root);
	BST_Node<T> *findSmallest(BST_Node<T> *root);
	void addHelper(BST_Node<T> *node, const T &val, int &nOps);
	BST_Node<T> *searchHelper(BST_Node<T> *root, const T &key, int &nOps);
	BST_Node<T> *removeHelper(BST_Node<T> *root, const T &key);
	int count(BST_Node<T> *node);
	int maxHeight(BST_Node<T> *node);

	void emptyHelper(BST_Node<T> *node);
	void preOrderTravHelper(BST_Node<T> *root, std::ostream &out);
	void inOrderTravHelper(BST_Node<T> *root, std::ostream &out);
	void postOrderTravHelper(BST_Node<T> *root, std::ostream &out);
	void prettyBreadthFirst(BST_Node<T> *root, std::ostream &out);
	void prettyInorder(BST_Node<T> *root, std::ostream &out, int h = 0);
	void prettyPreorder(BST_Node<T> *root, std::ostream &out,
											std::string prefix = "");

public:
	BST(const T &data);
	BST(const T &data, const Comparator<T> &comparator);
	BST();
	BST(const Comparator<T> &comparator);
	~BST();

	// add/remove data into the tree
	void add(const T &data);
	void add(const T &data, int &nOps);

	// removes value from the tree and returns it
	// trows excpetion if key is not found in the tree
	T remove(const T &key);

	// empties the tree
	void empty();

	// returns true if the tree is empty
	bool isEmpty();

	// returns the number of nodes in the tree
	int count();

	// searches for value key in the tree based on the provided comparator
	// returns true if element is found in the tree, false otherwise
	bool contains(const T &key);

	// searches for value key in the tree based on
	// throws exception if key is not found in the tree
	T search(const T &key);
	T search(const T &key, int &nOps);

	// find largest/smallest
	T findLargestData();
	T findSmallestData();

	// traversals
	void breadthFirstTrav(std::ostream &out);
	void preOrderTrav(std::ostream &out);
	void inOrderTrav(std::ostream &out);
	void postOrderTrav(std::ostream &out);

	// sets the traversal order of the tree. << operator will use the specified
	// order. BST_INORDER is default.
	void setOrder(BST_TRAVERSAL order);

	// output operator. Traverses the tree in traversalOrder and outputs nodes to
	// out
	template <typename U>
	friend std::ostream &operator<<(std::ostream &out, BST<U> &bst);
};

template <typename T>
BST<T>::BST() {
	root = nullptr;
	comparator = new GenericComparator<T>;
}

template <typename T>
BST<T>::BST(const Comparator<T> &comp) {
	root = nullptr;
	comparator = comp.clone();
}

template <typename T>
BST<T>::BST(const T &data) {
	root = createNode(data);
	comparator = new GenericComparator<T>;
}

template <typename T>
BST<T>::BST(const T &data, const Comparator<T> &comp) {
	root = createNode(data);
	comparator = comp.clone();
}

template <typename T>
BST_Node<T> *BST<T>::createNode(T data) {
	return new BST_Node<T>(data);
}

template <typename T>
BST<T>::~BST() {
	empty();
	delete comparator;
}

template <typename T>
int BST<T>::maxHeight(BST_Node<T> *node) {
	if (!node) {
		return -1;
	}
	int lH = 1 + maxHeight(node->left);
	int rH = 1 + maxHeight(node->right);
	return rH > lH ? rH : lH;
}

template <typename T>
T BST<T>::findLargestData() {
	if (!root)
		throw "Exception: tree is empty";
	return findLargest(this->root)->getData();
}

template <typename T>
BST_Node<T> *BST<T>::findLargest(BST_Node<T> *root) {
	if (root->right)
		return findLargest(root->right);
	return root;
}

template <typename T>
T BST<T>::findSmallestData() {
	if (!root)
		throw "Exception: tree is empty";
	return findSmallest(this->root)->getData();
}

template <typename T>
BST_Node<T> *BST<T>::findSmallest(BST_Node<T> *root) {
	if (root->left)
		return findSmallest(root->left);
	return root;
}

template <typename T>
void BST<T>::addHelper(BST_Node<T> *node, const T &val, int &nOps) {
	nOps++;
	if (comparator->compare(val, node->data) < 0) {
		if (node->left) {
			addHelper(node->left, val, nOps);
		} else {
			node->left = createNode(val);
		}
	} else {
		if (node->right) {
			addHelper(node->right, val, nOps);
		} else {
			nOps++;
			node->right = createNode(val);
		}
	}
}

template <typename T>
void BST<T>::add(const T &data) {
	int nOps = 0;
	add(data, nOps);
}

template <typename T>
void BST<T>::add(const T &data, int &nOps) {
	if (this->root == nullptr) {
		nOps++;
		root = createNode(data);
	} else {
		addHelper(this->root, data, nOps);
	}
}

template <typename T>
T BST<T>::remove(const T &key) {
	BST_Node<T> *node = removeHelper(this->root, key);
	if (node)
		return node->data;
	else
		throw "Not found";
}

template <typename T>
BST_Node<T> *BST<T>::removeHelper(BST_Node<T> *node, const T &key) {
	if (!node) // if there's no parent, return null
		return nullptr;

	if (comparator->compare(key, node->data) < 0)
		// if key is less than root->data, assign root->left to
		// the deleted node
		node->left = removeHelper(node->left, key);

	else if (comparator->compare(key, node->data) > 0)
		// if more, assign the right child to be the deleted node
		node->right = removeHelper(node->right, key);

	else { // found the right node
		if (node == this->root) {

			if (!node->left) { // if no left child, assign temp to left, delete
												 // current node and return temp
				this->root = node->right;
				delete node;
				return root;
			} else if (!node->right) {
				this->root = node->left;
				delete node;
				return root;
			} else {
				// has both children
				node->data = findLargest(node->left)->data;
				node->left = removeHelper(node->left, node->data);
			}

		} else if (!node->left) { // if no left child, assign temp to left, delete
															// current node and return temp
			BST_Node<T> *temp = node->right;
			delete node;
			return temp;
		} else if (!node->right) {
			BST_Node<T> *temp = node->left;
			delete node;
			return temp;
		} else {
			// has both children
			node->data = findLargest(node->left)->data;
			node->left = removeHelper(node->left, node->data);
		}
	}
	return node;
}

template <typename T>
void BST<T>::emptyHelper(BST_Node<T> *node) {
	if (node) {
		emptyHelper(node->left);
		emptyHelper(node->right);
		delete node;
	}
}

template <typename T>
void BST<T>::empty() {
	emptyHelper(root);
	root = nullptr;
}

template <typename T>
bool BST<T>::isEmpty() {
	return root == nullptr;
}

template <typename T>
int BST<T>::count(BST_Node<T> *node) {
	if (node) {
		return 1 + count(node->left) + count(node->right);
	}
	return 0;
}

template <typename T>
int BST<T>::count() {
	return count(root);
}

template <typename T>
bool BST<T>::contains(const T &key) {
	int nOps = 0;
	BST_Node<T> *node = searchHelper(this->root, key, nOps);
	if (node)
		return true;
	else {
		return false;
	}
}

template <typename T>
T BST<T>::search(const T &key) {
	int nOps = 0;
	BST_Node<T> *node = searchHelper(this->root, key, nOps);
	if (node)
		return node->data;
	else {
		throw "Data doesn't exist in BST.";
	}
}

template <typename T>
T BST<T>::search(const T &key, int &nOps) {
	BST_Node<T> *node = searchHelper(this->root, key, nOps);
	if (node)
		return node->data;
	else {
		throw "Data doesn't exist in BST.";
	}
}

template <typename T>
BST_Node<T> *BST<T>::searchHelper(BST_Node<T> *root, const T &key, int &nOps) {
	if (!root)
		return nullptr;
	nOps++;
	if (comparator->compare(key, root->data) < 0)
		return searchHelper(root->left, key, nOps);
	nOps++;
	if (comparator->compare(key, root->data) > 0)
		return searchHelper(root->right, key, nOps);
	return root;
}

template <typename T>
void BST<T>::breadthFirstTrav(std::ostream &out) {
	Queue<BST_Node<T> *> queue;
	queue.enqueue(this->root);

	while (!queue.isEmpty()) {

		BST_Node<T> *root = queue.dequeue();
		out << root->data << std::endl;

		if (root->left)
			queue.enqueue(root->left);
		if (root->right)
			queue.enqueue(root->right);
	}
}

template <typename T>
void BST<T>::preOrderTrav(std::ostream &out) {
	preOrderTravHelper(this->root, out);
}

template <typename T>
void BST<T>::preOrderTravHelper(BST_Node<T> *root, std::ostream &out) {
	if (!root)
		return;
	out << root->data << std::endl;
	preOrderTravHelper(root->left, out);
	preOrderTravHelper(root->right, out);
}

template <typename T>
void BST<T>::inOrderTrav(std::ostream &out) {
	inOrderTravHelper(this->root, out);
}

template <typename T>
void BST<T>::inOrderTravHelper(BST_Node<T> *root, std::ostream &out) {
	if (!root)
		return;
	inOrderTravHelper(root->left, out);
	out << root->data << std::endl;
	inOrderTravHelper(root->right, out);
}

template <typename T>
void BST<T>::postOrderTrav(std::ostream &out) {
	postOrderTravHelper(this->root, out);
}

template <typename T>
void BST<T>::postOrderTravHelper(BST_Node<T> *root, std::ostream &out) {

	if (!root)
		return;
	postOrderTravHelper(root->left, out);
	postOrderTravHelper(root->right, out);
	out << root->data << std::endl;
}

template <typename T>
void BST<T>::prettyInorder(BST_Node<T> *root, std::ostream &out, int h) {
	if (!root)
		return;
	prettyInorder(root->left, out, h + 1);
	out << std::setw(2 * h + 2) << "" << root->data << std::endl;
	prettyInorder(root->right, out, h + 1);
}

template <typename T>
void BST<T>::prettyPreorder(BST_Node<T> *root, std::ostream &out,
														std::string prefix) {

	if (!root) {
		return;
	}

	bool hasLeft = (root->left);
	bool hasRight = (root->right);

	if (!hasLeft && !hasRight) {
		return;
	}

	out << prefix;
	out << ((hasLeft && hasRight) ? "├── " : "");
	out << ((!hasLeft && hasRight) ? "└── " : "");

	if (hasRight) {
		bool printStrand =
				(hasLeft && hasRight && (root->right->right || root->right->left));
		std::string newPrefix = prefix + (printStrand ? "│   " : "    ");
		out << root->right->data << std::endl;
		prettyPreorder(root->right, out, newPrefix);
	}

	if (hasLeft) {
		out << (hasRight ? prefix : "") << "└── " << root->left->data << std::endl;
		prettyPreorder(root->left, out, prefix + "    ");
	}
}

template <typename T>
void BST<T>::prettyBreadthFirst(BST_Node<T> *root, std::ostream &out) {

	Queue<BST_Node<T> *> queue;
	queue.enqueue(root);

	int nLeaves = 0, nextLeaves = 1;
	int h = maxHeight(root) + 1;
	out << h << "maxh\n";

	while (!queue.isEmpty()) {

		if (nLeaves == 0) {
			out << std::endl;
			nLeaves = nextLeaves;
			nextLeaves = 0;
			h--;
			for (int i = 0; i < h * (h - 1) + 1 && h != 0; i++) {
				out << "_ ";
			}
		}

		BST_Node<T> *root = queue.dequeue();
		nLeaves--;
		if (h > 0) {
			nextLeaves += 2;
			if (root) {
				out << root->data << " ";
				queue.enqueue(root->left);
				queue.enqueue(root->right);
			} else {
				out << "x ";
				queue.enqueue(nullptr);
				queue.enqueue(nullptr);
			}
		} else { // h == 0
			if (root) {
				out << root->data << " ";
			} else {
				out << "x ";
			}
		}
		for (int i = 0; i < h * (h + 1) + 1 && h >= 0; i++) {
			out << "_ ";
		}
	}
}

template <typename U>
std::ostream &operator<<(std::ostream &out, BST<U> &bst) {
	switch (bst.traversalOrder) {
	case BST_BREADTH_FIRST:
		bst.breadthFirstTrav(out);
		break;
	case BST_PREORDER:
		bst.preOrderTravHelper(bst.root, out);
		break;
	case BST_INORDER:
		bst.inOrderTravHelper(bst.root, out);
		break;
	case BST_POSTORDER:
		bst.postOrderTravHelper(bst.root, out);
		break;
	case BST_PRETTY_BREADTH_FIRST:
		bst.prettyBreadthFirst(bst.root, out);
		break;
	case BST_PRETTY_INORDER:
		bst.prettyInorder(bst.root, out);
		break;
	case BST_PRETTY_PREORDER:
		out << bst.root->getData() << std::endl;
		bst.prettyPreorder(bst.root, out);
		break;
	}
	return out;
}

template <typename T>
void BST<T>::setOrder(BST_TRAVERSAL order) {
	traversalOrder = order;
}
