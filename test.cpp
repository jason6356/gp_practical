#include <Windows.h>
#include <Math.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#pragma comment (lib, "OpenGL32.lib")
#define WINDOW_TITLE "Practical 6"

int qNo = 1;
float tx = 0, tz = 0, tSpeed = 1.0;			//translate for modelview
bool isOrtho = true;						//is Orthographic view
float ONear = -10.0, OFar = 10.0;			//Ortho near and far
float PNear = 1.0, PFar = 21.0;				//Perspective near and far
//Only will do for tx, ty for translation and ry for rotation 
float ptx = 0.0, pty = 0.0, ptSpeed = 0.1;	//translate for projection
float pRy = 0.0, prSpeed = 1.0;				//rotation y aixs for projection
float speed = 2.0;

float rotate = 0.0;
// Lighting
float amb[3] = { 1.0, 1.0, 1.0 };		// Red color  --> Ambient light - 3 indicates the 3 rgb value 
float posA[3] = { 0.0, 6.0, 0.0 };		// light position (0, 6, 0) --> x, y, z -axis --> light source is on top of the sphere
float dif[3] = { 1.0, 1.0, 1.0 };		// Green color --> Diffuse light - 3 indicates the 3 rgb value
float posD[3] = { 6.0, 0.0, 0.0 };		// light position (6, 0, 0) --> light source is on right side of the sphere
float ambM[3] = { 0.0, 0.0, 1.0 };		// Blue color ambient material 
float difM[3] = { 1.0, 0.0, 0.0 };		// Blue color diffuse material

bool isLightOn = false;					// is Light on?
bool isSphere = true;

//Event Listener
LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
		//Pause Button
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		//Key Down
	case WM_KEYDOWN:
		//Esc Button
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		else if (wParam == 0x31)
			qNo = 1;
		else if (wParam == 0x32) qNo = 2;

		if (qNo == 1) {
			if (wParam == VK_SPACE) {		// Space Key --> Switch off or on the light
				isLightOn = !isLightOn;
			}
			else if (wParam == 0x57) {		// Key "W" --> Move the light positon up (y-axis)
				posD[1] += speed;
			}
			else if (wParam == 0x53) {		// Key "S" --> Move the light position down (y-axis)
				posD[1] -= speed;
			}
			else if (wParam == 0x41) {		// Key "A" --> Move the light position left (x-axis)
				posD[0] -= speed;
			}
			else if (wParam == 0x44) {		// Key "D" --> Move the light position right (x-axis)
				posD[0] += speed;
			}
			else if (wParam == 0x45) {		// Key "E" --> Move the light position near (z-axis)
				posD[2] += speed;
			}
			else if (wParam == 0x51) {		// Key "Q" --> Move the light postion far (z-axis)
				posD[2] -= speed;
			}
			else if (wParam == VK_UP) {		// Key Up --> Rotate clock-wise at all-axis
				rotate += speed;

			}
			else if (wParam == VK_DOWN) {	// Key Down --> Rotate anticlock-wise at all-axis
				rotate -= speed;
			}
			else if (wParam == 0x4F) {		// Key "O" --> Switch polygon to sphere
				isSphere = true;
			}
			else if (wParam == 0x50) {		// Key "P" --> Switch polygon to pyramid
				isSphere = false;
			}
		}
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	//Specfic Bits for drawing
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

void drawSphere(double r) {
	glPointSize(3.0);
	glRotatef(0.1, 1.0, 1.0, 1.0);
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	//gluQuadricDrawStyle(sphere, GLU_LINE);
	gluSphere(sphere, r, 30, 30);
	gluDeleteQuadric(sphere);
}

void drawCylinder(double br, double tr, double h) {

	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL); // gl Point , fill , line
	gluCylinder(cylinder, br, tr, h, 4, 4);
	gluDeleteQuadric(cylinder);

}

