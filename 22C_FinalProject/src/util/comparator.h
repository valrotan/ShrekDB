#ifndef COMPARATOR_H
#define COMPARATOR_H

template<typename T>
class Comparator {
public:
	virtual ~Comparator() {}

	// analogous to a - b
	// return > 0 if a > b
	//        < 0 if a < b
	//          0 if a == b
	virtual int compare(const T &a, const T &b) = 0;
};

#endif // COMPARATOR_H
