#ifndef TERRAINCHUNK_HPP
#define TERRAINCHUNK_HPP

#include "utils.hpp"

class TerrainChunk {
private:
	static const int CHUNK_WIDTH;
	static const int CHUNK_HEIGHT;

	int offset_x;
	int offset_y;

	matrix_t height;
	matrix_t moisture;

public:
	TerrainChunk(int offx, int offy);
	~TerrainChunk();

	static int getChunkWidth();
	static int getChunkHeight();

	int getOffsetX() const;
	int getOffsetY() const;

	float getHeight(int x, int y) const;
	float getMoisture(int x, int y) const;

	void setHeight(int x, int y, float h);
	void setMoisture(int x, int y, float m);

	//void draw(...) const;
};

#endif