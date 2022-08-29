#include <Windows.h>
#include <gl/GL.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical 1"

//Lazy RGB Code for calculation
class RGBColor {

public:
	float r,g,b;
	RGBColor(float r, float g, float b) {
		this->r = r / 255;
		this->g = g / 255;
		this->b = b / 255;
	}
};

RGBColor backgroundColor = RGBColor(240, 128, 128);
int qNo = 1;

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
void pahangFlag() {

	//top white rectangle
	glBegin(GL_QUADS);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(-0.5, 0); //p1
		glVertex2f(-0.5, 0.5); 
		glVertex2f(0.8, 0.5);
		glVertex2f(0.8, 0);
	glEnd();

	//bottom black rectangle
	glBegin(GL_QUADS);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2f(-0.5, 0);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.8, -0.5);
		glVertex2f(0.8, 0);
	glEnd();
}

void n9Flag() {

	glBegin(GL_QUADS);
	//set colour of the current shape
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.8, 0.5);
	glVertex2f(0.8, -0.5);
	glVertex2f(-0.5, -0.5);
	glEnd();


	//red triangle
	glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.1, 0.5);
		glVertex2f(0.1, 0);
	glEnd();

	RGBColor brown = RGBColor(44, 5, 4);

	//brown triangle
	glBegin(GL_TRIANGLES);
		glColor3f(brown.r, brown.g, brown.b);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.1, 0);
		glVertex2f(-0.5, 0);
	glEnd();


}

void englandFlag() {

	//color configuration , auto convert normal rgb into float rgb 
	RGBColor grey = RGBColor(195, 195, 195);
	RGBColor shadeRed = RGBColor(120, 1, 1);
	RGBColor red = RGBColor(145, 1, 1);

	//top left white rectangle
	glShadeModel(GL_SMOOTH);
	glBegin(GL_POLYGON);
		glColor3f(grey.r, grey.g, grey.b);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.0, 0.5);
		glColor3f(1, 1, 1);
		glVertex2f(0, 0.1);
		glColor3f(grey.r, grey.g, grey.b);
		glVertex2f(-0.5, 0.1);
	glEnd();

	//red rectangle
	glShadeModel(GL_SMOOTH);
		glBegin(GL_QUADS);
		glColor3f(shadeRed.r,shadeRed.g,shadeRed.b);
		glVertex2f(0.0, 0.5);
		glVertex2f(0.3, 0.5);
		glColor3f(red.r, red.g, red.b);
		glVertex2f(0.3, 0.1);
		glVertex2f(0.0, 0.1);
	glEnd();

	//top right white rectangle

	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
		glColor3f(grey.r, grey.g, grey.b);
		glVertex2f(0.3, 0.5);
		glVertex2f(0.8, 0.5);
		glVertex2f(0.8, 0.1);
		glColor3f(1, 1, 1);
		glVertex2f(0.3, 0.1);
	glEnd();

	//middle left red

	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
		glColor3f(shadeRed.r, shadeRed.g, shadeRed.b);
		glVertex2f(-0.5, 0.1);
		glColor3f(red.r, red.g, red.b);
		glVertex2f(0, 0.1);
		glVertex2f(0, -0.1);
		glColor3f(shadeRed.r, shadeRed.g, shadeRed.b);
		glVertex2f(-0.5, -0.1);
	glEnd();

	//middle no shade

	glBegin(GL_QUADS);
		glColor3f(red.r, red.g, red.b);
		glVertex2f(0, 0.1);
		glVertex2f(0.3, 0.1);
		glVertex2f(0.3, -0.1);
		glVertex2f(0, -0.1);
	glEnd();

	//right red
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
		glColor3f(red.r, red.g, red.b);
		glVertex2f(0.3, 0.1);
		glColor3f(shadeRed.r, shadeRed.g, shadeRed.b);
		glVertex2f(0.8, 0.1);
		glVertex2f(0.8, -0.1);
		glColor3f(red.r, red.g, red.b);
		glVertex2f(0.3, -0.1);
	glEnd();

	//bottom left white
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
		glColor3f(grey.r, grey.g, grey.b);
		glVertex2f(-0.5, -0.1);
		glColor3f(1, 1, 1);
		glVertex2f(0, -0.1);
		glColor3f(grey.r, grey.g, grey.b);
		glVertex2f(0, -0.5);
		glVertex2f(-0.5, -0.5);
	glEnd();

	//bottom red 
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
		glColor3f(red.r, red.g, red.b);
		glVertex2f(0, -0.1);
		glVertex2f(0.3, -0.1);
		glColor3f(shadeRed.r, shadeRed.g, shadeRed.b);
		glVertex2f(0.3, -0.5);
		glVertex2f(0, -0.5);
	glEnd();

	//bottom right white
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
		glColor3f(1, 1, 1);
		glVertex2f(0.3, -0.1);
		glColor3f(grey.r, grey.g, grey.b);
		glVertex2f(0.8, -0.1);
		glVertex2f(0.8, -0.5);
		glVertex2f(0.3, -0.5);
	glEnd();

}

void scotlandFlag() {

	//white rectangle
	glBegin(GL_QUADS);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.8, 0.5);
		glVertex2f(0.8, -0.5);
		glVertex2f(-0.5, -0.5);
	glEnd();

	//init blue rgb color
	RGBColor blue = RGBColor(0, 101, 189);

	//top triangle;
	glBegin(GL_TRIANGLES);
		glColor3f(blue.r, blue.g, blue.b);
		glVertex2f(-0.4, 0.5);
		glVertex2f(0.7, 0.5);
		glVertex2f(0.1, 0.1);
	glEnd();

	//left triangle
	glBegin(GL_TRIANGLES);
		glColor3f(blue.r, blue.g, blue.b);
		glVertex2f(-0.5, 0.4);
		glVertex2f(0, 0);
		glVertex2f(-0.5, -0.4);
	glEnd();

	//bottom triangle
	glBegin(GL_TRIANGLES);
		glColor3f(blue.r, blue.g, blue.b);
		glVertex2f(-0.4, -0.5);
		glVertex2f(0.1, -0.1);
		glVertex2f(0.7, -0.5);
	glEnd();

	//right triangle
	glBegin(GL_TRIANGLES);
		glColor3f(blue.r, blue.g, blue.b);
		glVertex2f(0.8, 0.4);
		glVertex2f(0.8, -0.5);
		glVertex2f(0.2, 0);
	glEnd();


}


void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	//set the background colour
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 0.0f);
	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT);


	switch (qNo) {
	case 1:
		pahangFlag();
		break;
	case 2:
		n9Flag();
		break;
	case 3:
		englandFlag();
		break;
	case 4:
		scotlandFlag();
		break;
	default:
		break;
	}

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
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

