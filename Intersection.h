#pragma once

#include "Line.h"

class Intersection {
public:
	enum INTERSECTION_TYPE {
		CW,
		CCW,
		COLINEAR
	};

	Intersection();
	Intersection(Line* _l1, Line* _l2);
	~Intersection();
	
	bool getDistribution();
	INTERSECTION_TYPE getOrientation(Point* a, Point* b, Point* c);

private:
	Line* l1;
	Line* l2;
};