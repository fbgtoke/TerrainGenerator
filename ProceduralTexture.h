#ifndef PROCEDURAL_TEXTURE_H
#define PROCEDURAL_TEXTURE_H

#include "utils.h"
#include "Simplex2d.h"

class ProceduralTexture {
public:
	ProceduralTexture();
	~ProceduralTexture();

	void generate(unsigned int width, unsigned int height, uint64_t seed);

	void setWrapS(GLint value);
	void setWrapT(GLint value);
	void setMinFilter(GLint value);
	void setMagFilter(GLint value);
	
	void use() const;
	
	unsigned int getWidth() const;
	unsigned int getHeight() const;

	GLuint getTexId() const;
	void setTexUnit(GLenum unit);

private:
	unsigned int mWidth  = 0;
	unsigned int mHeight = 0;

	unsigned char* mPixels;

	GLuint mTextureId = GL_INVALID_VALUE;
	GLenum mTextureUnit = GL_TEXTURE0;

	GLint wrapS = GL_REPEAT;
	GLint wrapT = GL_REPEAT;

	GLint minFilter = GL_LINEAR_MIPMAP_LINEAR;
	GLint magFilter = GL_LINEAR_MIPMAP_LINEAR;
};


#endif // PROCEDURAL_TEXTURE_H

