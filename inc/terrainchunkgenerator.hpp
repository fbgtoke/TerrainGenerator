#ifndef TERRAINCHUNKGENERATOR_HPP
#define TERRAINCHUNKGENERATOR_HPP

#include "utils.hpp"
#include "terrainchunk.hpp"
#include "simplexgenerator.hpp"

class TerrainChunkGenerator {
private:
	const unsigned int seed;

	static const float DEFAULT_SCALE;
	static const unsigned int DEFAULT_OCTAVES;
	static const unsigned int DEFAULT_PERSISTANCE;

	float scale;
	unsigned int octaves;
	unsigned int persistance;

public:
	TerrainChunkGenerator(unsigned int s);
	~TerrainChunkGenerator();

	TerrainChunk* generate(int origin_x, int origin_y);

	void setScale(float s);
	void setOctaves(unsigned int o);
	void setPersistance(unsigned int p);
	void set(float s, unsigned int o, unsigned int p);
};

#endif