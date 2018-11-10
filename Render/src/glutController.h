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
	static glm::mat4 *model, *view, *proj;


	//Camera Config:
	static glm::vec3 cameraPos;
	static glm::vec3 cameraFront;
	static glm::vec3 cameraUp;
	static float f1, f2;
	static int WIDTH, HEIGHT;
	static float scrollSpeed, cameraScale;

	static enum { CHOOSE_VERTEX_SHADER, CHOOSE_FRAGMENT_SHADER, CHOOSE_TEXTURE, CHOOSE_OBJECT };

	//Initializing of Mouse and Leybord processor
	void initMouseAndKeybord();

	//Load meshes and textures(scene)
	void initScene();

	//Init timers TODO
	void initTimers();

	//Initializing of shader
	void initShader();

	//init camera and translate matrices
	void initCamera();

	//init pop-up menu
	void initMenu();

	//Main loop processor
	static void displayController();

	//Mouse motion processor
	static void motionController(int x, int y);

	//Mouse mouse processor
	static void mouseController(int button, int state, int x, int y);

	//keyboardController
	static void keyboardController(unsigned char key, int x, int y);
	
	//
	static void timerController(int val);

	//Menu controller
	static void menuController(int);

	//Get path to file by systems calls
	//TO DO to LINUX
	static void chooseWindowFile(char * path);

public:

	GlutController() {}

	//Main init function, call first
	void initController(int argc, char *argv[]);
};

#endif // !GLUTCONTROLLER_H

