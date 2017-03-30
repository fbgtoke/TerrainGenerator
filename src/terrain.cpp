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
	unload();

	for (int i = y; i < nchunks; ++i) {
		for (int j = x; j < nchunks; ++j) {
			int offset_x = j * TerrainChunk::getChunkWidth();
			int offset_y = i * TerrainChunk::getChunkHeight();

			TerrainChunk* chunk = TerrainChunkLoader::load(offset_x, offset_y);
			chunks.push_back(chunk);
		}
	}
}

void Terrain::unload(TerrainChunk* chunk) {
	TerrainChunkLoader::uload(chunk);
	chunks.remove(chunk);
}

void Terrain::unloadAllChunks() {
	for (TerrainChunk* chunk : chunks)
		TerrainChunkLoader::uload(chunk);

	chunks.clear();
}

unsigned int Terrain::getSeed() const { return seed; }

void Terrain::draw(...) const {
	// TODO
}