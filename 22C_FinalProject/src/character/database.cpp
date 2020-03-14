#include "database.h"

std::ifstream &Database::getCharIStream() { return charIStream; }

std::ofstream &Database::getCharOStream() { return charOStream; }

std::ifstream &Database::getPosIStream() { return posIStream; }

std::ofstream &Database::getPosOStream() { return posOStream; }

std::ifstream &Database::getNegIStream() { return negIStream; }

std::ofstream &Database::getNegOStream() { return negOStream; }
