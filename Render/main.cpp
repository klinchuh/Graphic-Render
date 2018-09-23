#include <Windows.h>	
#include "root.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine, int nCmdShow)
{
	Application::InitProgram(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	return 0;
}
