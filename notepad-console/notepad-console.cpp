// notepad-console.cpp : Defines the entry point for the application.
//

#include "notepad-console.h"

int main(int argc, char *argv[])
{
	// TODO : OPTIONS

	if (argc < 2) {
		// show usage
		return 1;
	}

	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		if ((arg == "-h") || (arg == "--help")) {
			// show usage
			return 0;
		}
		else if ((arg == "-v") || (arg == "--version")) {
			std::cerr << get_ver() << std::endl;
		}
		// TODO : Add a "config" option
	}

	return 0;
}
