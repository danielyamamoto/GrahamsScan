#pragma once

#include <string>
#include <iostream>
#include "Point.h"

class Line {
public:
	Line();
	Line(Point* _a, Point* _b);
	~Line();

	Point* getPointA();
	Point* getPointB();

	float getM();
	void to_String();

private:
	Point* a;
	Point* b;
};