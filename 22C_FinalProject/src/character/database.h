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

public:
	Database(std::string charsPath, std::string posPath, std::string negPath)
			: charsPath(charsPath), posPath(posPath), negPath(negPath) {}
	~Database() { closeAll(); }

	void closeAll();

	void openReadChars();
	Database &operator>>(Character &c);
	bool doneReadingChars() { return charIStream.eof(); }
	void closeReadChars();

	void openReadPos();
	bool readPos(int &a, int &b);
	bool doneReadingPos() { return posIStream.eof(); }
	void closeReadPos();

	void openReadNeg();
	bool readNeg(int &a, int &b);
	bool doneReadingNeg() { return negIStream.eof(); }
	void closeReadNeg();

	void openWriteChars();
	Database &operator<<(Character &c);
	void closeWriteChars();

	void openWritePos();
	Database &writePos(int a, int b);
	void closeWritePos();

	void openWriteNeg();
	Database &writeNeg(int a, int b);
	void closeWriteNeg();

	void clearChars();
	void clearPos();
	void clearNeg();

	std::ifstream &getCharIStream();
	std::ifstream &getPosIStream();
	std::ifstream &getNegIStream();
	std::ofstream &getCharOStream();
	std::ofstream &getPosOStream();
	std::ofstream &getNegOStream();
};

#endif // DATABASE_H
