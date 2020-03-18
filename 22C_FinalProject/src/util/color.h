#ifndef COLORS_H
#define COLORS_H

#include <iostream>
#include <string>
#ifndef __APPLE__
#include <Windows.h>
#endif

/* Windows colors
0   BLACK
1   BLUE
2   GREEN
3   CYAN
4   RED
5   MAGENTA
7   LIGHTGRAY
8   DARKGRAY
9   LIGHTBLUE
10  LIGHTGREEN
11  LIGHTCYAN
12  LIGHTRED
13  LIGHTMAGENTA
14  YELLOW
15  WHITE
*/

/* ANSI Colors
Black	30	40
Red	31	41
Green	32	42
Yellow	33	43
Blue	34	44
Magenta	35	45
Cyan	36	46
White	37	47
Bright Black	90	100
Bright Red	91	101
Bright Green	92	102
Bright Yellow	93	103
Bright Blue	94	104
Bright Magenta	95	105
Bright Cyan	96	106
Bright White	97	107
*/

enum COLOR {
	BLACK = 0,
	GRAY,
	WHITE,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	MAGENTA,
	CYAN,
	BRIGHT_RED,
	BRIGHT_GREEN,
	BRIGHT_BLUE,
	BRIGHT_MAGENTA,
	BRIGHT_CYAN,
	BRIGHT_GRAY,
	RESET,
	SUCCESS = BRIGHT_GREEN,
	WARNING = YELLOW,
	_ERROR = BRIGHT_RED
};

class Color {
private:
#ifndef __APPLE__
	static const int WINDOWS_COLORS[];
#else
	static const int ANSI_COLORS[];
#endif

	COLOR foreground, background;

public:
	// create with setColor(RESET) to reset
	Color(COLOR foreground, COLOR background = BLACK)
			: foreground(foreground), background(background) {}

	friend std::ostream &operator<<(std::ostream &out, const Color &color);
};

#endif // COLORS_H
