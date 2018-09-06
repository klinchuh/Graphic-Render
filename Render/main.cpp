#include "stdafx.h"
#include "root.h"
#include <windows.h>



int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine, int nCmdShow) 
{
	return Application::InitProgram(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}