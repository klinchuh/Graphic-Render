#pragma once
#include <Windows.h>
#include <sstream>
#include <iostream>
#include <cassert>
#include "tgaimage.h"
#include "scene.h"
#include "Render.h"

class Application {
private:
	/*back buffer*/
	static HDC bufHdc;
	static HBITMAP bufBMP;

	/*data for scene*/
	static Scene *mainScene;

	/*TO DO*/
	//static void CALLBACK timerProc(HWND hWnd, UINT message, UINT_PTR idEvent, DWORD time);

	/*preset editboxes*/
	static void InitWindow(HWND hWnd);

	/*redraw a scene*/
	static void reDraw(HWND hWnd);

	/*copy data from Render::colorBuffer[] to the screen(back buffer)*/
	static void drawToBuffer(HWND hWnd);

	/*procceser*/
	static INT_PTR CALLBACK DlgProcceser(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	/*load scene and texture into memory*/
	static void loadScene(const char* objPath, const char* tgaPath);

	/*Invoke windows choose of files dialog and return path to file or empty file*/
	static void chooseWindowsFile(char * path);


public:
	/*function for init all program*/
	static void InitProgram(HINSTANCE hInst, HINSTANCE hPrevInstance,
		LPWSTR lpCmdLine, int nCmdShow);
};

