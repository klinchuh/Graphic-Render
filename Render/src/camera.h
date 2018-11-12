#ifndef CAMERA_H
#define CAMERA_H

#include "basicLibs.h"

//TO DO:

class Camera {
private:
	int WIDTH, HEIGHT;
	glm::mat4 *view, *proj;
	glm::vec3 cameraPos, cameraFront, cameraUp;
	float yaw, pitch;
	float scrollSpeed, cameraScale;

	glm::vec3 transAnglesToVector(float f1, float f2);

	void reCountView();

public:

	Camera(int width, int height);

	~Camera();


	void setScrollSpeed(float speed);

	void setCameraScale(float scale);


	void scaleOut();

	void scaleIn();

	
	void modifYaw(float move);

	void modifPitch(float move);


	glm::mat4* getViewMatrix();

	glm::mat4* getProjectionMatrix();
};

#endif // !CAMERA_H
