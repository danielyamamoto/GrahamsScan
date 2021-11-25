#include "Line.h"

// Complejidad O(1)
Line::Line() {
	a = new Point(0, 0);
	b = new Point(0, 0);
}

// Complejidad O(1)
Line::Line(Point* _a, Point* _b) {
	a = _a;
	b = _b;
}

// Complejidad O(1)
Line::~Line() { }

// Complejidad O(1)
Point* Line::getPointA() { return a; }

// Complejidad O(1)
Point* Line::getPointB() { return b; }

// Complejidad O(1)
float Line::getM() {
	return (b->getY() - a->getY()) / (b->getX() - a->getX());
}

// Complejidad O(1)
void Line::to_String() {
	std::cout << a->to_String() << ", " << b->to_String() << std::endl;
}