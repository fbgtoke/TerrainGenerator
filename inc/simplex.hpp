#ifndef SIMPLEX_HPP
#define SIMPLEX_HPP

#include "utils.hpp"

class Simplex {
private:
	static const uint8_t p[256];
	static const int g[12][3];
	const uint32_t seed;

	static inline uint8_t hash(int x, int y, uint32_t seed);
	static inline int fastfloor(float x);
	static inline float dot(int x0, int y0, float x1, float y1);

public:
	Simplex(uint32_t s);

	float noise(float x, float y);

	float fractal(float x, float y, float pers, float freq, int oct, float a);
};

#endif