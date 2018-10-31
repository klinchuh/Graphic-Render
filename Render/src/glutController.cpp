#include "glutController.h"
#include "math.h"
#include "camera.h"

Scene *GlutController::scene;

ShaderInterface *GlutController::shader;

bool GlutController::mouse_1_down = false, mouse_2_down = false;

int GlutController::curMouseX, GlutController::curMouseY;

glm::mat4 GlutController::model, GlutController::view, GlutController::proj;


glm::vec3 GlutController::cameraPos = glm::vec3(0.0f, 0.0f, 2.0f);
glm::vec3 GlutController::cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 GlutController::cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


float GlutController::f1 = 90, GlutController::f2 = 0;

int GlutController::WIDTH = 800, GlutController::HEIGHT = 600;

float GlutController::scrollSpeed = 5, GlutController::cameraScale = 3;


void GlutController::initController(int argc, char *argv[]) {
	//Init glut Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(argv[0]);

	//Init glew
	if (glewInit()) {
		ERROR_FLT("Unable to initialize GLEW ... exiting");
		exit(EXIT_FAILURE);
	}

	//Init z-buffer
	glEnable(GL_DEPTH_TEST);


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

	//init camera
	initCamera();

	//init main program loop
	glutDisplayFunc(displayController);

	//On my intel intergated graphic chip don't work without it(don't render first cadr)
	displayController();
}


void GlutController::initCamera() {
	proj = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

	
	cameraPos = Camera::transAnglesToVector(f1, f2);
	cameraPos *= cameraScale;

	view = glm::lookAt(cameraPos + cameraFront, cameraFront, cameraUp);

	shader->attachViewMatrix(view);
	shader->attachProjectionMatrix(proj);
	shader->attachModelMatrix(model);
}


void GlutController::initMouseAndKeybord() {
	glutMouseFunc(mouseController);
	glutMotionFunc(motionController);
	glutKeyboardFunc(keyboardController);
}


void GlutController::initScene() {
	scene = new Scene(2, 1);

	scene->loadTexture(0, "gr\\african_head_diffuse.jpg");
	scene->loadTexture(1, "gr\\african_head_diffuse.jpg");

	scene->loadVAO(0, "gr\\african_head.obj");
}


void GlutController::initTimers() {
	//TO DO
}


void GlutController::initShader() {
	shader = new Shader("shd\\test.vert", "shd\\test.frag");
	shader->use();
}


void GlutController::mouseController(int button, int state, int x, int y) {
	DEBUG_S(">>>mouse proc : " << button << ' ' << state << ' ' << x << ' ' << y);
	switch (button) {
		case GLUT_LEFT_BUTTON: {
			if (state == GLUT_DOWN) {
				curMouseX = x;
				curMouseY = y;
				mouse_1_down = 1;
			}
			else {
				mouse_1_down = 0;
			}
			break;
		}
		case 3: {
			cameraScale += 0.15f;
			break;
		}
		case 4: {
			cameraScale -= 0.15f;
			if (cameraScale < 0.5f) {
				cameraScale = 0.5f;
			}
			break;
		}

	}

	displayController();
}


void GlutController::motionController(int x, int y) {
	DEBUG_S(">>>move to " << x << ' ' << y);
	
	shader->use();

	if (mouse_1_down == 1) {
		glm::vec3 front;
		f1 += (x - curMouseX) / scrollSpeed;
		f2 += (y - curMouseY) / scrollSpeed;

		curMouseX = x;
		curMouseY = y;

		if (f2 > 89.0f) {
			f2 = 89.0;
		}

		if (f2 < -89.0) {
			f2 = -89.0;
		}
	}

	displayController();
}


void GlutController::displayController() {
	//Set background color
	glClearColor(0, 1.0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Bind Our Shader
	shader->use();

	//Bind Vertex Array(VAO)
	glBindVertexArray(scene->VAOs[0]);

	//Draw current Vertex Array(VAO)

	cameraPos = Camera::transAnglesToVector(f1, f2);
	cameraPos *= cameraScale;
	view = glm::lookAt(cameraPos + cameraFront, cameraFront, cameraUp);
	shader->attachViewMatrix(view);

	model = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -1.0f));
	shader->attachModelMatrix(model);
	glDrawArrays(GL_TRIANGLES, 0, scene->getVAOSize(0));

	//glDrawArrays(GL_TRIANGLES, 0, 6); 

	//Bend Standart Vertex Array
	glBindVertexArray(0);
	
	glFlush();
	//We have double buffer
	glutSwapBuffers();
}

void GlutController::keyboardController(unsigned char key, int x, int y) {
	DEBUG_S(key << ' ' << x << ' ' << y);
	//switch(key) {
//
	//}
}