#include "utils.hpp"
#include "game.hpp"

void usage() {
	std::cout
		<< "Usage: terrain [seed]" 							 << std::endl
		<< "  Run the aplication with a given seed" 		 << std::endl
		<< "  [seed] must be a 32bit unsigned integer value" << std::endl;

	exit(1);
}

int main(int argc, char** argv) {
	if (argc != 2)
		usage();

	//uint32_t seed = atoi(argv[1]);

	Game::get()->run(argc, argv);

	return 0;
}