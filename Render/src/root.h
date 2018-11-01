#ifndef ROOT_H
#define ROOT_H

#include "basicLibs.h"

#include "glutController.h"
#include "controllerInterface.h"

void root(int argc, char *argv[]) {
	ControllerInterface *Controller = new GlutController();

	Controller->initController(argc, argv);

	glutMainLoop();
}

#endif // !ROOT_H
