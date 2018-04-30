#ifndef _MESH_INCLUDE
#define _MESH_INCLUDE

#include "utils.h"

class Mesh {
public:
	Mesh();
	~Mesh();

  void initVAO();
  void updateVAO();
  void freeVAO();
  GLuint getVAO() const;

  void setVertices(float* vertices, unsigned int nelem);
  void setNormals(float* normals, unsigned int nelem);
  void setTexCoords(float* texcoords, unsigned int nelem);

  float* vertices();
  float* normals();
  float* texcoords();

  unsigned int verticesSize() const;
  unsigned int normalsSize() const;
  unsigned int texcoordsSize() const;

  unsigned int numVertices() const;

  void getMinMaxVertices(glm::vec3& min, glm::vec3& max) const;

  glm::vec3 center() const;
  glm::vec3 size() const;

protected:
  enum VBO_TYPES : unsigned int {
    Vertices,
    Normals,
    Indices,
    Texcoords,
    NUM_VBOS
  };

  GLuint mVAO = GL_INVALID_VALUE;
  GLuint mVBOs[NUM_VBOS];

  float* mVertices = nullptr;
  unsigned int mNumVertices = 0;

  float* mNormals = nullptr;
  unsigned int mNumNormals = 0;

  unsigned int* mIndices = nullptr;
  unsigned int mNumIndices = 0;

  float* mTexcoords = nullptr;
  unsigned int mNumTexcoords = 0;

  glm::vec3 min, max;

  void allocateVertices(unsigned int nelem);
  void allocateNormals(unsigned int nelem);
  void allocateTexCoords(unsigned int nelem);
};

#endif // _MESH_INCLUDE