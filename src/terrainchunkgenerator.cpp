#include "terrainchunkgenerator.hpp"

const float TerrainChunkGenerator::DEFAULT_SCALE              = 0.007f;
const unsigned int TerrainChunkGenerator::DEFAULT_OCTAVES     = 3;
const unsigned int TerrainChunkGenerator::DEFAULT_PERSISTANCE = 2;

TerrainChunkGenerator::TerrainChunkGenerator(unsigned int s) : seed(s) {
	set(DEFAULT_SCALE, DEFAULT_OCTAVES, DEFAULT_PERSISTANCE);
}

TerrainChunkGenerator::~TerrainChunkGenerator() {}

TerrainChunk* TerrainChunkGenerator::generate(int origin_x, int origin_y) {
	TerrainChunk* chunk = new TerrainChunk(origin_x, origin_y);
	SimplexGenerator* simplex = new SimplexGenerator(seed);

	for (int x = 0; x < origin_x; ++x) {
		for (int y = 0; y < origin_y; ++y) {
			float offx = x + origin_x;
			float offy = y + origin_y;
			
			float height   = 0.f;
			float frequency = 1.f;
			float amplitude = 1.f;
			float max       = 0.f;

			unsigned int n;
			for (n = 1; n <= octaves; ++n) {
				height += simplex->noise(offx * frequency, offy * frequency) * amplitude;

				max += amplitude;

				amplitude *= persistance;
				frequency *= 2;
			}

			chunk->setHeight(x, y, height/max);
		}
	}

	delete simplex;
	return chunk;
}

void TerrainChunkGenerator::setScale(float s) { scale = s; }
void TerrainChunkGenerator::setOctaves(unsigned int o) { octaves = o; }
void TerrainChunkGenerator::setPersistance(unsigned int p) { persistance = p; }
void TerrainChunkGenerator::set(float s, unsigned int o, unsigned int p) {
	setScale(s);
	setOctaves(o);
	setPersistance(p);
}