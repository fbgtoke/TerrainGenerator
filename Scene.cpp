#include "Scene.h"

const glm::vec3 Scene::lightDir = glm::vec3(1.0f, -1.0f, 0.5f);

const float Scene::VEL   = 0.5f;
const float Scene::ALPHA = M_PI * 1.f/8.f;

Scene::Scene() {}

Scene::~Scene() {
  if (mTerrain != nullptr)
    delete mTerrain;

  if (mShaderProgram != nullptr)
    delete mShaderProgram;
}

void Scene::init() {
  mRunning = true;
  mShaderProgram = ShaderProgram::loadFromFile("simple");

  uint64_t seed = 0x0000000000000002;
  mTerrain = new Terrain(seed);
  mTerrain->init();
}

bool Scene::update(unsigned int deltaTime) {
  PM = mCamera.getPerspectiveMatrix();
  VM = mCamera.getViewMatrix();
  TG = glm::mat4(1.f);

  return mRunning;
}

void Scene::draw() {
  mShaderProgram->use();
  glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(PM));
  glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(VM));

  glUniform3f(4, lightDir.x, lightDir.y, lightDir.z);

  if (mTerrain != nullptr)
    mTerrain->draw();
}

void Scene::keyPressed(unsigned char key) {
  switch(key) {
  case 'a':
  case 'A':
    mCamera.move({+VEL, 0.f, 0.f});
    break;
  case 'd':
  case 'D':
    mCamera.move({-VEL, 0.f, 0.f});
    break;
  case 'w':
  case 'W':
    mCamera.move({0.f, 0.f, +VEL});
    break;
  case 's':
  case 'S':
    mCamera.move({0.f, 0.f, -VEL});
    break;
  case 'i':
  case 'I':
    mCamera.move({0.f, +VEL, 0.f});
    break;
  case 'k':
  case 'K':
    mCamera.move({0.f, -VEL, 0.f});
    break;
  case 'q':
  case 'Q':
    mRunning = false;
    break;
  case '4': mTerrain->rotate(glm::vec3(0.f, -ALPHA, 0.f)); break;
  case '6': mTerrain->rotate(glm::vec3(0.f, +ALPHA, 0.f)); break;
  case '8': mTerrain->rotate(glm::vec3(-ALPHA, 0.f, 0.f)); break;
  case '2': mTerrain->rotate(glm::vec3(+ALPHA, 0.f, 0.f)); break;
  }
}

void Scene::keyReleased(unsigned char key) {}

void Scene::mouseMove(int x, int y) {}