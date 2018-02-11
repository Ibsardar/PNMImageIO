#include <iostream>
#include <exception>
#include "pnmio.h"

//for sleep function:
#include "stdlib.h"

int main (int argc, char * argv []) {

    std::cout << "loading images..." << std::endl;

    pnmio thing; // make this a namespace instead of an object...
	try {
		thing.load_image("bird_very_small.pnm", true);
		thing.load_image("feep.pgm", true, false);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	// sleep 20s
	_sleep(20000);

    return 0;
}

// Quick compile: g++ -o OUT pnmio.cpp driver.cpp
