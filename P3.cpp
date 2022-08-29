
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>
#include "Circle.cpp"
#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical 3"

//Question No
int qNo = 1;

//Exercise 1 propertise
float tx = 0, ty = 0;
float tSpeed = 0.1;

//Exercise 2 Windmill Propertise
int bladeCount = 4;
float rAngle = 0; // windmill rotating angle
float rSpeed = 0.1; //windmill rotate speed
float tempSpeed = 0;

//Weather propertise
bool morning = true;

//Cloud propertise
float cloudT = 0.0;
float cloudTSpeed = 0.0001;

//Stickman propertise
float stickT = -1.5;
float stickWalkTSpeed = 0.0001;
float stickY = -0.4;
float stickFloatTSpeed = 0.001;
bool drawStick = true;

//UFO Propertise
float ufoAngle = 0;
float ufoXT = 0;
float ufoYT = 2.0;
float ufoFlyingSpeed = 0.01;
bool shootRay = false;



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
		else if (wParam == VK_LEFT) tx -= tSpeed ;
		else if (wParam == VK_RIGHT) tx += tSpeed;
		else if (wParam == VK_UP) ty += tSpeed;
		else if (wParam == VK_DOWN) ty -= tSpeed;
		else if (wParam == VK_F1) {
			drawStick = true;
			morning = !morning;
			stickT = -1.5;
			stickY = -0.4;
			ufoXT = 0;
			ufoYT = 2;
			ufoAngle = 0;
		}
		else if (wParam == 0x57) rSpeed += 0.01;
		else if (wParam == 0x53) rSpeed -= 0.01;
		else if (wParam == 0x42) bladeCount = bladeCount == 8 ? 4 : 8;
		else if (VK_SPACE) {
			tempSpeed = rSpeed > 0 ? rSpeed : tempSpeed;
			rSpeed = rSpeed == 0.0 ? tempSpeed : 0.0;
			tx = 0;
			ty = 0;
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

void sample() {
	glPushMatrix(); 
	{
		glScalef(0.5, 0.5, 1);

		glPushMatrix();
		{
			glTranslatef(0.5, 0.0, 0.0);
			glBegin(GL_TRIANGLES);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(-0.5, 0.0);
			glVertex2f(0.0, 0.5);
			glVertex2f(0.5, 0.0);
			glEnd();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glRotatef(90, 0.0, 0.0, 1.0);

			glPushMatrix();
			{
				glTranslatef(-0.5, 0.0, 0.0);
				glBegin(GL_QUADS);
				glColor3f(0.0, 1.0, 0.0);
				glVertex2f(-0.5, 0.0);
				glVertex2f(-0.5, 0.5);
				glVertex2f(0.5, 0.5);
				glVertex2f(0.5, 0.0);
				glEnd();
			}
			glPopMatrix();

			glPushMatrix();
			{
				glTranslatef(0.0, 0.5, 0.0);
				glBegin(GL_TRIANGLES);
				glColor3f(0.0, 0.0, 1.0);
				glVertex2f(-0.5, 0.0);
				glVertex2f(0.0, 0.5);
				glVertex2f(0.5, 0.0);
				glEnd();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void exercise3a() {
	glLoadIdentity();
	glClearColor(0, 0, 0,0);
	glScalef(0.5, 0.5, 0);

	glPushMatrix();
	{
		glTranslatef(-tx, -ty, 0);
		glBegin(GL_QUADS); //1st quard
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0.5, 0);
		glVertex3f(1, 0.5, 0);
		glVertex3f(1, 0, 0);
		glEnd();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(tx, ty, 0);
		glBegin(GL_QUADS); //2nd quard
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0.5, 0);
		glVertex3f(1, 0.5, 0);
		glVertex3f(1, 0, 0);
		glEnd();
	}
	glPopMatrix();
}


float bladeAngle = 0;
float rTest = 0;
void drawCircleFilled(Circle* circle) {

	RGBColor* color = circle->color;
	glColor3f(color->r, color->g, color->b);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(circle->x, circle->y);
	for (float angle = circle->startingAngle; angle <= circle->endingAngle; angle += (2 * circle->PI) / circle->noOfTri) {
		circle->x2 = circle->x + circle->r * cos(angle);
		circle->y2 = circle->y + circle->r * sin(angle);
		glVertex2f(circle->x2, circle->y2);
	}
	glEnd();

}

void drawCircleNotFilled(Circle* circle) {

	RGBColor* color = circle->color;
	glColor3f(color->r, color->g, color->b);
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	//glVertex2f(circle->x, circle->y);
	for (float angle = circle->startingAngle; angle <= circle->endingAngle; angle += (2 * circle->PI) / circle->noOfTri) {
		circle->x2 = circle->x + circle->r * cos(angle);
		circle->y2 = circle->y + circle->r * sin(angle);
		glVertex2f(circle->x2, circle->y2);
	}
	glEnd();
}

void drawBlade() {
	
	for (bladeAngle; bladeAngle <= 360; bladeAngle += (360 / bladeCount) ){
		glColor3f(1, 1, 1);
		glRotatef(bladeAngle, 0, 0, 1);
		glBegin(GL_QUADS);
		glVertex2f(0.5, 0.0);
		glVertex2f(1.3, 0.0);
		glVertex2f(1.3, -0.2);
		glVertex2f(0.5, -0.2);
		glEnd();

		RGBColor brown = RGBColor(147, 99, 65);
		glLineWidth(5);
		glColor3f(brown.r, brown.g, brown.b);
		glBegin(GL_LINES);
		glVertex2f(1.3, 0.0);
		glVertex2f(0, 0.0);
		glEnd();
	}

	if (rTest > 360)
		rTest = 0;

	rTest += 0.1;
	bladeAngle = 0;


	//2
}

void drawWindmillTower() {

	RGBColor grey = RGBColor(146, 140, 135);
	glColor3f(grey.r, grey.g, grey.b);
	glBegin(GL_QUADS);
	glVertex3f(-0.2, 0.8, 0);
	glVertex3f(0.2, 0.8, 0); //right 0.2 unit
	glVertex3f(0.4, 0.6, 0); //right and go down 0.2 unit
	glVertex3f(-0.4, 0.6, 0); // last point;
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(-0.4, 0.6, 0);
	glVertex3f(0.4, 0.6, 0); // go right 0.8 unit
	glVertex3f(0.8, -1.5, 0);
	glVertex3f(-0.8, -1.5, 0);
	glEnd();

}

void drawWindow() {


	glColor3f(0, 0, 0);
	glTranslatef(-0.15, 0.0, 0);
	glBegin(GL_QUADS);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.3, 0.0);
		glVertex2f(0.3, -0.5);
		glVertex2f(0.0, -0.5);
	glEnd();

}

void drawSun() {

	RGBColor orange = RGBColor(255, 204, 1);
	//draw orange circle
	Circle sunCircle = Circle(2.0,2.0, 0.5, &orange, 0, 360);
	drawCircleFilled(&sunCircle);
	//draw the triangle

	//2.7,2
	//upper point - 2.7, 2.2
	//lower point - 2.7, 1.8
	//loop the angles

	for (float rTriangle = 180; rTriangle <= 270; rTriangle += 45.0) {
		glPushMatrix(); {
			glColor3f(orange.r, orange.g, orange.b);
			glTranslatef(2.0, 2.0, 0);
			glRotatef(rTriangle, 0, 0, 1);
			glBegin(GL_TRIANGLES);
			glVertex2f(0.7, 0.2);
			glVertex2f(0.7, -0.2);
			glVertex2f(0.9, 0);
			glEnd();
		}
		glPopMatrix();
	}
}

void drawCloud() {

	RGBColor white = RGBColor(255, 255, 255);
	Circle circle1 = Circle(0, 0, 0.2, &white, 0, 180);
	Circle circle2 = Circle(0, 0, 0.3, &white, 0, 180);
	
	glPushMatrix();
	{
		glTranslatef(-0.8, 1.5, 0);
		drawCircleFilled(&circle1);
	}
	glPopMatrix();
	glPushMatrix(); 
	{
		glTranslatef(-0.5, 1.5, 0);
		drawCircleFilled(&circle2);
	}
	glPopMatrix();
	glPushMatrix(); 
	{
		glTranslatef(-0.2, 1.5, 0);
		drawCircleFilled(&circle1);
	}
	glPopMatrix();

}

void drawMoon() {

	RGBColor moonColor = RGBColor(249, 225, 77);
	RGBColor nightColor = RGBColor(14, 58, 119);
	Circle biggerPortion = Circle(0, 0, 0.5, &moonColor, 0, 360);
	Circle smallerPortion = Circle(0, 0, 0.3, &nightColor, 0, 360);
	
	glPushMatrix(); 
	{
		glTranslatef(1.5, 1.5, 0);
		drawCircleFilled(&biggerPortion);
	}
	glPopMatrix();

	glPushMatrix(); 
	{
		glTranslatef(1.25, 1.5, 0);
		drawCircleFilled(&smallerPortion);
	}
	glPopMatrix();
}

void drawStickMan() {
	
	glPushMatrix(); 
	{
		//draw head
		glTranslatef(0, 0.5, 0);
		Circle head = Circle(0, 0, 0.2, &RGBColor(0, 0, 0), 0, 360);
		drawCircleNotFilled(&head);
	}
	glPopMatrix();

	//draw body
	glPushMatrix(); 
	{
		glBegin(GL_LINES);
		glVertex2f(0.0, 0.3);
		glVertex2f(0.0, -0.5);
		glEnd();
	}
	glPopMatrix();

	//draw hand
	glPushMatrix(); 
	{
		glPushMatrix();
		{
			glRotatef(330, 0, 0, 1);
			glBegin(GL_LINES);
			glVertex2f(0.0, 0.0);
			glVertex2f(0.3, 0.0);
			glEnd();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glRotatef(210, 0, 0, 1);
			glBegin(GL_LINES);
			glVertex2f(0.0, 0.0);
			glVertex2f(0.3, 0.0);
			glEnd();
		}
		glPopMatrix();
	}
	glPopMatrix();
	
	//draw leg
	glPushMatrix(); 
	{
		glTranslatef(0, -0.5, 0);
		//left leg
		glPushMatrix();
		{
			glRotatef(330, 0, 0, 1);
			glBegin(GL_LINES);
			glVertex2f(0.0, 0.0);
			glVertex2f(0.3, 0.0);
			glEnd();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glRotatef(210, 0, 0, 1);
			glBegin(GL_LINES);
			glVertex2f(0.0, 0.0);
			glVertex2f(0.3, 0.0);
			glEnd();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawUFO() {
	
	RGBColor ufoBlue = RGBColor(128, 215, 222);
	RGBColor ufoDarkBlue = RGBColor(64, 72, 75);
	Circle upperCircle = Circle(0, 0, 0.3, &ufoBlue, 0, 360);
	drawCircleFilled(&upperCircle);
	Circle lowerHalfCircle = Circle(0, 0, 0.5, &ufoDarkBlue, 180, 360);
	drawCircleFilled(&lowerHalfCircle);
}

void drawYellowRay() {
	
	glColor3f(1, 1, 0);
	glBegin(GL_QUADS);
		glVertex2f(-0.2, 1);
		glVertex2f(0.2, 1);
		glVertex2f(0.4, -0.8);
		glVertex2f(-0.4, -0.8);
	glEnd();

}

void exercise3b() {

	if (morning) {
		RGBColor skyColor = RGBColor(153, 206, 213);
		glClearColor(skyColor.r, skyColor.g, skyColor.b, 0);

		//draw sun
		glPushMatrix(); 
		{
			drawSun();
		}
		glPopMatrix();

		//draw the cloud
		glPushMatrix(); 
		{

			glTranslatef(cloudT, 0, 0);

			glPushMatrix(); 
			{
				drawCloud();
			}
			glPopMatrix();

			glPushMatrix(); 
			{
				glTranslatef(-1.5, -0.5, 0);
				drawCloud();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	else {
		RGBColor nightColor = RGBColor(14, 58, 119);
		glClearColor(nightColor.r, nightColor.g, nightColor.b, 0);
		drawMoon();

		if (shootRay)
			drawYellowRay();

		glPushMatrix(); 
		{
			glScalef(0.5, 0.5, 0);
			glTranslatef(ufoXT, ufoYT, 0);
			glRotatef(ufoAngle, 0, 0, 1);
			drawUFO();
		}
		glPopMatrix();

		if (drawStick) {
			glPushMatrix(); 
			{
				glTranslatef(stickT, stickY, 0);
				glScalef(0.3, 0.3, 0.0);
				drawStickMan();
			}
			glPopMatrix();
		}

		if (stickT >= 0) {
			stickY += stickFloatTSpeed;
			shootRay = true;

			if (stickY > 1) {
				drawStick = false;	
				ufoAngle = 30;
				ufoXT += ufoFlyingSpeed;
				ufoYT += ufoFlyingSpeed;
				shootRay = false;
			}

		}
		else {
			stickT += stickWalkTSpeed;
		}
	}
	//draw land
	glPushMatrix(); 
	{
		RGBColor grassColor = RGBColor(128, 187, 59);
		glColor3f(grassColor.r, grassColor.g, grassColor.b);

		glBegin(GL_QUADS);
		glVertex3f(-5, -0.6, 0);
		glVertex3f(5, -0.6, 0);
		glVertex3f(5, -5, 0);
		glVertex3f(-5, -5, 0);
		glEnd();
	}
	glPopMatrix();

	//draw the road between the windmill
	glPushMatrix(); 
	{
		glTranslatef(0, -0.6, 0);
		RGBColor roadBrown = RGBColor(36, 20, 4);
		glColor3f(roadBrown.r, roadBrown.g, roadBrown.b);
		glBegin(GL_QUADS);
		glVertex2f(-1.8, 0);
		glVertex2f(1.8, 0);
		glVertex2f(1.8, -0.1);
		glVertex2f(-1.8, -0.1);
		glEnd();
	}
	glPopMatrix();

	//Windmill 1
	glPushMatrix(); 
	{
		glTranslatef(-1.5, 0.0, 0);
		glScalef(0.5, 0.5, 0);
		drawWindmillTower();

		glPushMatrix();
		{
			drawWindow();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0, 0.6, 0);
			glRotatef(rAngle, 0, 0, 1);
			drawBlade();
		}
		glPopMatrix();
	}
	glPopMatrix();

	//Windmill 2
	glPushMatrix(); 
	{
		glTranslatef(1.5, 0.0, 0);
		glScalef(0.5, 0.5, 0);
		drawWindmillTower();

		glPushMatrix(); 
		{
			drawWindow();
		}
		glPopMatrix();

		glPushMatrix(); 
		{
			glTranslatef(0, 0.6, 0);
			glRotatef(rAngle, 0, 0, 1);
			drawBlade();
		}
		glPopMatrix();
	}
	glPopMatrix();

	rAngle += rSpeed;
	cloudT += cloudTSpeed;

	if (cloudT > 5)
		cloudT = 0;
}

void display() {

	//glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);

	switch (qNo) {
		case 1:
			exercise3a();
			break;
		case 2:
			exercise3b();
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

