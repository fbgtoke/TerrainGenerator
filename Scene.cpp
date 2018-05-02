#include "Scene.h"

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
  mShaderProgram->setUniformMatrix4f("PM", PM);
  mShaderProgram->setUniformMatrix4f("VM", VM);
  mShaderProgram->setUniformMatrix4f("TG", TG);

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
  }
}

void Scene::keyReleased(unsigned char key) {}

void Scene::mouseMove(int x, int y) {}