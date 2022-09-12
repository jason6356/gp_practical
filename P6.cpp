
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>
#include <gl/GLU.h>
#pragma comment (lib, "OpenGL32.lib")
#define WINDOW_TITLE "Practical 5"

/*
* Projection Settings
*/
bool isOrtho = true; //is Orthographic

/*
	Z Axis Object
*/
float zCord = 0; // Z axis for the object in the model view
const float oFar = 10.0;
const float oNear = -10.0;
//Perspective Near Far
const float pNear = 1.0;
const float pFar = 21.0;

float pTx = 0.0;
float pTy = 0.0;


float PRangle = 0.0;

//orgin
float x = 0.15, y = 0;
//radius
float r = 0.2;
float angle = 0.0;

float noOfTri = 1000;
float x2 = 0, y2 = 0;
float PI = 3.1429;

int qNo = 6;

//Translatetion
float tx = 0, ty = 0;
float tz = 0.0;
float tSpeed = 0.5;

//change color
float red = 1;
float green = 0;
float blue = 0;

//rotation for the arm
float rAngle = 0.0;
float rSpeed = 0.5;

//rotation for the entire arm
float zArm = 0.0;
float xArm = 0.0;
float yArm = 0.0;


//Intensity of the light source 
float amb[3] = { 1.0,0.0,0.0 }; //Red Color ambient light
float posA[3] = { 0.0,6.0,0.0 }; //Ambient Pos


//Practical Need
float posD[3] = { 6.0,0.0,0.0 }; //Diffuse Pos
float dif[3] = { 1.0,0.0,0.0 }; // Red Color diffuse light


//material color
float ambM[3] = { 0.0,0.0,0.0 }; //;Red Color ambient material
float difM[3] = { 1.0,1.0,1.0 }; // White color diffuse material
boolean isAmb = false;

boolean isSphere = false;


/*
 * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
 * 0x3A - 0x40 : unassigned
 * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
 */
void yAxisRotate() {
	float xOld, yOld, zOld;
	xOld = posD[0];
	yOld = posD[1];
	zOld = posD[2];
	posD[0] = zOld * sin(angle) + xOld * cos(angle);
	posD[1] = posD[1];
	posD[2] = yOld * cos(angle) - xOld * sin(angle);
}

void xAxisRotate() {
	float xOld, yOld, zOld;
	xOld = posD[0];
	yOld = posD[1];
	zOld = posD[2];
	posD[0] = xOld;
	posD[1] = yOld * cos(angle) - zOld * sin(angle);
	posD[2] = yOld * sin(angle) + zOld * cos(angle);
}

void zAxisRotate() {
	float xOld, yOld, zOld;
	xOld = posD[0];
	yOld = posD[1];
	zOld = posD[2];
	posD[0] = xOld * cos(angle) - yOld * sin(angle);
	posD[1] = xOld * sin(angle) + yOld * cos(angle);
	posD[2] = zOld;
}


LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == 'W') posD[1] += tSpeed;
		else if (wParam == 'S') posD[1] -= tSpeed;
		else if (wParam == 'A') posD[0] -= tSpeed;
		else if (wParam == 'D') posD[0] += tSpeed;
		else if (wParam == 'E') posD[2] += tSpeed;
		else if (wParam == 'Q') posD[2] -= tSpeed;
		else if (wParam == VK_UP) {
			xAxisRotate();
			yAxisRotate();
			zAxisRotate();
			angle = 2 * PI / 100;
		}
		else if (wParam == VK_DOWN) {
			xAxisRotate();
			yAxisRotate();
			zAxisRotate();
			angle = -(2 * PI / 100);
		}
		else if (wParam == VK_SPACE) {
			posD[0] = 6.0;
			posD[1] = 0.0;
			posD[2] = 0.0;

		}
		else if (wParam == 'P')
			isSphere = ~isSphere;
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

void drawSphere(float r, float sl, float st) {
	GLUquadricObj* sphere = NULL;			//create quadric obj pointer
	sphere = gluNewQuadric();				//create the quadric obj
	gluQuadricDrawStyle(sphere, GLU_FILL);	//set the draw style
	gluSphere(sphere, r, sl, st);			//draw sphere
	gluDeleteQuadric(sphere);				//delete the quadric obj
}


void drawCone(float r, float h) {
	GLUquadricObj* cylinder = NULL;				//create quadric obj pointer
	cylinder = gluNewQuadric();					//create the quadric obj
	//gluQuadricDrawStyle(cylinder, GLU_FILL);	//set the draw style
	gluCylinder(cylinder, 0.0, r, h, 30, 30);	//draw cone
	gluDeleteQuadric(cylinder);					//delete the quadric obj
}

void drawConeLine(float r, float h) {
	GLUquadricObj* cylinder = NULL;				//create quadric obj pointer
	cylinder = gluNewQuadric();					//create the quadric obj
	gluQuadricDrawStyle(cylinder, GLU_LINE);	//set the draw style
	gluCylinder(cylinder, 0.0, r, h, 20, 10);	//draw cone
	gluDeleteQuadric(cylinder);					//delete the quadric obj
	glLineWidth(3.0);
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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glTranslatef(pTx, pTy, 0);
	glRotatef(PRangle, 0, 1, 0);

	if (isOrtho) {
		glOrtho(-10.0, 10.0, -10.0, 10.0, oNear, oFar);
	}
	else {
		gluPerspective(20, 1.0, -1.0, 1.0);
		glFrustum(-10, 10.0, -10.0, 10.0, pNear, pFar);
	}
	//PRangle += 0.1;
}

void lightning() {
	glEnable(GL_LIGHTING); // turn on lighting for the whole scene
	glPushMatrix();
	glTranslatef(tx, ty, tz);
		if (isAmb) {
			glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
			glLightfv(GL_LIGHT0, GL_POSITION, posA);
			glEnable(GL_LIGHT0);
		}
		else {
			glLightfv(GL_LIGHT1, GL_DIFFUSE, dif);
			glLightfv(GL_LIGHT1, GL_POSITION, posD);
			glEnable(GL_LIGHT1);
		}
	glPopMatrix();
}

void display() {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 0);

	projection(); //projection
	lightning(); //lightning

	//translation -> tx tx
	//rotation -> ry

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glPushMatrix();
	{
		glTranslatef(0, 0, zCord);
		//glColor3f(0, 0, 1.0);
		if (isAmb) {
			glMaterialfv(GL_FRONT, GL_AMBIENT, ambM);
		}
		else {
			glMaterialfv(GL_FRONT, GL_DIFFUSE, difM);

		}

		glPushMatrix();
			glColor3f(1, 0, 0);
			glTranslatef(posD[0], posD[1], posD[2]);
			drawCube(0.5);
		glPopMatrix();
		if(isSphere)
			drawSphere(3, 100, 100);
		else {
			glPushMatrix();
			glRotatef(90, 1, 0, 1);
			drawPyramid(3.0);
			glPopMatrix();
		}
	}
	glPopMatrix();
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