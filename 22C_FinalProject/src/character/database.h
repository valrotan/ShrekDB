#ifndef DATABASE_H
#define DATABASE_H

#include "character.h"
#include <fstream>
#include <iostream>
#include <string>

class Database {
private:
	std::string charsPath, posPath, negPath;

	std::ifstream charIStream, posIStream, negIStream;
	std::ofstream charOStream, posOStream, negOStream;

	bool cio, pio, nio, coo, poo, noo; // Characters In Open, Pos In Open...

	void closeAll() {
		closeReadChars();
		closeReadPos();
		closeReadNeg();
		closeWriteChars();
		closeWritePos();
		closeWriteNeg();
	}

public:
	Database(std::string charsPath, std::string posPath, std::string negPath)
			: charsPath(charsPath), posPath(posPath), negPath(negPath) {}
	~Database() { closeAll(); }

	void openReadChars() {
		closeReadChars();
		charIStream.open(charsPath);
		charIStream.ignore(1000, '\n');
		cio = true;
	}
	Database &operator>>(Character &c) {
		if (!cio)
			throw "File not open exception";
		charIStream >> c;
		return *this;
	}
	bool doneReadingChars() { return charIStream.eof(); }
	void closeReadChars() {
		if (cio)
			charIStream.close();
		cio = false;
	}

	void openReadPos() {
		closeReadPos();
		posIStream.open(posPath);
		pio = true;
	}
	Database &readPos(int &a, int &b) {
		if (!pio)
			throw "File not open exception";
		posIStream >> a >> b;
		return *this;
	}
	bool doneReadingPos() { return posIStream.eof(); }
	void closeReadPos() {
		if (pio)
			posIStream.close();
		pio = false;
	}

	void openReadNeg() {
		closeReadNeg();
		negIStream.open(negPath);
		nio = true;
	}
	Database &readNeg(int &a, int &b) {
		if (!nio)
			throw "File not open exception";
		negIStream >> a >> b;
		return *this;
	}
	bool doneReadingNeg() { return negIStream.eof(); }
	void closeReadNeg() {
		if (nio)
			negIStream.close();
		nio = false;
	}

	void openWriteChars() {
		closeWriteChars();
		charOStream.open(charsPath, std::ios_base::app);
		charOStream << Character::getDBHeader() << std::endl;
		coo = true;
	}
	Database &operator<<(Character &c) {
		if (!coo)
			throw "File not open exception";
		Character::setPrintStyle(CHARACTER_STYLE_DB);
		charOStream << c << std::endl;
		return *this;
	}
	void closeWriteChars() {
		if (coo)
			charOStream.close();
		coo = false;
	}

	void openWritePos() {
		closeWritePos();
		posOStream.open(posPath, std::ios_base::app);
		poo = true;
	}
	Database &writePos(int &a, int &b) {
		if (!pio)
			throw "File not open exception";
		posOStream << a << b;
		return *this;
	}
	void closeWritePos() {
		if (poo)
			posOStream.close();
		poo = false;
	}

	void openWriteNeg() {
		closeWriteNeg();
		negOStream.open(negPath, std::ios_base::app);
		noo = true;
	}
	Database &writeNeg(int &a, int &b) {
		if (!noo)
			throw "File not open exception";
		negOStream << a << b;
		return *this;
	}
	void closeWriteNeg() {
		if (noo)
			negOStream.close();
		noo = false;
	}

	void clearChars() {
		charOStream.open(charsPath);
		charOStream.clear();
		charOStream.close();
	}
	void clearPos() {
		posOStream.open(posPath);
		posOStream.clear();
		posOStream.close();
	}
	void clearNeg() {
		negOStream.open(negPath);
		negOStream.clear();
		negOStream.close();
	}
	std::ifstream &getCharIStream();
	std::ifstream &getPosIStream();
	std::ifstream &getNegIStream();
	std::ofstream &getCharOStream();
	std::ofstream &getPosOStream();
	std::ofstream &getNegOStream();
};

#endif // DATABASE_H
