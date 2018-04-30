#include "Mesh.h"

Mesh::Mesh() {}

Mesh::~Mesh() {
  if (mVertices  != nullptr) free(mVertices);
  if (mNormals   != nullptr) free(mNormals);
  if (mIndices   != nullptr) free(mIndices);
  if (mTexcoords != nullptr) free(mTexcoords);

  freeVAO();
}

void Mesh::freeVAO() {
  if (mVAO != GL_INVALID_VALUE) {
    glDeleteBuffers(Mesh::NUM_VBOS, mVBOs);
    glDeleteVertexArrays(1, &mVAO);
  }
}

void Mesh::initVAO() {
  glGenVertexArrays(1, &mVAO);
  glBindVertexArray(mVAO);

  glGenBuffers(Mesh::NUM_VBOS, mVBOs);

  glBindBuffer(GL_ARRAY_BUFFER, mVBOs[Mesh::Vertices]);
  glBufferData(GL_ARRAY_BUFFER, mNumVertices * 3 * sizeof(float), &mVertices[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, mVBOs[Mesh::Normals]);
  glBufferData(GL_ARRAY_BUFFER, mNumNormals * 3 * sizeof(float), &mNormals[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVBOs[Mesh::Indices]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, mNumIndices * 3 * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, mVBOs[Mesh::Texcoords]);
  glBufferData(GL_ARRAY_BUFFER, mNumTexcoords * 2 * sizeof(float), &mTexcoords[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindVertexArray(0);
}

void Mesh::updateVAO() {
  glBindVertexArray(mVAO);

  glBindBuffer(GL_ARRAY_BUFFER, mVBOs[Mesh::Vertices]);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, mVBOs[Mesh::Normals]);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, mVBOs[Mesh::Texcoords]);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
  
  glBindVertexArray(0);
}

GLuint Mesh::getVAO() const { return mVAO; }

float* Mesh::vertices() { return mVertices; }
float* Mesh::normals() { return mNormals; }
float* Mesh::texcoords() { return mTexcoords; }