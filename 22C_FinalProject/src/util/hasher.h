#pragma once

#include <string>

template <typename T>
class Hasher {
public:
	virtual ~Hasher() {}
	virtual long hash(T key, const int size) = 0;
	virtual Hasher* clone() const = 0;
};

class IntegerHasher : public Hasher<int> {
public:
	~IntegerHasher() {}
	long hash(int k, const int size) override {
		unsigned long key = k * k * k;
		return key % size;
	} 

	IntegerHasher* clone() const override {
		return new IntegerHasher(*this);
	};
};


class StringHasher : public Hasher<std::string> {
private:
	int getSumChars(std::string k) {
		int sum = 0;
		for (int i = 0; k[i] != '\0'; i++)
			sum += k[i];
		return sum;
	}

public:
	~StringHasher() {}
	long hash(std::string k, const int size) override {
		int kk = getSumChars(k);
		unsigned long key = kk * kk * kk;
		return key % size;
	}
	StringHasher* clone() const override {
		return new StringHasher(*this);
	};
};
