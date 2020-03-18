#include "database.h"

void Database::closeAll() {
	closeReadChars();
	closeReadPos();
	closeReadNeg();
	closeWriteChars();
	closeWritePos();
	closeWriteNeg();
}

void Database::openReadChars() {
	closeReadChars();
	charIStream.open(charsPath);
	charIStream.ignore(1000, '\n');
	cio = true;
}

Database &Database::operator>>(Character &c) {
	if (!cio)
		throw "File not open exception";
	charIStream >> c;
	return *this;
}

void Database::closeReadChars() {
	if (cio)
		charIStream.close();
	cio = false;
}

void Database::openReadPos() {
	closeReadPos();
	posIStream.open(posPath);
	pio = true;
}

bool Database::readPos(int &a, int &b) {
	if (!pio)
		throw "File not open exception";
	posIStream >> a >> b;
	return !posIStream.eof();
}

void Database::closeReadPos() {
	if (pio)
		posIStream.close();
	pio = false;
}

void Database::openReadNeg() {
	closeReadNeg();
	negIStream.open(negPath);
	nio = true;
}

bool Database::readNeg(int &a, int &b) {
	if (!nio)
		throw "File not open exception";
	negIStream >> a >> b;
	return !negIStream.eof();
}

void Database::closeReadNeg() {
	if (nio)
		negIStream.close();
	nio = false;
}

void Database::openWriteChars() {
	closeWriteChars();
	charOStream.open(charsPath, std::ios_base::app);
	charOStream << Character::getDBHeader() << std::endl;
	coo = true;
}

Database &Database::operator<<(Character &c) {
	if (!coo)
		throw "File not open exception";
	Character::setPrintStyle(CHARACTER_STYLE_DB);
	charOStream << c << std::endl;
	return *this;
}

void Database::closeWriteChars() {
	if (coo)
		charOStream.close();
	coo = false;
}

void Database::openWritePos() {
	closeWritePos();
	posOStream.open(posPath, std::ios_base::app);
	poo = true;
}

Database &Database::writePos(int a, int b) {
	if (!poo)
		throw "File not open exception";
	posOStream << a << " " << b << "\n";
	return *this;
}

void Database::closeWritePos() {
	if (poo)
		posOStream.close();
	poo = false;
}

void Database::openWriteNeg() {
	closeWriteNeg();
	negOStream.open(negPath, std::ios_base::app);
	noo = true;
}

Database &Database::writeNeg(int a, int b) {
	if (!noo)
		throw "File not open exception";
	negOStream << a << " " << b << "\n";
	return *this;
}

void Database::closeWriteNeg() {
	if (noo)
		negOStream.close();
	noo = false;
}

void Database::clearChars() {
	charOStream.open(charsPath);
	charOStream.clear();
	charOStream.close();
}

void Database::clearPos() {
	posOStream.open(posPath);
	posOStream.clear();
	posOStream.close();
}

void Database::clearNeg() {
	negOStream.open(negPath);
	negOStream.clear();
	negOStream.close();
}

std::ifstream &Database::getCharIStream() { return charIStream; }

std::ofstream &Database::getCharOStream() { return charOStream; }

std::ifstream &Database::getPosIStream() { return posIStream; }

std::ofstream &Database::getPosOStream() { return posOStream; }

std::ifstream &Database::getNegIStream() { return negIStream; }

std::ofstream &Database::getNegOStream() { return negOStream; }
