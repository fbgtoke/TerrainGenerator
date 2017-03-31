#include "terrain.hpp"

const unsigned int Terrain::DEFAULT_ORIGIN_X    = 0;
const unsigned int Terrain::DEFAULT_ORIGIN_Y    = 0;
const unsigned int Terrain::DEFAULT_CHUNK_COUNT = 10;

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

			TerrainChunk* chunk = TerrainChunkLoader::load(offset_x, offset_y, seed);
			chunks.insert(chunk);
		}
	}
}

void Terrain::unload(TerrainChunk* chunk) {
	TerrainChunkLoader::unload(chunk);
	chunks.erase(chunk);
}

void Terrain::unloadAllChunks() {
	for (TerrainChunk* chunk : chunks)
		TerrainChunkLoader::unload(chunk);

	chunks.clear();
}

unsigned int Terrain::getSeed() const { return seed; }

/*
void Terrain::draw(...) const {
	// TODO
}*/