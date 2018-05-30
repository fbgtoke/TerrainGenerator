#include "Camera.h"

Camera::Camera() {
  setFOV(M_PI * 0.25f);
  setAspectRatio(1.f);
  setZs(0.1f, 100.f);
  
  setOBS({20.f, 10.f, -10.f});
  setVRP({20.f,  0.f,  10.f});
  setUP ({ 0.f,  1.f,   0.f});
}

Camera::~Camera() {}

void Camera::setFOV(float fov) { FOV = fov; }
void Camera::setAspectRatio(float ratio) { mRatio = ratio; }
void Camera::setZs(float znear, float zfar) { mZnear = znear; mZfar = zfar; }
void Camera::setPerspective(float fov, float ratio, float znear, float zfar) {
  setFOV(fov);
  setAspectRatio(ratio);
  setZs(znear, zfar);
}

void Camera::setOBS(const glm::vec3& obs) { OBS = obs; }
void Camera::setVRP(const glm::vec3& vrp) { VRP = vrp; }
void Camera::setUP(const glm::vec3& up) { UP = up; }
void Camera::setView(const glm::vec3& obs, const glm::vec3& vrp, const glm::vec3& up) {
  setOBS(obs);
  setVRP(vrp);
  setUP(up);
}

void Camera::move(const glm::vec3& direction, bool moveVRP) {
  OBS += direction;
  if (moveVRP) VRP += direction;
}

void Camera::setDirection(const glm::vec3& direction) { VRP = OBS + direction; }

glm::mat4 Camera::getPerspectiveMatrix() const { return glm::perspective(FOV, mRatio, mZnear, mZfar); }
glm::mat4 Camera::getViewMatrix() const { return glm::lookAt(OBS, VRP, UP); }