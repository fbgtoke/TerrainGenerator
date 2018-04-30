#ifndef UTILS_H
#define UTILS_H

/* GLM */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* GLUT */
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

/* STD utils */
#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>

/* STD containers */
#include <vector>
#include <list>

#define TIME_PER_FRAME 1000.f / 60.f // Approx. 60 fps

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 800

/* Useful macros */
#define randomFloat(min, max) \
  (min + static_cast <float> (rand())/(static_cast <float> (RAND_MAX/(max-min))))

#define randomInt(min, max) \
  (min + static_cast <int> (rand())/(static_cast <int> (RAND_MAX/(max-min))))

#define CHECK_GL_ERROR() {                        \
  GLuint error;                                   \
  while ((error = glGetError()) != GL_NO_ERROR) { \
    std::cerr << "OpenGL Error in "               \
              << __FILE__ << ":"                  \
              << __LINE__ << " => "               \
              << "0x" << std::hex                 \
              << error << std::endl;              \
  }                                               \
}

#endif
