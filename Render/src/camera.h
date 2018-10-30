#ifndef CAMERA_H
#define CAMERA_H

#include "basicLibs.h"

//TO DO:

class Camera {
public:
	static glm::vec3 transAnglesToVector(float f1, float f2) {
		glm::vec3 answer;
		answer.x = cos(glm::radians(f1)) * cos(glm::radians(f2));
		answer.y = sin(glm::radians(f2));
		answer.z = sin(glm::radians(f1)) * cos(glm::radians(f2));
		answer = glm::normalize(answer);

		return answer;
	}
};

#endif // !CAMERA_H
