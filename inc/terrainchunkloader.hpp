#ifndef TERRAINCHUNKLOADER_HPP
#define TERRAINCHUNKLOADER_HPP

#include "utils.hpp"
#include "terrainchunk.hpp"
#include "terrainchunkgenerator.hpp"

class TerrainChunkLoader {
private:
	static const char SAVE_DIR[];

	static unsigned int coords2identifier(int x, int y);
	static void identifier2coords(int& x, int& y, unsigned int id);

	static TerrainChunk* generate(int offx, int offy, unsigned int seed);

	static bool saveToDisk(TerrainChunk* chunk);
	static bool inDisk(TerrainChunk* chunk);

public:
	static TerrainChunk* load(int offx, int offy, unsigned int seed);
	static void unload(TerrainChunk* chunk);
};

#endif