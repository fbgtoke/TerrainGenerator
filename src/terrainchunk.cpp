#include "terrainchunk.hpp"

const int TerrainChunk::CHUNK_WIDTH  = 16;
const int TerrainChunk::CHUNK_HEIGHT = 16;

TerrainChunk::TerrainChunk(int offx, int offy) : offset_x(offx), offset_y(offy) {
	height   = matrix_t(CHUNK_HEIGHT, std::vector<float>(CHUNK_WIDTH, 0.f));
	moisture = matrix_t(CHUNK_HEIGHT, std::vector<float>(CHUNK_WIDTH, 0.f));
};

TerrainChunk::~TerrainChunk() {
	height.clear();
	moisture.clear();
}

int TerrainChunk::getOffsetX() const { return offset_x; }
int TerrainChunk::getOffsetY() const { return offset_y; }

int TerrainChunk::getChunkWidth()  { return CHUNK_WIDTH;  }
int TerrainChunk::getChunkHeight() { return CHUNK_HEIGHT; }

float TerrainChunk::getHeight(int x, int y) const {
	return height[y][x];
}

float TerrainChunk::getMoisture(int x, int y) const {
	return moisture[y][x];
}

void TerrainChunk::setHeight(int x, int y, float h) {
	height[y][x] = h;
}

void TerrainChunk::setMoisture(int x, int y, float m) {
	moisture[y][x] = m;
}

/*void TerrainChunk::draw(...) const {
	// TODO
}*/