#ifndef TERRAIN_H
#define TERRAIN_H

#include "utils.h"
#include "Chunk.h"
#include "ProceduralTexture.h"
#include "Texture.h"

class Terrain {
public:
  Terrain(uint64_t seed);
  ~Terrain();
  
  void init();
  void update(unsigned int deltaTime);
  void draw();

  void loadChunk(int x, int z);
  void unloadChunk(int x, int z);

  void unloadAllChunks();

private:
  uint64_t mSeed;
  std::list<Chunk*> mChunks;

  static const glm::vec3 lightDir;

  Texture mTexture;
  //ProceduralTexture mTexture;
};

#endif // TERRAIN_H