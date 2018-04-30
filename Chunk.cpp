#include "Chunk.h"

const unsigned int Chunk::kChunkWidth = 64;
const unsigned int Chunk::kChunkDepth = 64;
const float Chunk::kTileSize = 0.25f;

const float Chunk::kSimplexFrequency = 1.f/64.f;
const float Chunk::kSimplexMin = 0.f;
const float Chunk::kSimplexMax = 5.f;

Chunk::Chunk(int x, int z, const uint64_t& seed) : mSeed(seed), mOffsetX(x), mOffsetZ(z) {}

Chunk::~Chunk() {}

glm::ivec2 Chunk::getOffset() const { return {mOffsetX, mOffsetZ}; }

void Chunk::generate() {
  calculateVertices();
  calculateNormals();
  calculateIndices();
  calculateTexcoords();

  initVAO();
}

void Chunk::draw() {
  if (mVertices == nullptr) return;

  glBindVertexArray(mVAO);
  glDrawElements(GL_TRIANGLES, mNumIndices * 3, GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);
}

bool Chunk::outOfBounds(int x, int z) const {
  return
    x < 0 || x >= (int)kChunkWidth ||
    z < 0 || z >= (int)kChunkDepth;
}

glm::vec3 Chunk::getVertex(int x, int z) const {
  unsigned int index;
  glm::vec3 vertex(0.f);

  if (outOfBounds(x, z)) {
    Simplex2d simplex(mSeed, kSimplexFrequency, kSimplexMin, kSimplexMax);

    float coordX = (int)(x) + mOffsetX * (int)kChunkWidth;
    float coordZ = (int)(z) + mOffsetZ * (int)kChunkDepth;

    vertex.x = ((int)(x) + mOffsetX * (int)kChunkWidth) * kTileSize;
    vertex.y = simplex.getValue(coordX, coordZ);
    vertex.z = ((int)(z) + mOffsetZ * (int)kChunkDepth) * kTileSize;
  } else {
    index = (unsigned int)z * kChunkWidth * 3 + (unsigned int)x * 3;
    
    vertex.x = mVertices[index + 0];
    vertex.y = mVertices[index + 1];
    vertex.z = mVertices[index + 2];
  }

  return vertex;
}

void Chunk::calculateVertices() {
  unsigned int i, j;
  Simplex2d simplex(mSeed, kSimplexFrequency, kSimplexMin, kSimplexMax);

  mNumVertices = kChunkDepth * kChunkWidth;
  mVertices = (float*) malloc(mNumVertices * 3 * sizeof(float));

  for (i = 0; i < kChunkDepth; ++i) {
    for (j = 0; j < kChunkWidth; ++j) {
      float coordX = (int)(j) + mOffsetX * (int)kChunkWidth;
      float coordZ = (int)(i) + mOffsetZ * (int)kChunkDepth;

      mVertices[i*kChunkWidth*3 + j*3 + 0] = ((int)(j) + mOffsetX * (int)kChunkWidth) * kTileSize;
      //mVertices[i*kChunkWidth*3 + j*3 + 1] = simplex.getValue(coordX, coordZ);
      mVertices[i*kChunkWidth*3 + j*3 + 1] = simplex.fractal(coordX, coordZ, 4, 0.2f, 0.5f);
      mVertices[i*kChunkWidth*3 + j*3 + 2] = ((int)(i) + mOffsetZ * (int)kChunkDepth) * kTileSize;
    }
  }
}

void Chunk::calculateNormals() {
  unsigned int i, j;
  glm::vec3 x0, x1;
  glm::vec3 z0, z1;
  glm::vec3 normal;

  mNumNormals = kChunkWidth * kChunkDepth;
  mNormals = (float*) malloc(mNumNormals * 3 * sizeof(float));

  for (i = 0; i < kChunkDepth; ++i) {
    for (j = 0; j < kChunkWidth; ++j) {
      x0 = getVertex((int)j - 1, (int)i);
      x1 = getVertex((int)j + 1, (int)i);

      z0 = getVertex((int)j, (int)i - 1);
      z1 = getVertex((int)j, (int)i + 1);

      normal = glm::cross(glm::normalize(z1-z0), glm::normalize(x1-x0));
      
      mNormals[i*kChunkWidth*3 + j*3 + 0] = normal.x;
      mNormals[i*kChunkWidth*3 + j*3 + 1] = normal.y;
      mNormals[i*kChunkWidth*3 + j*3 + 2] = normal.z;
    }
  }
}

void Chunk::calculateIndices() {
  unsigned int i, j;

  mNumIndices = (kChunkDepth - 1) * (kChunkWidth - 1) * 2;
  mIndices = (unsigned int*) malloc(mNumIndices * 3 * sizeof(unsigned int));

  for (i = 0; i < kChunkDepth - 1; ++i) {
    for (j = 0; j < kChunkWidth - 1; ++j) {
      mIndices[i*(kChunkWidth-1)*6 + j*6 + 0] = (i + 0) * kChunkWidth + (j + 0);
      mIndices[i*(kChunkWidth-1)*6 + j*6 + 1] = (i + 0) * kChunkWidth + (j + 1);
      mIndices[i*(kChunkWidth-1)*6 + j*6 + 2] = (i + 1) * kChunkWidth + (j + 1);

      mIndices[i*(kChunkWidth-1)*6 + j*6 + 3] = (i + 0) * kChunkWidth + (j + 0);
      mIndices[i*(kChunkWidth-1)*6 + j*6 + 4] = (i + 1) * kChunkWidth + (j + 1);
      mIndices[i*(kChunkWidth-1)*6 + j*6 + 5] = (i + 1) * kChunkWidth + (j + 0);
    }
  }
}

void Chunk::calculateTexcoords() {
  unsigned int i, j;
  glm::vec2 texcoord;

  mNumTexcoords = kChunkDepth * kChunkWidth;
  mTexcoords = (float*) malloc(mNumTexcoords * 2 * sizeof(float));

  for (i = 0; i < kChunkDepth; ++i) {
    for (j = 0; j < kChunkWidth; ++j) {
      mTexcoords[i*kChunkWidth*2 + j*2 + 0] = ((float)kChunkWidth / (float)512)  * (float)j;
      mTexcoords[i*kChunkWidth*2 + j*2 + 1] = ((float)kChunkDepth / (float)512) * (float)i;
    }
  }
}