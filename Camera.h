#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

class Camera {
public:
  Camera();
  ~Camera();

  void setFOV(float fov);
  void setAspectRatio(float ratio);
  void setZs(float znear, float zfar);
  void setPerspective(float fov, float ratio, float znear, float zfar);

  void setOBS(const glm::vec3& obs);
  void setVRP(const glm::vec3& vrp);
  void setUP(const glm::vec3& up);
  void setView(const glm::vec3& obs, const glm::vec3& vrp, const glm::vec3& up);

  void move(const glm::vec3& direction, bool moveVRP = true);
  void setDirection(const glm::vec3& direction);

  glm::mat4 getPerspectiveMatrix() const;
  glm::mat4 getViewMatrix() const;

private:
  float FOV, mRatio, mZnear, mZfar;
  glm::vec3 OBS, VRP, UP;
};

#endif // CAMERA_H