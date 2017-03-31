#include "utils.hpp"
#include "terrain.hpp"

void usage() {
	std::cout << "Usage: main SEED" << std::endl;

	exit(0);
}

int main(int argc, char** argv) {
	if (argc != 2)
		usage();

	unsigned int seed = atoi(argv[1]);

	std::cout << "Seed: " << seed << std::endl;
	std::cout << "Creating terrain" << std::endl;

	Terrain terrain(seed);

	std::cout << "Generated" << std::endl;

	while (1);
}