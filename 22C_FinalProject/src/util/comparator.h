#ifndef COMPARATOR_H
#define COMPARATOR_H

template <typename T>
class Comparator {
public:
	virtual ~Comparator() {}

	// return > 0 if a > b
	//        < 0 if a < b
	//          0 if a == b
	virtual int compare(const T &a, const T &b) = 0;

	virtual Comparator<T> *clone() const = 0;

	virtual bool strictlyEquals(const T &a, const T &b) { return a == b; }
};

template <typename T>
class GenericComparator : public Comparator<T> { // generic comparator
public:
	int compare(const T &a, const T &b) override;

	GenericComparator<T> *clone() const override {
		return new GenericComparator<T>(*this);
	}
};

template <typename T>
int GenericComparator<T>::compare(const T &a, const T &b) {
	if (a > b) {
		return 1;
	} else if (a < b) {
		return -1;
	}
	return a == b ? 0 : 1;
}

#endif // COMPARATOR_H
