#include "terrain.hpp"

const unsigned int Terrain::DEFAULT_ORIGIN_X    = 0;
const unsigned int Terrain::DEFAULT_ORIGIN_Y    = 0;
const unsigned int Terrain::DEFAULT_CHUNK_COUNT = 2;

Terrain::Terrain(unsigned int s) : seed(s) {
	load(DEFAULT_ORIGIN_X, DEFAULT_ORIGIN_Y, DEFAULT_CHUNK_COUNT);
}

Terrain::~Terrain() {
	unloadAllChunks();
}


void Terrain::load(unsigned int x, unsigned int y, unsigned int nchunks) {
	unloadAllChunks();

	unsigned int i, j;
	for (i = y; i < nchunks; ++i) {
		for (j = x; j < nchunks; ++j) {
			int offset_x = j * TerrainChunk::getChunkWidth();
			int offset_y = i * TerrainChunk::getChunkHeight();

			std::cout << "Loading chunk (" << offset_x << "," << offset_y << ")";
			std::cout << " ... " << std::endl;

			TerrainChunk* chunk = TerrainChunkLoader::load(offset_x, offset_y, seed);
			chunks.insert(chunk);

			std::cout << "Chunk loaded" << std::endl;
		}
	}
}

void Terrain::unload(TerrainChunk* chunk) {
	TerrainChunkLoader::unload(chunk);
	chunks.erase(chunk);
}

void Terrain::unloadAllChunks() {
	std::cout << "Unloading all chunks" << std::endl;

	for (TerrainChunk* chunk : chunks)
		TerrainChunkLoader::unload(chunk);

	chunks.clear();

	std::cout << "All chunks unloaded" << std::endl;
}

unsigned int Terrain::getSeed() const { return seed; }

/*
void Terrain::draw(...) const {
	// TODO
}*/