void drawPyramid(float sz) {
	//glBegin(GL_TRIANGLES);
	//glVertex3f(0.0f, sz, 0.0f);
	//glVertex3f(-sz, -sz, -sz);
	//glVertex3f(sz, -sz, -sz);

	//glVertex3f(0.0f, sz, 0.0f);
	//glVertex3f(-sz, -sz, sz);
	//glVertex3f(sz, -sz, sz);

	//glVertex3f(0.0f, sz, 0.0f);
	//glVertex3f(-sz, -sz, sz);
	//glVertex3f(-sz, -sz, -sz);

	//glVertex3f(0.0f, sz, 0.0f);
	//glVertex3f(sz, -sz, sz);
	//glVertex3f(sz, -sz, -sz);
	//glEnd();

	//glBegin(GL_QUADS);
	//glVertex3f(-sz, -sz, sz);
	//glVertex3f(-sz, -sz, -sz);
	//glVertex3f(sz, -sz, -sz);
	//glVertex3f(sz, -sz, sz);
	//glEnd();
	// Draw Pyramid by using Cylinder (without covering bottom)
	drawCylinder(0.0, sz, sz);
}

void projection() {
	//adjust the perspective view of object [only for orthographic perspective]
	glMatrixMode(GL_PROJECTION);		//refer to projection matrix
	glLoadIdentity();						//reset projection matrix

	glTranslatef(ptx, pty, 0.0);			//translate for projection
	glRotatef(pRy, 0.0, 1.0, 0.0);			//rotate along the y axis for projection
	if (isOrtho) {
		////only for orthographic projection
		glOrtho(-10.0, 10.0, -10.0, 10.0, ONear, OFar);
	}
	else {
		////only for perspective projection
		gluPerspective(20, 1, -1, 1);
		//Limit the max and min size
		glFrustum(-10.0, 10.0, -10.0, 10.0, PNear, PFar);
	}

}

void lighting() {
	if (isLightOn) {
		glEnable(GL_LIGHTING);		// turn on lighting for the whole scene
	}
	else {
		glDisable(GL_LIGHTING);
	}

	// Light 0 : Red color ambient light at position (0, 6, 0) above sphere
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	// Set the properties of GL_POSITION for GL_LIGHT0
	// By default the light source is from the centre - origin (0, 0)
	glLightfv(GL_LIGHT0, GL_POSITION, posA);
	//glEnable(GL_LIGHT0);

	// Light 1 : Green color diffuse light at position (6, 0, 0) right side of the sphere
	glLightfv(GL_LIGHT1, GL_DIFFUSE, dif);
	// Set the properties of GL_POSITION for GL_LIGHT0
	glLightfv(GL_LIGHT1, GL_POSITION, posD);
	glEnable(GL_LIGHT1);
}

void P6Demo() {

	//projection();

	lighting();

	////FIRST method : just assign at display without using switch
	//-----------------------------------------------------------------------------------------------------
	glMatrixMode(GL_MODELVIEW);		// refer to modelview
	glLoadIdentity();				// reset modelview matrix
	//translate along z-axis and will disappear once clicking 3 time and is based on the glOrtho
	//glTranslatef(tx, 0.0, tz);		// translate the model
	//if radius = tSpeed, will not become bigger or smaller and only will disappear
	// There is no blue color at all because after enable lighting glColor3f will no longer working anymore
	glColor3f(0.0, 0.0, 1.0);		// blue color for sphere
	// To solve this problem, replace with glMaterial
	//if() {
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambM);	// red color ambient material
	// } else {
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, difM);	// red color diffuse material
	// }
	drawSphere(3.0);
	//-----------------------------------------------------------------------------------------------------
}

void Q1() {
	lighting();

	projection();
	////FIRST method : just assign at display without using switch
	//-----------------------------------------------------------------------------------------------------
	glMatrixMode(GL_MODELVIEW);		// refer to modelview
	glLoadIdentity();				// reset modelview matrix

	glRotatef(rotate, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);		// black color for sphere
	glMaterialfv(GL_FRONT, GL_DIFFUSE, difM);	// red color diffuse material
	if (isSphere) {
		drawSphere(3.0);
	}
	else {
		drawPyramid(3.0);
	}
	//-----------------------------------------------------------------------------------------------------
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear screen
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	switch (qNo) {
	case 1:
		Q1();
		break;
	default:
		P6Demo();
		break;
		// display something else
	}
}


//--------------------------------------------------------------------

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

	//Window Detail Configuration
	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		//Resolution	           Height, Width
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,

		//400:300 flat rectangle size

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
	//fps (Depends on Graphic Card)

	////adjust the perspective view of object [only for orthographic perspective]
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	//////only for orthographic projection
	////glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0); 
	//// 
	//////only for perspective projection
	//gluPerspective(20, 1, -1, 1);
	//glFrustum(-10.0, 10.0, -10.0, 10.0, 1.0, 21.0);

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
