#ifndef CONTROLLERINTERFACE_H
#define CONTROLLERINTERFACE_H

class ControllerInterface {
public:
	virtual void initController(int num, char *ptr[]) = 0;
};

#endif // !CONTROLLERINTERFACE_H

