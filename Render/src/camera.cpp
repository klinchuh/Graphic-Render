#include "camera.h"


Camera::Camera(int width, int height) {
	WIDTH = width;
	HEIGHT = height;

	view = new glm::mat4;
	proj = new glm::mat4;


	scrollSpeed = 5;
	cameraScale = 3;

	cameraFront = glm::vec3(0, 0, 0);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	*proj = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);

	reCountView();
}

Camera::~Camera() {
	delete view;
	delete proj;
}

void Camera::setScrollSpeed(float speed) {
	scrollSpeed = speed;
}

void Camera::setCameraScale(float scale) {
	cameraScale = scale;
	reCountView();
}

void Camera::scaleOut() {
	cameraScale *= 1.02;
	reCountView();
}

void Camera::scaleIn() {
	cameraScale *= 0.98;

	if (cameraScale < 0.5f) {
		cameraScale = 0.5f;
	}

	reCountView();
}

void Camera::modifYaw(float move) {
	yaw += move / scrollSpeed;
	reCountView();
}

void Camera::modifPitch(float move) {
	pitch += move / scrollSpeed;

	if (pitch > 89.0f) {
		pitch = 89.0;
	}

	if (pitch < -89.0) {
		pitch = -89.0;
	}

	reCountView();
}

glm::mat4* Camera::getViewMatrix() {
	return view;
}

glm::mat4* Camera::getProjectionMatrix() {
	return proj;
}

glm::vec3 Camera::transAnglesToVector(float f1, float f2) {
	glm::vec3 answer;
	answer.x = cos(glm::radians(f1)) * cos(glm::radians(f2));
	answer.y = sin(glm::radians(f2));
	answer.z = sin(glm::radians(f1)) * cos(glm::radians(f2));
	answer = glm::normalize(answer);

	return answer;
}

void Camera::reCountView() {
	cameraPos = transAnglesToVector(yaw, pitch);

	*view = glm::lookAt(cameraPos * cameraScale + cameraFront, cameraFront, cameraUp);
}
