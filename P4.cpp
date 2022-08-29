
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>
#include <gl/GLU.h>
#include "RGBColor.cpp"
#include "P4.h"
#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical 4"

//Question No
int qNo = 1;

//Triangle Rotation Propertise
float xAngle = 0;
float yAngle = 0;
float zAngle = 0;

//rotation for the arm
float rAngle = 0.0;
float rSpeed = 0.5;

//rotation for the entire arm
float zArm = 0.0;
float xArm = 0.0;
float yArm = 0.0;

/*
 * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
 * 0x3A - 0x40 : unassigned
 * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
 * For lazy reference
 * https://www.ibm.com/docs/en/ste/8.4.1?topic=information-hex-decimal-symbol-values
 */

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == 0x31) qNo = 1;
		else if (wParam == 0x32) qNo = 2;
		else if (wParam == 0x58) xAngle -= rSpeed;
		else if (wParam == 0x59) yAngle -= rSpeed;
		else if (wParam == 0x5A) zAngle -= rSpeed;
		else if (wParam == VK_UP) rAngle += rSpeed;
		else if (wParam == VK_DOWN) rAngle -= rSpeed;
		else if (wParam == VK_LEFT) xArm += rSpeed;
		else if (wParam == VK_RIGHT) xArm -= rSpeed;
		else if (wParam == VK_SPACE) {
			rAngle = 0;
			xArm = 0;
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------


 //--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

//Demo Code

void drawCube(float sz) {

	glBegin(GL_QUADS);
	// Face 1
	glColor3f(1, 0, 0);
	glVertex3f(0.0f, 0.0f, sz);
	glVertex3f(sz, 0.0f, sz);
	glVertex3f(sz, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	// Face 2 
	glColor3f(1, 1, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, sz, 0.0f);
	glVertex3f(0.0f, sz, sz);
	glVertex3f(0.0f, 0.0f, sz);
	// Face 3
	glColor3f(1, 1, 1);
	glVertex3f(0.0f, 0.0f, sz);
	glVertex3f(0.0f, sz, sz);
	glVertex3f(sz, sz, sz);
	glVertex3f(sz, 0.0f, sz);
	//Face 4
	glColor3f(0, 1, 1);
	glVertex3f(sz, 0.0f, sz);
	glVertex3f(sz, sz, sz);
	glVertex3f(sz, sz, 0.0f);
	glVertex3f(sz, 0.0f, 0.0f);
	//Face 5
	glColor3f(0, 0, 1);
	glVertex3f(sz, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, sz, 0.0f);
	glVertex3f(sz, sz, 0.0f);
	//Face 6
	glColor3f(1, 0, 0);
	glVertex3f(sz, sz, 0.0f);
	glVertex3f(0.0f, sz, 0.0f);
	glVertex3f(0.0f, sz, sz);
	glVertex3f(sz, sz, sz);
	glEnd();

}

void drawRectangle(float sz) {

	glBegin(GL_LINE_LOOP);
	// Face 1
	glColor3f(1, 0, 0);
	glVertex3f(0.0f, 0.0f, sz);
	glVertex3f(sz, 0.0f, sz);
	glVertex3f(sz, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	// Face 2 
	glColor3f(1, 1, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, sz, 0.0f);
	glVertex3f(0.0f, sz, sz);
	glVertex3f(0.0f, 0.0f, sz);
	// Face 3
	glColor3f(1, 1, 1);
	glVertex3f(0.0f, 0.0f, sz);
	glVertex3f(0.0f, sz, sz);
	glVertex3f(sz, sz, sz);
	glVertex3f(sz, 0.0f, sz);
	//Face 4
	glColor3f(0, 1, 1);
	glVertex3f(sz, 0.0f, sz);
	glVertex3f(sz, sz, sz);
	glVertex3f(sz, sz, 0.0f);
	glVertex3f(sz, 0.0f, 0.0f);
	//Face 5
	glColor3f(0, 0, 1);
	glVertex3f(sz, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, sz, 0.0f);
	glVertex3f(sz, sz, 0.0f);
	//Face 6
	glColor3f(1, 0, 0);
	glVertex3f(sz, sz, 0.0f);
	glVertex3f(0.0f, sz, 0.0f);
	glVertex3f(0.0f, sz, sz);
	glVertex3f(sz, sz, sz);
	glEnd();

}

void cube() {

	glRotatef(0.01, 1, -1, 0);
	drawCube(0.5);

	drawCube(-0.5);
}

//Exercise

void drawPyramid(float size)
{
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	//face 1 bottom
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(0.0, 0.0, size);//p1
	glVertex3f(size, 0.0, size);//go right from p1
	glVertex3f(size, 0.0, 0.0);//go front from p2
	glVertex3f(0.0, 0.0, 0.0);//go left from p2
	glVertex3f(size / 2, size, size / 2); // go up from p2 to center up
	
	//face 2 top
	glVertex3f(0.0, 0.0, size); // go from the center up to left back point (p1)
	glVertex3f(size / 2, size, size / 2); // p1 go back up to center up 
	glVertex3f(size, 0.0, size); // center up and go to (p2)
	glVertex3f(size / 2, size, size / 2); // go back up to center up
	glVertex3f(size, 0.0, 0.0); // center up and go to (p3)
	glVertex3f(size / 2, size, size / 2); // back to center up
	glVertex3f(0.0, 0.0, 0.0); // go to p4
	glEnd();
}

void exercise1() {

	glPushMatrix(); 
	{
		glRotatef(xAngle, 1, 0, 0);
		glRotatef(yAngle, 0, 1, 0);
		glRotatef(zAngle, 0, 0, 1);
		drawPyramid(0.5);
	}
	glPopMatrix();
}

void drawRec(float sz) {
	glBegin(GL_LINE_LOOP);
	{
		//Face 1
		glVertex3f(0, sz, 0);
		glVertex3f(sz * 2, sz, 0); //right
		glVertex3f(sz * 2, 0, 0); //down
		glVertex3f(0, 0, 0); //left
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	{	
		//Face 2
		glVertex3f(0, sz, 0);
		glVertex3f(0, sz, sz);//back
		glVertex3f(sz * 2, sz, sz);//right
		glVertex3f(sz * 2, sz, 0);//front
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	{
		//Face 3
		glVertex3f(0, sz, sz);
		glVertex3f(0, 0, sz);//down
		glVertex3f(sz * 2, 0, sz);//right
		glVertex3f(sz * 2, sz, sz);// up
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	{
		glVertex3f(0, 0, sz);
		glVertex3f(sz * 2, 0, sz);//right
		glVertex3f(sz * 2, 0, 0);//front
		glVertex3f(0, 0, 0);//left

	}
	glEnd();
}

void robotFinger() {
	glColor3f(1, 1, 1);

	glPushMatrix(); 
	{
		glScalef(0.5, 0.5, 0.5);
		glTranslatef(-1, 0, 0);
		glRotatef(xArm, 1, 0, 0);
		glRotatef(yArm, 0, 1, 0);
		glRotatef(yArm, 0, 0, 1);
		drawRec(0.5);
		glPushMatrix(); 
		{
			glTranslatef(1, 0, 0);
			glRotatef(rAngle, 0, 0, 1);
			drawRec(0.5);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void display() {

	
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glTranslatef(0.00001, 0.00001, 0);
	//glRotatef(5, 0, 1, 1);

	switch (qNo) {
		case 1:
			exercise1();
			break;
		case 2:
			robotFinger();
			break;
		default:
			break;
	}

}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;
	//configure the resolution here
	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------

