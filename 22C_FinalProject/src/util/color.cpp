#include "color.h"
#include <iostream>
#include <sstream>

#ifndef __APPLE__
static const int WINDOWS_COLORS[] = {0, 8,  15, 4, 2,  1,  14, 5,
																		 3, 12, 10, 9, 13, 11, 7,  15};
#else
static const int ANSI_COLORS[] = {30, //
																	40, //
																	97, //
																	31, //
																	32, //
																	34, //
																	93, //
																	35, //
																	36, //
																	91, //
																	92, //
																	94, //
																	95, //
																	96, //
																	97, //
																	0};
#endif

std::ostream &operator<<(std::ostream &out, const Color &color) {
#ifndef __APPLE__
	if ((foreground % 16) == (background % 16))
		foreground++;
	foreground %= 16;
	background %= 16;
	unsigned short wAttributes =
			((unsigned)background << 4) | (unsigned)foreground;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	SetConsoleTextAttribute(hStdOut, wAttributes);
#else
	if (color.foreground == RESET) {
		out << "\u001b[0m";
	} else {
		std::stringstream s;
		s << "\u001b[" << ANSI_COLORS[color.foreground] << ";"
			<< ANSI_COLORS[color.background] + 10 << "m";
		out << s.str();
	}
#endif
	return out;
}
