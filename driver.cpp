#include <iostream>
#include <exception>
#include "pnmio.h"

//for sleep function:
#include "stdlib.h"

int main (int argc, char * argv []) {

	try {

		pnmio thing; // make this a namespace instead of an object...

		std::cout << "loading images..." << std::endl;
		
		Image bird = thing.load_image("bird_very_small.pnm", true);
		Image feep = thing.load_image("feep.pgm", true, false);

		std::cout << "storing images..." << std::endl;

		thing.store_image("stored_feep.pnm", feep, true);
		thing.store_image("stored_very_small_bird.pnm", bird, true);

	} catch (std::exception &e) {
		
		std::cout << e.what() << std::endl;
	
	}

	// sleep 20s
	_sleep(20000);

    return 0;
}

// Quick compile: g++ -o OUT pnmio.cpp driver.cpp
