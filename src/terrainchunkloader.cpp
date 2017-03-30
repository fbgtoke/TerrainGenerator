#include "terrainchunkloader.hpp"

const char TerrainChunkLoader::SAVE_DIR[] = "data/";

unsigned int TerrainChunkLoader::coords2identifier(int x, int y) {
	// TODO
}

void TerrainChunkLoader::identifier2coords(int& x, int& y, unsigned int id) {
	// TODO
}

TerrainChunk* TerrainChunkLoader::generate(int offx, int offy, 
																						unsigned int seed) {
	
	TerrainChunkGenerator* generator(seed);
	TerrainChunk* chunk = generator->generate(offy, offx);
	delete generator;
}

bool TerrainChunkLoader::saveToDisk(TerrainChunk* chunk) {
	// TODO
}

bool TerrainChunkLoader::inDisk(TerrainChunk* chunk) {
	// TODO
}

TerrainChunk* TerrainChunkLoader::load(int offx, int offy, unsigned int seed) {
	if (!inDisk(id))
		return generate(id, seed);

	// TODO
}

void TerrainChunkLoader::unload(TerrainChunk* chunk) {
	if (!inDisk(chunk))
		saveToDisk(chunk);

	delete chunk;
}