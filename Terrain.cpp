#include "Terrain.h"

Terrain::Terrain(uint64_t seed) : mSeed(seed) {}

Terrain::~Terrain() {
  unloadAllChunks();
}

void Terrain::init() {
  int i, j;
  for (i = 0; i < 30; i += 1) {
    for (j = 0; j < 35; j += 1) {
      loadChunk(j, i);
    }
  }

  //loadChunk(0, 0);
  //loadChunk(1, 0);
  //loadChunk(0, 1);
  //loadChunk(1, 1);

  //mTexture.generate(256, 256, mSeed);
  mTexture.loadFromFile("textures/grass.jpg", TEXTURE_PIXEL_FORMAT_RGB);
  std::cout << "Done" << std::endl;
}

void Terrain::update(unsigned int deltaTime) {}

void Terrain::draw() {
  mTexture.use();

  glm::mat4 TG;
  TG = glm::mat4(1.f);
  TG = glm::rotate(TG, mRotation.x, glm::vec3(1.f, 0.f, 0.f));
  TG = glm::rotate(TG, mRotation.y, glm::vec3(0.f, 1.f, 0.f));
  TG = glm::rotate(TG, mRotation.z, glm::vec3(0.f, 0.f, 1.f));
  glUniformMatrix4fv(3, 1, GL_FALSE, glm::value_ptr(TG));

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

void Terrain::rotate(const glm::vec3& rotation) { mRotation += rotation; }