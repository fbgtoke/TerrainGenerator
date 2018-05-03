#ifndef SCENE_H
#define SCENE_H

#include "utils.h"
#include "ShaderProgram.h"
#include "Terrain.h"
#include "Camera.h"

class Scene {
public:
  Scene();
  ~Scene();

  void init();
  bool update(unsigned int deltaTime);
  void draw();

  void keyPressed(unsigned char key);
  void keyReleased(unsigned char key);

  void mouseMove(int x, int y);

private:
  static const glm::vec3 lightDir;

  static const float VEL;
  static const float ALPHA;

  bool mRunning = false;

  Terrain* mTerrain = nullptr;
  ShaderProgram* mShaderProgram = nullptr;

  Camera mCamera;
  glm::mat4 PM, VM, TG;
};

#endif // SCENE_H