#include <iostream>

using namespace std;

#include "ui/mainscreen.h"

int main() {
	MainScreen main(cin, cout);
	main.interact();
}
