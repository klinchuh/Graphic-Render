#pragma once
#include "stdafx.h"
#include <windows.h>
#include "tgaimage.h"
#include "scene.h"
#include "Render.h"
#include "resource.h"
#include <sstream>
#include <iostream>
#include <cassert>

class Application {
public:

	//back buffer
	static HDC bufHdc;
	static HBITMAP bufBMP;

	//data for scene
	static Scene *mainScene;


	//TO DO
	static void CALLBACK timerProc(HWND hWnd, UINT message, UINT_PTR idEvent, DWORD time);

	//loading a scene into memory
	static void InitScene(HWND hWnd);

	//redraw a scene
	static void reDraw(HWND hWnd);

	//copy data from Render::colorBuffer[] to the screen(back buffer)
	static void drawToBuffer(HWND hWnd);

	//function for init all program
	static int InitProgram(HINSTANCE hInst, HINSTANCE hPrevInstance,
		LPWSTR lpCmdLine, int nCmdShow);

	//procceser
	static INT_PTR CALLBACK About(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

HDC Application::bufHdc;
HBITMAP Application::bufBMP;
Scene *Application::mainScene;