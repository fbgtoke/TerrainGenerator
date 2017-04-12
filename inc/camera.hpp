#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "gameobject.hpp"

class Camera : public GameObject {
private:
	static const float TRANSLATION_VEL;
	static const float ROTATION_ANGLE;
	static const float PITCH_LIMIT;

	float pitch;
	float yaw;
	glm::vec3 position;

	static const float ZNEAR;
	static const float ZFAR;

	float width;
	float height;
	float fov;
	float ratio;

	void lock();
	void move(const glm::vec3& direction);
	glm::vec3 getVRP();

public:
	Camera(int w, int h);
	~Camera();

	void event(unsigned char key, int x, int y) final;
	void resize(int w, int h);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectMatrix();

	void setPosition(const glm::vec3& p);
	glm::vec3 getPosition() const;
};

#endif