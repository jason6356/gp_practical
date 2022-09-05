  
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>
#include <gl/GLU.h>
#include "RGBColor.cpp"
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
float angle = 0;

float noOfTri = 1000;
float x2 = 0, y2 = 0;
float PI = 3.1429;

int qNo = 6;

//Translatetion
float tx = 0, ty = 0;
float tSpeed = 0.1;

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

RGBColor colors[] = {
	RGBColor(255,0,0),
	RGBColor(255,165,0),
	RGBColor(255,255,0),
	RGBColor(0,128,0),
	RGBColor(0,0,255),
	RGBColor(255,0,255),
	RGBColor(128,0,128),
};



//Intensity of the light source 
float amb[3] = { 1.0,0.0,0.0 }; //Red Color ambient light
float posA[3] = { 0.0,6.0,0.0 }; //Ambient Pos
float posD[3] = { 6.0,0.0,0.0 }; //Diffuse Pos
float dif[3] = { 1.0,1.0,1.0 }; // Green Color diffuse light
bool isLightOn = false;



//material color
float ambM[3] = { 0.0,0.0,1.0 }; //;Red Color ambient material
float difM[3] = { 0.0,0.0,1.0 }; // Red color diffuse material
boolean isAmb = true;


//Step 1 : Variable declaration
GLuint texture = 0;  //texture name
BITMAP BMP;			 //bitmap structure
HBITMAP hBMP = NULL; //bitmap handle

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
		else if (wParam == VK_LEFT) {
			tx -= tSpeed;
			pTx -= tSpeed;
		}
		else if (wParam == VK_RIGHT) {
			tx += tSpeed;
			pTx += tSpeed;
		}
		else if (wParam == VK_UP) {

			rAngle += rSpeed;

			if (isOrtho) {
				if (zCord < oFar)
					zCord += tSpeed;
			}
			else
				if (zCord < pFar / 2)
					zCord += tSpeed;
		}
		else if (wParam == VK_DOWN) {
			rAngle -= rSpeed;
			if (isOrtho) {
				if (zCord > oNear)
					zCord -= tSpeed;
			}
			else
				if (zCord > pNear)
					zCord -= tSpeed;
		}
		else if (wParam == VK_LEFT) xArm += rSpeed;
		else if (wParam == VK_RIGHT) xArm -= rSpeed;
		else if (wParam == 'O') {
			isOrtho = true;
			zCord = 0;
		}
		else if (wParam == 'P') {
			isOrtho = false;
			zCord = 0;
		}
		else if (wParam == 'D') {
			PRangle += 1;
		}
		else if (wParam == 'A') {
			PRangle -= 1;
		}
		else if (wParam == VK_SPACE) {
			//isAmb = !isAmb;
			isLightOn = !isLightOn;
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

void drawQuads(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4)
{
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(x1, y1, z1);
	glTexCoord2f(1, 1);
	glVertex3f(x2, y2, z2);
	glTexCoord2f(1, 0);
	glVertex3f(x3, y3, z3);
	glTexCoord2f(0, 0);
	glVertex3f(x4, y4, z4);
	glEnd();
}

void drawCube(float length, float height, float width)
{
	float x = length / 2;
	float y = height / 2;
	float z = width / 2;
	drawQuads(-x, y, -z, x, y, -z, x, -y, -z, -x, -y, -z); // front side
	drawQuads(-x, y, z, x, y, z, x, -y, z, -x, -y, z);	   // back side
	drawQuads(-x, y, z, -x, y, -z, -x, -y, -z, -x, -y, z); // left side
	drawQuads(x, y, -z, x, y, z, x, -y, z, x, -y, -z);	   // right side
	drawQuads(-x, y, z, x, y, z, x, y, -z, -x, y, -z);	   // top
	drawQuads(-x, -y, z, x, -y, z, x, -y, -z, -x, -y, -z); // btm
}

void drawCube(float sz) {

	glBegin(GL_QUADS);
	// Face 1
	glColor3f(1, 0, 0);
	glTexCoord2f(0.0, 0.5);
	glVertex3f(0.0f, 0.0f, sz);
	glTexCoord2f(0.5,0.5);
	glVertex3f(sz, 0.0f, sz);
	glTexCoord2f(0.5, 0.0);
	glVertex3f(sz, 0.0f, 0.0f);
	glTexCoord2f(0.0, 0.0);
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

void drawCylinder(double br, double tr, double h) {
	GLUquadricObj* var = NULL;

	var = gluNewQuadric();

	//glColor3f(0, 0, 1);
	glRotatef(0.01, 1, 1, 1);
	gluQuadricDrawStyle(var, GLU_LINE);
	gluCylinder(var, br, tr, h, 30, 30);
	gluDeleteQuadric(var);

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

void drawGluCylinder(float tr, float br, float h) {
	GLUquadricObj* cylinder = NULL;			//create quadric obj pointer
	cylinder = gluNewQuadric();				//create the quadric obj
	gluQuadricDrawStyle(cylinder, GLU_LINE);	//set the draw style
	gluCylinder(cylinder, tr, br, h, 30, 2);			//draw sphere
	gluDeleteQuadric(cylinder);				//delete the quadric obj
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "Box.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);



	glRotatef(0.5, 0.1, 0.1, 0.1);

	drawCube(0.5,0.5,0.5);

	glDisable(GL_TEXTURE_2D);

	DeleteObject(hBMP);

	glDeleteTextures(1, &texture);

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
