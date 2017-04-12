#include "terrain.hpp"

const unsigned int Terrain::CHUNK_COUNT = 2;

Terrain::Terrain(uint32_t s) : seed(s) {
	seed = s;

	unsigned int size = CHUNK_COUNT * CHUNK_COUNT;

	for (unsigned int i = 0; i < size; ++i) {
		int x = i % CHUNK_COUNT;
		int z = i / CHUNK_COUNT;

		TerrainChunk* chunk = new TerrainChunk(seed, x, z);
		chunks.insert(chunk);
	}
}

Terrain::~Terrain() {
	for (TerrainChunk* chunk : chunks)
		delete chunk;
	chunks.clear();
}

void Terrain::event(unsigned char key, int x, int y) {}
void Terrain::update() {}

void Terrain::draw() {
	for (TerrainChunk* chunk : chunks)
		chunk->draw();
}