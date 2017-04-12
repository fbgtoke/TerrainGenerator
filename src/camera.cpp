#include "camera.hpp"

const float Camera::TRANSLATION_VEL = 0.01f;
const float Camera::ROTATION_ANGLE  = M_PI/64.f;
const float Camera::PITCH_LIMIT     = M_PI/4.f;

const float Camera::ZNEAR =  .5f;
const float Camera::ZFAR  = 20.f;

Camera::Camera(int w, int h) {
	pitch = 0.f;
	yaw   = 0.f;
	position = glm::vec3(0.f, 0.f, 1.f);

	width  = w;
	height = h;
	fov    = atan(height/2);
}

Camera::~Camera() {}

void Camera::lock() {
	if (pitch < -PITCH_LIMIT)
		pitch = -PITCH_LIMIT;

	if (pitch > PITCH_LIMIT)
		pitch = PITCH_LIMIT;

	if (yaw < 0.f)
		yaw += 2 * M_PI;

	if (yaw > 2 * M_PI)
		yaw -= 2 * M_PI;
}

void Camera::move(const glm::vec3& direction) {
	glm::vec3 local_direction = direction;
	local_direction = glm::rotate(local_direction, pitch, glm::vec3(1.f, 0.f, 0.f));
	local_direction = glm::rotate(local_direction, yaw  , glm::vec3(0.f, 1.f, 0.f));

	position += TRANSLATION_VEL * glm::normalize(local_direction);
}

glm::vec3 Camera::getVRP() {
	move(glm::vec3(0.f, 0.f, -1.f));
	glm::vec3 VRP = position;
	move(glm::vec3(0.f, 0.f, 1.f));

	return VRP;
}

void Camera::event(unsigned char key, int x, int y) {
	switch (key) {
		case 'j': yaw   += ROTATION_ANGLE; lock(); break;
		case 'l': yaw   -= ROTATION_ANGLE; lock(); break;
		case 'i': pitch += ROTATION_ANGLE; lock(); break;
		case 'k': pitch -= ROTATION_ANGLE; lock(); break;

		case 'w': move(glm::vec3( 0.f,  0.f, -1.f)); break;
		case 's': move(glm::vec3( 0.f,  0.f,  1.f)); break;
		case 'd': move(glm::vec3( 1.f,  0.f,  0.f)); break;
		case 'a': move(glm::vec3(-1.f,  0.f,  0.f)); break;
		case 'q': move(glm::vec3( 0.f, -1.f,  0.f)); break;
		case 'e': move(glm::vec3( 0.f,  1.f,  0.f)); break;

		default: break;
	}
}

// WIP
void Camera::resize(int w, int h) {}

glm::mat4 Camera::getViewMatrix() {
	glm::vec3 OBS = position;
	glm::vec3 VRP = getVRP();
	glm::vec3 up  = glm::vec3(0.f, 1.f, 0.f);

	return glm::lookAt(OBS, VRP, up);
}

glm::mat4 Camera::getProjectMatrix() {
	float ratio = width / height;

	return glm::perspective(fov, ratio, ZNEAR, ZFAR);
}

void Camera::setPosition(const glm::vec3& p) { position = p; }
glm::vec3 Camera::getPosition() const { return position; }