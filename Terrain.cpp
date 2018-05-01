#include "Terrain.h"

const glm::vec3 Terrain::lightDir = glm::vec3(1.0f, -1.0f, 0.5f);

Terrain::Terrain(uint64_t seed) : mSeed(seed) {}

Terrain::~Terrain() {
  unloadAllChunks();
}

void Terrain::init() {
  int i, j;
  for (i = -10; i < 10; ++i) {
    for (j = -10; j < 10; ++j) {
      loadChunk(j, i);
    }
  }

  //loadChunk(0, 0);

  //mTexture.generate(256, 256, mSeed);
  mTexture.loadFromFile("textures/grass.jpg", TEXTURE_PIXEL_FORMAT_RGB);
  std::cout << "Done" << std::endl;
}

void Terrain::update(unsigned int deltaTime) {}

void Terrain::draw() {
  glUniform3f(0, Terrain::lightDir.x, Terrain::lightDir.y, Terrain::lightDir.z);
  mTexture.use();

  for (Chunk* chunk : mChunks)
    chunk->draw();
}

void Terrain::loadChunk(int x, int z) {
  Chunk* chunk = new Chunk(x, z, mSeed);
  chunk->generate();

  mChunks.push_back(chunk);
}

void Terrain::unloadChunk(int x, int z) {
  std::list<Chunk*>::iterator it = mChunks.begin();

  while (it != mChunks.end()) {
    if ((*it)->getOffset() == glm::ivec2(x, z)) {
      delete (*it);
      mChunks.erase(it++);
      return;
    } else {
      it++;
    }
  }

}

void Terrain::unloadAllChunks() {
  for (Chunk* chunk : mChunks)
    delete chunk;
  mChunks.clear();
}