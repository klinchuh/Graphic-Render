#ifndef ROOT_H
#define ROOT_H

#include "basicLibs.h"

#include "glutController.h"
#include "controllerInterface.h"

void root(int num, char *ptr[]) {
	ControllerInterface *Controller = new GlutController();

	Controller->initController(num, ptr);

	glutMainLoop();
}

#endif // !ROOT_H
