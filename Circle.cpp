#include "RGBColor.cpp"
#include <math.h>
#include <iostream>
#pragma comment (lib, "OpenGL32.lib")
class Circle {
public:
	RGBColor* color;
	float x, y, x2, y2,r;
	float noOfTri = 1000;
	const float PI = 3.1429;
	float startingAngle;
	float endingAngle;
	Circle(float x,float y,float r,RGBColor* color,float startingAngle,float endingAngle) {
		this->x = x;
		this->y = y;
		this->r = r;
		this->x2 = 0;
		this->y2 = 0;
		this->color = color;
		this->startingAngle = startingAngle > 2 * PI ? startingAngle *  PI / 180: startingAngle;
		this->endingAngle = endingAngle > 2 * PI ? endingAngle * PI / 180 : endingAngle;
	}

};