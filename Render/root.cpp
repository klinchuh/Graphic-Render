#include <windows.h>
#include "root.h"
#include "resource.h"

HDC Application::bufHdc;
HBITMAP Application::bufBMP;
Scene *Application::mainScene;

//------------------------------------------------------------------------------------
/*void CALLBACK Application::timerProc(HWND hWnd, UINT message, UINT_PTR idEvent, DWORD time) {
	reDraw(hWnd);
}*/
//------------------------------------------------------------------------------------
void Application::InitScene(HWND hWnd) {
	mainScene = new Scene();

	assert(mainScene->loadScene("obj/african_head.obj"));
	assert(mainScene->loadTexture("obj/african_head_diffuse.tga"));

	SetDlgItemText(hWnd, IDC_EDIT1, "7 0 7");
	SetDlgItemText(hWnd, IDC_EDIT2, "1.5 0 1.5");
	SetDlgItemText(hWnd, IDC_EDIT3, "0 1 0");
}
//------------------------------------------------------------------------------------
void Application::reDraw(HWND hWnd) {

	Vec3 eye, center, up;
	Vec2 scale;

	char str[255];
	std::stringstream ss;
	GetDlgItemText(hWnd, IDC_EDIT1, str, 255);
	ss << str << ' ';
	GetDlgItemText(hWnd, IDC_EDIT2, str, 255);
	ss << str << ' ';
	GetDlgItemText(hWnd, IDC_EDIT3, str, 255);
	ss << str << ' ';

	ss >> eye[0] >> eye[1] >> eye[2]
		>> center[0] >> center[1] >> center[2]
		>> up[0] >> up[1] >> up[2];

	Render::lookAt(eye, center, up);

	Render::setViewPotrMatrix(0, 0, Render::sizeX, Render::sizeY);

	Render::compileScene(mainScene);


	RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}
//------------------------------------------------------------------------------------
void Application::drawToBuffer(HWND hWnd) {

	HDC hdc = GetDC(hWnd);

	bufHdc = CreateCompatibleDC(hdc);

	bufBMP = CreateCompatibleBitmap(hdc, Render::sizeX, Render::sizeY);

	SelectObject(bufHdc, bufBMP);

	int sizeX = Render::sizeX;
	int sizeY = Render::sizeY;


	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			SetPixel(bufHdc, i, sizeY - j, Render::colorBuffer[i * sizeY + j]);
		}
	}

}
//------------------------------------------------------------------------------------
void Application::InitProgram(HINSTANCE hInst, HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine, int nCmdShow) {
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProcceser);
}
//------------------------------------------------------------------------------------
INT_PTR CALLBACK Application::DlgProcceser(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
		case WM_INITDIALOG: {
			InitScene(hWnd);
			//SetTimer(hWnd, Timer_ID1, 10000, timerProc);
			return (INT_PTR)TRUE;
		}

		case WM_CREATE: {
			break;
		}

		case WM_COMMAND: {

			switch (LOWORD(wParam)) {

			case IDC_reDraw: {
				reDraw(hWnd);
				break;
			}

			case IDC_CHECK1: {
				Render::RENDER_WITHOUT_TEXTURES ^= 1;
				break;
			}

			case IDCANCEL:
			case IDOK:
			{
				EndDialog(hWnd, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
			}
			break;
		}

		case WM_PAINT: {
			PAINTSTRUCT ps;
			drawToBuffer(hWnd);

			HDC hdc = BeginPaint(hWnd, &ps);

			//BiBlt(hdc, x, y, ...) x, y - up left angle of Picture
			BitBlt(hdc, 50, 50, Render::sizeX, Render::sizeY, bufHdc, 0, 0, SRCCOPY);

			EndPaint(hWnd, &ps);
			break;
		}

		case WM_CLOSE: {
			EndDialog(hWnd, LOWORD(wParam));
		}
	}

	return (INT_PTR)FALSE;
}