#pragma once
#include <iostream>

/* Interactive abstract class
 * Represents an object that has IO interaction with the user
 */
class Interactive {
public:
	virtual ~Interactive() {}

	/* interact
	 * single function of the Interactive that allows the subclass to interact
	 * with IO streams
	 */
	virtual void interact(std::istream &in, std::ostream &out) = 0;
};
