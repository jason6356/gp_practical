
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>
#include <vector>
#include <thread>
#include "RGBColor.cpp"
#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical 2"

//orgin
float x = 0.15, y = 0;
//radius
float r = 0.2;
float angle = 0;
float noOfTri = 1000;
float x2 = 0, y2 = 0;
float PI = 3.1429;

int qNo = 1;

//Translatetion
float tx = 0, ty = 0;
float tSpeed = 0.01;

//change color
float red = 1;
float green = 0;
float blue = 0;

//array of colors

RGBColor colors[] = {
	RGBColor(255,0,0),
	RGBColor(255,165,0),
	RGBColor(255,255,0),
	RGBColor(0,128,0),
	RGBColor(0,0,255),
	RGBColor(255,0,255),
	RGBColor(128,0,128),
};

//color 
RGBColor currentColor = colors[0];

//extra feature 
float rAngle = 0;
boolean spin = false;

//scale vars
float sRate = 0.001;
float currentScale = 1;

/*
 * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
 * 0x3A - 0x40 : unassigned
 * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
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
		else if (wParam == 0x33) qNo = 3;
		else if (wParam == 0x34) qNo = 4;
		else if (wParam == 0x35) spin = ~spin;
		else if (wParam == 0x36) qNo = 6;
		else if (wParam == VK_LEFT) tx -= tSpeed;
		else if (wParam == VK_RIGHT) tx += tSpeed;
		else if (wParam == VK_UP) ty += tSpeed;
		else if (wParam == VK_DOWN) ty -= tSpeed;
		else if (wParam == 0x52) {
			red = 1;
			green = 0;
			blue = 0;
		}
		else if (wParam == 0x47) {
			red = 0;
			green = 1;
			blue = 0;
		}
		else if (wParam == 0x42) {
			red = 0;
			green = 0;
			blue = 1;

		}
		else if (wParam == VK_SPACE) {
			tx = 0;
			ty = 0;
			red = 1;
			green = 1;
			blue = 1;
			rAngle = 0;
			spin = false;
		}
		break;	


	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
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

void mySquare() {
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex2f(-0.2, 0.1);
	glVertex2f(0.2, 0.1);
	glVertex2f(0.2, -0.1);
	glVertex2f(-0.2, -0.1);
	glEnd();

}

int i = 0;

void q1() {

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glPointSize(10);
	glColor3f(red, green, blue);
	glTranslatef(tx, ty, 0);

	glBegin(GL_POINTS);
		glVertex2f(0.0, 0.0);
	glEnd();
}


void updateColor() {
	static int i = 0;
	currentColor = colors[i % 7];
	i++;
}

void q2() {

	//std::this_thread::sleep_for(std::chrono::milliseconds(250));
	//12 vertex, 7 colors
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	if (spin) {
		rAngle += 0.05;
		if (rAngle > 360)
			rAngle = 0;
	}

	glRotatef(rAngle, 0, 0, 1);

	glShadeModel(GL_SMOOTH);
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLE_FAN);
		glColor3f(currentColor.r, currentColor.g, currentColor.b);
		updateColor();
		glVertex2f(0.0, -0.16);
		glColor3f(currentColor.r, currentColor.g, currentColor.b);
		updateColor();
		glVertex2f(0.0, -0.36);
		glColor3f(currentColor.r, currentColor.g, currentColor.b);
		updateColor();
		glVertex2f(0.3, -0.58);
		glColor3f(currentColor.r, currentColor.g, currentColor.b);
		updateColor();
		glVertex2f(0.19, -0.22);
		glColor3f(currentColor.r, currentColor.g, currentColor.b);
		updateColor();
		glVertex2f(0.5, 0.0);
		glColor3f(currentColor.r, currentColor.g, currentColor.b);
		updateColor();
		glVertex2f(0.11, 0.0);
		glColor3f(currentColor.r, currentColor.g, currentColor.b);
		updateColor();
		glVertex2f(0.0, 0.36);
		glColor3f(currentColor.r, currentColor.g, currentColor.b);
		updateColor();
		glVertex2f(-0.11, 0.0);
		glColor3f(currentColor.r, currentColor.g, currentColor.b);
		updateColor();
		glVertex2f(-0.5, 0.0);
		glColor3f(currentColor.r, currentColor.g, currentColor.b);
		updateColor();
		glVertex2f(-0.18, -0.22);
		glColor3f(currentColor.r, currentColor.g, currentColor.b);
		updateColor();
		glVertex2f(-0.3, -0.58);
		glColor3f(currentColor.r, currentColor.g, currentColor.b);
		updateColor();
		glVertex2f(0.0, -0.36);
	glEnd();
}

void q3() {
	
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glPointSize(5);
	glRotatef(rAngle, 0, 0, 1);
	glTranslatef(0.5, 0.0, 0);
	glBegin(GL_POINTS);
		glColor3f(1, 0, 0);
		glVertex3f(0, -0.5, 0);
	glEnd();

	rAngle += 0.01;

}

boolean grow = true;

void q4() {

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glScalef(currentScale, currentScale, 1);

	glBegin(GL_QUADS);
		glColor3f(1, 0, 0);
		glVertex3f(0.0, 0.1, 0.0);
		glVertex3f(0.1, 0.1, 0.0);
		glVertex3f(0.1, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	if (currentScale > 10)
		currentScale = 1;

	currentScale += sRate;




}

float zTest = 0.01;

void display() {
	
	switch (qNo) {
	case 1:
		q1();
		break;
	case 2:
		q2();
		break;
	case 3:
		q3();
		break;
	case 4:
		q4();
		break;
	default:
		break;
	}

}
//
//void display()
//{
//	//--------------------------------
//	//	OpenGL drawing
//	//--------------------------------
//	// Sequence of graphics
//	// Scale -> Rotation -> Translation
//	// 
//	// 
//	// 
//	////set the background colour
//	//glLoadIdentity();
//	//glClear(GL_COLOR_BUFFER_BIT);
//	//glTranslatef(-0.5, 0.5, 0.0);
//	////glRotatef(-90, 0.0, 0.0, 1.0);
//	////go left 0.5 unit 
//	////glScalef(1.05, 1.05, 0.0);
//	//
//	//glBegin(GL_TRIANGLES);
//	//	glVertex2f(-0.5, 0.0);
//	//	glVertex2f(0.0, 0.5);
//	//	glVertex2f(0.5, 0.0);
//	//glEnd();
//
//	//glBegin(GL_QUADS);
//	//glVertex2f(-0.5,0.0);
//	//glVertex2f(-0.5,0.5);
//	//glVertex2f(0.5,0.5);
//	//glVertex2f(0.5, 0.0);
//	//glEnd();
//	//i++;
//	
//	//chap 5 -> projection matrix , 
//	//glMatrixMode(GL_MODELVIEW);
//
//	//glloadidentity (clear all the transformation in the matrix stack)
//	//glTranslate // 2 -> this will run after the rotation
//	//glRotate  //1 -> this will run first
//	//draw()
//
//	//from these code segments, all the transformation will be stacked up together for the next obj
//	//glLoadIdentity();
//	//glLineWidth(10);
//	//glTranslatef(0.0, 0.5, 0.5);
//	//glBegin(GL_POINTS);
//	//	glVertex2f(0, 0);
//	//glEnd();
//
//	////first way -> use glloadidentity to remove all the matrix stack , then the stack 
//	//// will remain the translation of go right
//	////glLoadIdentity();
//	//glTranslatef(0.5, 0.0, 0.0);
//	//glBegin(GL_POINTS);
//	//	glVertex2f(0, 0);
//	//glEnd();
//	
//	
//	//Matrix Stacks
//
//	//draw 2 points
//
//	//glMatrixMode(GL_MODELVIEW);
//
//	//glPushMatrix();
//	//	glTranslatef(0.5, 0.0, 0.0);
//	//	glBegin(GL_POINTS);
//	//		glVertex2f(0, 0);
//	//	glEnd();
//	//glPopMatrix();
//	//	
//	//glPushMatrix();
//	//	glTranslatef(0, 0.5, 0.0);
//	//	glBegin(GL_POINTS);
//	//		glVertex2f(0, 0);
//	//	glEnd();
//	//glPopMatrix();
//
//
//	//glPushMatrix();
//	//glRotatef(45, 0, 0, 1);
//	//glTranslatef(-0.5, 0.0, 0.0);
//	//mySquare();
//	//
//	//glPushMatrix();
//	//glRotatef(45, 0, 0, 1);
//	//glTranslatef(0.5, 0.0, 0.0);
//	//mySquare();
//
//	//glPopMatrix();
//	//glPopMatrix();
//
//	
//	
//	glClear(GL_COLOR_BUFFER_BIT);
//	glTranslatef(0.001, 0, 0);
//	glPushMatrix();
//	glRotatef(i, 0, 0, 1);
//	mySquare();
//	glPopMatrix();
//
//	i++;
//
//
//	//--------------------------------
//	//	End of OpenGL drawing
//	//--------------------------------
//}
////--------------------------------------------------------------------




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
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
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

