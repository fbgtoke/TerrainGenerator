#include "terrain.hpp"

const unsigned int TerrainChunk::CHUNK_SIZE = 480;

const float TerrainChunk::PERSISTANCE = 0.8f;
const float TerrainChunk::FREQUENCY   = 0.02f;
const int   TerrainChunk::OCTAVES     = 8;
const float TerrainChunk::AMPLITUDE   = 2.5f;

TerrainChunk::TerrainChunk(uint32_t s, int offx, int offz) {
	seed = s;
	offset_x = offx;
	offset_z = offz;

	initIndexes();
	generate();
	initVAO();
}

TerrainChunk::~TerrainChunk() {
	vertices.clear();
	colors.clear();
	indexes.clear();
	freeVAO();
}

void TerrainChunk::initIndexes() {
	GLuint restart_index = CHUNK_SIZE * CHUNK_SIZE;

	unsigned int z, x;
	for (z = 0; z < CHUNK_SIZE; ++z) {
		for (x = 0; x < CHUNK_SIZE; ++x) {
			if (z < CHUNK_SIZE - 1) {
				indexes.push_back(z * CHUNK_SIZE + x);
				indexes.push_back((z + 1) * CHUNK_SIZE + x);
			}
		}
		indexes.push_back(restart_index);
	}
}

void TerrainChunk::initVAO() {
	GLsizeiptr vertices_size = vertices.size() * sizeof(glm::vec3);
	GLsizeiptr colors_size = colors.size() * sizeof(glm::vec3);
	GLsizeiptr indexes_size  = indexes.size()  * sizeof(unsigned int);
	GLuint restart_index = CHUNK_SIZE * CHUNK_SIZE;	

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
	glBufferData(GL_ARRAY_BUFFER, vertices_size, &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  	glEnableVertexAttribArray(0);

  	glGenBuffers(1, &VBO_colors);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_colors);
	glBufferData(GL_ARRAY_BUFFER, colors_size, &colors[0], GL_STATIC_DRAW);

	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
  	glEnableVertexAttribArray(1);

  	glGenBuffers(1, &VBO_indexes);
  	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_indexes);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes_size, &indexes[0], GL_STATIC_DRAW);

	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(restart_index);
	glBindVertexArray(0);
}

void TerrainChunk::freeVAO() {
	glDeleteBuffers(1, &VBO_vertices);
	glDeleteBuffers(1, &VBO_colors);
	glDeleteBuffers(1, &VBO_indexes);
	glDeleteVertexArrays(1, &VAO);
}

void TerrainChunk::generate() {
	Simplex* simplex = new Simplex(seed);

	// Create vertices
	unsigned int z, x;
	for (z = 0; z < CHUNK_SIZE; ++z) {
		for (x = 0; x < CHUNK_SIZE; ++x) {
			float real_x = x + (offset_x * (CHUNK_SIZE - 1));
			float real_z = z + (offset_z * (CHUNK_SIZE - 1));

			float value = simplex->fractal(
				real_x, real_z, PERSISTANCE, FREQUENCY, OCTAVES, AMPLITUDE
			);

			vertices.push_back({ real_x, value, real_z });

			float intensity = value / AMPLITUDE;
			glm::vec3 color = glm::vec3(0.f, 1.f, 0.f);

			colors.push_back(intensity * color);
		}
	}

	delete simplex;
}

void TerrainChunk::event(unsigned char key, int x, int y) {}
void TerrainChunk::update() {}

void TerrainChunk::draw() {
	glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLE_STRIP, indexes.size(), GL_UNSIGNED_INT, 0);
}