#ifndef CHUNK_H
#define CHUNK_H

#include "utils.h"
#include "Texture.h"
#include "Simplex2d.h"
#include "Mesh.h"

class Chunk : public Mesh {
public:
  Chunk(int x, int z, const uint64_t& seed);
  ~Chunk();

  glm::ivec2 getOffset() const;

  void generate();

  void draw();

  bool outOfBounds(int x, int z) const;
  glm::vec3 getVertex(int x, int z) const;

private:
  static const unsigned int kChunkWidth;
  static const unsigned int kChunkDepth;
  static const float kTileSize;

  static const float kSimplexFrequency;
  static const float kSimplexMin;
  static const float kSimplexMax;

  static const unsigned int kFractalOctaves;
  static const float kFractalLacunarity;
  static const float kFractalGain;

  const uint64_t& mSeed;
  int mOffsetX;
  int mOffsetZ;

  void calculateVertices();
  void calculateNormals();
  void calculateIndices();
  void calculateTexcoords();
};

#endif // CHUNK_H