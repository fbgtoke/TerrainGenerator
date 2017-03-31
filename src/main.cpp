#include "utils.hpp"
#include "terrain.hpp"

void usage() {
	std::cout << "Usage: main SEED" << std::endl;

	exit(0);
}

int main(int argc, char** argv) {
	if (argc != 2)
		usage();

	int seed = atoi(argv[1]);
	Terrain terrain(seed);

	std::cout << "Generated" << std::endl;

	while (1);
}