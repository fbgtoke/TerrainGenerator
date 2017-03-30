#ifndef SIMPLEXGENERATOR_HPP
#define SIMPLEXGENERATOR_HPP

#include "utils.hpp"

class SimplexGenerator {
private:
	static const int grad3[][3];
	static const std::vector<short> p;

	const unsigned int seed;
	std::vector<short> perm;

	static int fastFloor(float x);
	static float dot(int g[3], float x, float y);

public:
	SimplexGenerator(unsigned int s);
	~SimplexGenerator();

	float noise(float x, float y) const;
};

#endif