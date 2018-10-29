#include "glutController.h"
#include "math.h"

Scene GlutController::*scene;

Shader GlutController::*shader;

bool GlutController::mouse_1_down = false, mouse_2_down = false;

int GlutController::curMouseX, GlutController::curMouseY;

glm::mat4 GlutController::model, GlutController::view, GlutController::proj;


glm::vec3 GlutController::cameraPos = glm::vec3(0.0f, 0.0f, 2.0f);
glm::vec3 GlutController::cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 GlutController::cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float GlutController::f1 = -90, GlutController::f2 = 0;

void GlutController::initController(int num, char *ptr[]) {

	//init Textures and mesh logic
	initScene();
	//init shader
	initShader();

	//attach textures to shader
	shader->attachTexture(0, "texture1");
	shader->attachTexture(1, "texture2");

	//init timers
	initTimers();

	//init Mouse, Motion, Keybork controllers
	initMouseAndKeybord();

	//init main program loop
	glutDisplayFunc(displayController);
}


void GlutController::initMouseAndKeybord() {
	glutMouseFunc(mouseController);
	glutMotionFunc(motionController);
}


void GlutController::initScene() {
	scene = new Scene(2, 1);

	scene->loadTexture(0, "gr\\wall.jpg");
	scene->loadTexture(1, "gr\\wall.jpg");

	scene->loadVAO(0, "gr\\cat.obj");
}


void GlutController::initTimers() {
	//TO DO
}


void GlutController::initShader() {
	shader = new Shader("shaders\\test.vert", "shaders\\test.frag");
	shader->use();
}


void GlutController::mouseController(int button, int state, int x, int y) {
	DEBUG_S(button << ' ' << state << ' ' << x << ' ' << y);
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_UP) {
			curMouseX = x;
			curMouseX = y;
			mouse_1_down = 1;
		}
		else {
			mouse_1_down = 0;
		}
	}
}


void GlutController::motionController(int x, int y) {
	DEBUG_S("move to " << x << ' ' << y);
	if (mouse_1_down == 1) {
		glm::vec3 front;
		f1 += (x - curMouseX) / -12.f;
		f2 += (y - curMouseY) / 12.f;

		if (f2 > 89.0f) {
		f2 = 89.0;
		}

		if (f2 < -89.0) {
			f2 = -89.0;
		}

		front.x = cos(glm::radians(f1)) * cos(glm::radians(f2));
		front.y = sin(glm::radians(f2));
		front.z = sin(glm::radians(f1)) * cos(glm::radians(f2));
		cameraFront = glm::normalize(front);
		curMouseX = x;
		curMouseY = y;
	}

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	shader->attachViewMatrix(view);

	//display();


}


void GlutController::displayController() {

}