#include "terrainchunkloader.hpp"

const char TerrainChunkLoader::SAVE_DIR[] = "data/";

unsigned int TerrainChunkLoader::getIdentifier(TerrainChunk* chunk) {
	int offx = chunk->getOffsetX();
	int offy = chunk->getOffsetY();

	unsigned int id = coords2identifier(offx, offy);
	return id;
}

unsigned int TerrainChunkLoader::coords2identifier(int x, int y) {
	// TODO
	return 0;
}

void TerrainChunkLoader::identifier2coords(int& x, int& y, unsigned int id) {
	// TODO
}

TerrainChunk* TerrainChunkLoader::generate(int offx, int offy, 
																						unsigned int seed) {
	
	std::cout << "Generating chunk" << std::endl;

	TerrainChunkGenerator* generator = new TerrainChunkGenerator(seed);
	TerrainChunk* chunk = generator->generate(offy, offx);
	delete generator;

	std::cout << "Generated" << std::endl;
	
	return chunk;
}

bool TerrainChunkLoader::saveToDisk(TerrainChunk* chunk) {
	// TODO
	return false;
}

bool TerrainChunkLoader::inDisk(unsigned int id) {
	// TODO
	return false;
}

TerrainChunk* TerrainChunkLoader::load(int offx, int offy, unsigned int seed) {
	unsigned int id = coords2identifier(offx, offy);

	if (!inDisk(id))
		return generate(offx, offy, seed);

	// TODO
	return NULL;
}

void TerrainChunkLoader::unload(TerrainChunk* chunk) {
	unsigned int id = getIdentifier(chunk);

	if (!inDisk(id))
		saveToDisk(chunk);

	delete chunk;
}