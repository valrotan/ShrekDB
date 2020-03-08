#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "interactive.h"


class MainScreen : Interactive
{
public:
	MainScreen();

	void interact(std::istream &in, std::ostream &out);
};

#endif // MAINSCREEN_H
