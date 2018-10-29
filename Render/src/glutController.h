#ifndef GLUTCONTROLLER_H
#define GLUTCONTROLLER_H

#include "basicLibs.h"

#include "controllerInterface.h"
#include "scene.h"
#include "shader.h"

class GlutController : public ControllerInterface {
private:
	static Scene *scene;

	static ShaderInterface *shader;

	//Mouse and keybord:
	static bool mouse_1_down, mouse_2_down;
	static int curMouseX, curMouseY;

	//Camera matrix:
	static glm::mat4 model, view, proj;


	//Camera Config:
	static glm::vec3 cameraPos;
	static glm::vec3 cameraFront;
	static glm::vec3 cameraUp;
	static float f1, f2;

public:
	GlutController() {}

	void initMouseAndKeybord();

	void initScene();

	void initTimers();

	void initShader();

	void initController(int num, char *ptr[]);

	static void displayController();

	static void motionController(int x, int y);

	static void mouseController(int button, int state, int x, int y);
};

#endif // !GLUTCONTROLLER_H

