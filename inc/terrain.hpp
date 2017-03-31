#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "utils.hpp"
#include "terrainchunk.hpp"
#include "terrainchunkloader.hpp"

class Terrain {
private:
	const unsigned int seed;

	static const unsigned int DEFAULT_ORIGIN_X;
	static const unsigned int DEFAULT_ORIGIN_Y;
	static const unsigned int DEFAULT_CHUNK_COUNT;

	std::set<TerrainChunk*> chunks;

public:
	Terrain(unsigned int s);
	~Terrain();

	void load(unsigned int x, unsigned int y, unsigned int nchunks);
	void unload(TerrainChunk* chunk);
	void unloadAllChunks();

	unsigned int getSeed() const;

	//void draw(...) const;
};

#endif