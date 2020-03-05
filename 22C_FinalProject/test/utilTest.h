#ifndef UTILTEST_H
#define UTILTEST_H

#include "../src/util/color.h"
#include <iostream>

using namespace std;

void runUtilTests() {
	for (int i = 0; i <= RESET; i++) {
		for (int j = 0; j <= RESET; j++) {
			cout << Color((COLOR)i, (COLOR)j) << "abc";
		}
	}

}

#endif // UTILTEST_H
