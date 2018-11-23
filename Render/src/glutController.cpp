#include "glutController.h"
#include "math.h"

#ifdef _WIN32
#include <commdlg.h>
#endif // _WIN32

Scene *GlutController::scene;

ShaderInterface *GlutController::shader;

bool GlutController::mouse_1_down = false, mouse_2_down = false;

int GlutController::curMouseX, GlutController::curMouseY;

Camera *GlutController::camera;

int GlutController::WIDTH = 800, GlutController::HEIGHT = 600;


void GlutController::initController(int argc, char *argv[]) {
	//Init glut Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_SINGLE);
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

	//init timers
	initTimers();

	//init Mouse, Motion, Keybork controllers
	initMouseAndKeybord();

	//init pop up menu
	initMenu();

	//init camera
	initCamera();

	//init main program loop
	glutDisplayFunc(displayController);

	//On my intel intergated graphic chip don't work without it(don't render first cadr)
	displayController();
}

void GlutController::initCamera() {
	camera = new Camera(WIDTH, HEIGHT);

	shader->attachProjectionMatrix(camera->getProjectionMatrix());
	shader->attachViewMatrix(camera->getViewMatrix());
}

void GlutController::initMenu() {
	int k = glutCreateMenu(menuController);

	//TO DO
	glutAddMenuEntry("TO DO: Choose vertex shader", CHOOSE_VERTEX_SHADER);
	//TO DO
	glutAddMenuEntry("TO DO: Choose fragment shader", CHOOSE_FRAGMENT_SHADER);

	glutAddMenuEntry("Choose texture(*.jpg)", CHOOSE_TEXTURE);
	glutAddMenuEntry("Choose object(*.obj)", CHOOSE_OBJECT);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void GlutController::initMouseAndKeybord() {
	glutMouseFunc(mouseController);
	glutMotionFunc(motionController);
	glutKeyboardFunc(keyboardController);
}

void GlutController::initScene() {
	scene = new Scene(2, 2);

	scene->loadTexture(0, "gr\\african_head_diffuse.jpg");
	//scene->loadTexture(1, "gr\\wall.jpg");

	scene->loadVAO(0, "gr\\african_head.obj");
	//scene->loadVAO(1, "gr\\cat.obj");

	//set Up start pos of object
	scene->addObject(0, 0, glm::vec3{ 0, 0, 0 }, glm::vec3{0.0f, 0.f, 0.f});
	//scene->addObject(1, 0, glm::vec3{ 3, 0, 0 }, glm::vec3{0.0f, 0.f, 0.f});
	//scene->addObject(0, 1, glm::vec3{ 6, 0, 0 }, glm::vec3{100.0f, 0.f, 100.f});
}

void GlutController::timerController(int val) {
	displayController();
	glutTimerFunc(1, timerController, 0);
}

void GlutController::initTimers() {
	glutTimerFunc(1, timerController, 0);
}

void GlutController::initShader() {
	shader = new Shader("shd\\test.vert", "shd\\test.frag");
	shader->use();
	shader->attachTexture(0, "texture1");
	shader->setVec3("lightVec", glm::vec3{ 0.0f, 1.0f, 1.0f });
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
	//mouse wheel up
	case 3: {
		camera->scaleOut();
		break;
	}
	//mouse wheel down
	case 4: {
		camera->scaleIn();
		break;
	}
	}
}

void GlutController::motionController(int x, int y) {
	DEBUG_S(">>>move to " << x << ' ' << y);

	shader->use();

	if (mouse_1_down == 1) {
		glm::vec3 front;
		camera->modifYaw(x - curMouseX);
		camera->modifPitch(y - curMouseY);

		curMouseX = x;
		curMouseY = y;
	}
}

void GlutController::displayController() {
	//Set background color
	glClearColor(0, 1.0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Bind Our Shader
	shader->use();
	shader->setVec3("lightVec", camera->getCamDir());

	//Set up transforms matrices
	shader->attachViewMatrix(camera->getViewMatrix());
	shader->attachProjectionMatrix(camera->getProjectionMatrix());



	//render every object
	for (size_t i = 0; i < scene->getObjectsCount(); i++) {

		//Bind Vertex Array(VAO) and texture
		scene->bindObject(i);

		shader->attachModelMatrix(&scene->getModelMatrix(i));

		//Draw current Vertex Array(VAO)
		glDrawArrays(GL_TRIANGLES, 0, scene->getObjectMeshSize(i));
	}

	//We have double buffer
	glutSwapBuffers();
}

void GlutController::keyboardController(unsigned char key, int x, int y) {
	DEBUG_S(key << ' ' << x << ' ' << y);
	//switch(key) {
//
	//}
}

void GlutController::menuController(int menuIdentificator) {

	switch (menuIdentificator) {
	case CHOOSE_VERTEX_SHADER: {
		//TO DO
		break;
	}

	case CHOOSE_FRAGMENT_SHADER: {
		// TO DO
		break;
	}

	case CHOOSE_TEXTURE: {
		char *path = new char[255];
		chooseWindowFile(path);
		if (path[0] != '\0') {
			scene->loadTexture(0, path);
			shader->attachTexture(0, "texture1");
		}
		delete[] path;
		break;
	}

	case CHOOSE_OBJECT: {
		char *path = new char[255];
		chooseWindowFile(path);
		if (path[0] != '\0') {
			scene->loadVAO(0, path);
			shader->attachTexture(0, "texture1");
		}
		delete[] path;
		break;
	}
	}
}

void GlutController::chooseWindowFile(char * path) {
#ifdef _WIN32 
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	OPENFILENAME ofn = { 0 };
	char szFileName[260];
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = (LPSTR)path;
	*(ofn.lpstrFile) = 0;
	ofn.nMaxFile = 255;
	ofn.lpstrFilter = NULL;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = (LPSTR)szFileName;
	*(ofn.lpstrFileTitle) = 0;
	ofn.nMaxFileTitle = sizeof(szFileName);
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_EXPLORER;
	GetOpenFileName(&ofn);
#endif // _WIN32
}