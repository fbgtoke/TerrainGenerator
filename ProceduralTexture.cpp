#include "ProceduralTexture.h"

ProceduralTexture::ProceduralTexture() {}

ProceduralTexture::~ProceduralTexture() {
	if (mTextureId != GL_INVALID_VALUE)
		glDeleteTextures(1, &mTextureId);

	if (mPixels != nullptr) free(mPixels);
}

void ProceduralTexture::generate(unsigned int width, unsigned int height, uint64_t seed) {
	mWidth  = width;
	mHeight = height;

	mPixels = (unsigned char*) malloc(mWidth * mHeight * 3 * sizeof(unsigned char));

	Simplex2d simplex(seed, 1.f/8.f, 16.f, 255.f);

	unsigned int i, j;
	for (i = 0; i < mHeight; ++i) {
		for (j = 0; j < mWidth; ++j) {
			mPixels[i*mWidth*3 + j*3 + 0] = (unsigned int)simplex.getValue(j, i)*0.25f;
			mPixels[i*mWidth*3 + j*3 + 1] = (unsigned int)simplex.getValue(j, i);
			mPixels[i*mWidth*3 + j*3 + 2] = (unsigned int)simplex.getValue(j, i)*0.25f;
		}
	}

	glGenTextures(1, &mTextureId);
	glBindTexture(GL_TEXTURE_2D, mTextureId);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, mWidth, mHeight);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, mPixels);
}

void ProceduralTexture::setWrapS(GLint value) { wrapS = value; }
void ProceduralTexture::setWrapT(GLint value) { wrapT = value; }
void ProceduralTexture::setMinFilter(GLint value) { minFilter = value; }
void ProceduralTexture::setMagFilter(GLint value) { magFilter = value; }

void ProceduralTexture::use() const {
	glActiveTexture(mTextureUnit);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

unsigned int ProceduralTexture::getWidth()  const { return mWidth;  }
unsigned int ProceduralTexture::getHeight() const { return mHeight; }

GLuint ProceduralTexture::getTexId() const { return mTextureId; }
void ProceduralTexture::setTexUnit(GLenum unit) { mTextureUnit = unit; }