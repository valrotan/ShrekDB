#include "bstTest.h"
#include "charactertest.h"
#include <iostream>
using namespace std;

int main() {
	cout << "Running tests..." << endl;
	characterTests();
	runBSTTests();
}
