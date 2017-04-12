#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "gameobject.hpp"
#include "terrainchunk.hpp"

class Terrain : public GameObject {
private:
	static const unsigned int CHUNK_COUNT;

	uint32_t seed;
	std::set<TerrainChunk*> chunks;

public:
	Terrain(uint32_t s);
	~Terrain();

	void event(unsigned char key, int x, int y) final;
	void update() final;
	void draw() final;
};

#endif