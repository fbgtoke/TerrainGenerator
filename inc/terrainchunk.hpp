#ifndef TERRAINCHUNK_HPP
#define TERRAINCHUNK_HPP

#include "gameobject.hpp"
#include "simplex.hpp"

class TerrainChunk : public GameObject {
private:
	int offset_x;
	int offset_z;

	uint32_t seed;
	static const float PERSISTANCE;
	static const float FREQUENCY;
	static const int OCTAVES;
	static const float AMPLITUDE;

	GLuint VAO;
	GLuint VBO_vertices;
	GLuint VBO_colors;
	GLuint VBO_indexes;

	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indexes;

	std::vector<glm::vec3> colors;

	void generate();
	void initIndexes();
	
	void freeVAO();

public:
	static const unsigned int CHUNK_SIZE;

	TerrainChunk(uint32_t s, int offx, int offz);
	~TerrainChunk();

	void initVAO();

	void event(unsigned char key, int x, int y) final;
	void update() final;
	void draw() final;
};

#endif