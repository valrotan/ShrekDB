#include "ioutil.h"

#include <iostream>

void IOUtil::clearScreen() {
#ifndef __APPLE__
	system("cls");
#else
	system("clear");
#endif
}
