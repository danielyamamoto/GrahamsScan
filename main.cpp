/*
El polígono convexo más pequeño en un conjunto de puntos aplicando el algoritmo de Graham's Scan.

Autores:
Yusdivia Molina
Daniel Yamamoto
Héctor Noyola

Fecha de modificación: 22/10/2021
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <time.h>
#include "Point.h"
#include "Intersection.h"
#include "pbPlots.hpp"
#include "supportLib.hpp"

// NOTA: Los archivos pbPlots y supportLib se ocupan para graficar los puntos, ¡abajo vienen las referencias!

#define NPOINTS 10
#define MIN -10.0f
#define MAX 10.0f
#define PLOT_SIZE 1200

// Liga del video tutorial: https://www.youtube.com/watch?v=RNKVHQzvaRM
// Liga del repositorio: https://github.com/InductiveComputerScience/pbPlots
void drawPlot(std::vector<Point*> points, std::string namePlot) {
	RGBABitmapImageReference* imageRef = CreateRGBABitmapImageReference();
	std::vector<double> x, y;
	for (int i = 0; i < points.size(); i++) {
		x.push_back(points[i]->getX());
		y.push_back(points[i]->getY());
	}

	DrawScatterPlot(imageRef, PLOT_SIZE, PLOT_SIZE, &x, &y);

	std::vector<double>* pngData = ConvertToPNG(imageRef->image);
	WriteToFile(pngData, namePlot);
	DeleteImage(imageRef->image);
}

// Liga de apoyo general: https://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
// Complejidad O(1)
int orientation(Point* p, Point* q, Point* r) {
	int val = (q->getY() - p->getY()) * (r->getX() - q->getX()) -
		(q->getX() - p->getX()) * (r->getY() - q->getY());
	if (val == 0) return 0;  // Colinear
	return (val > 0) ? 1 : 2; // Clock or Counterclock Wise
}

// Liga del top/push/pop: https://www.geeksforgeeks.org/stack-in-cpp-stl/ 
// Complejidad O(1)
Point* nextToTop(std::stack<Point*> &s) {
	Point* p = s.top();
	s.pop();
	Point* res = s.top();
	s.push(p);
	return res;
}

// Liga del sort: https://stackoverflow.com/questions/4484900/what-is-the-time-complexity-of-stdsort-in-the-c-standard-library
// Liga del stack top/push/pop: https://www.geeksforgeeks.org/stack-in-cpp-stl/ 
// Liga del vector push_back: https://www.hackerearth.com/practice/notes/standard-template-library/
// Liga de apoyo general: https://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
// Complejidad O(n log n)
void convexHull() {
    if (NPOINTS < 3) {
        std::cout << "No es posible realizar la operación con menos de 3 puntos" << std::endl;
    }

	std::vector<Point*> points;
	for (int i = 0; i < NPOINTS; i++) {
		Point* p = new Point();
		p->randomize(MIN, MAX); // Complejidad O(√(n))
		points.push_back(p); // Complejidad O(1)
	}

    // Plot de los puntos iniciales
	drawPlot(points, "plot1.png");

    // Ordenamos los puntos para encontrar la menos Y
	std::sort(points.begin(), points.end(), Point::compare_points_by_y_coordinate()); // Complejidad O(n log n)
	// Guardamos la menor Y 
	Point* minY = points[0];
    // Ordenamos los puntos por coordenadas polares
	std::sort(points.begin(), points.end(), Point::compare_points_by_polar_angle(minY)); // Complejidad O(n log n)
    // Creamos un stack donde se irán guardando los puntos que pertenen a la "envoltura"
	std::stack<Point*> result;
	result.push(points[0]); // Complejidad O(1)
	result.push(points[1]); // Complejidad O(1)
	result.push(points[2]); // Complejidad O(1)

	for (int i = 3; i < NPOINTS; i++) {
		while (orientation(nextToTop(result), result.top(), points[i]) != 2) {
			result.pop(); // Complejidad O(1)
		}
		result.push(points[i]); // Complejidad O(1)
	}
	
    // Agregamos el punto inicial para cerrar el "polígono"
	result.push(minY);
	
	// Imprimimos los puntos almacenados en el stack
	std::vector<Point*> tmp;
    while (!result.empty()) {
		Point* p = result.top(); // Complejidad O(1)
        tmp.push_back(p); // Complejidad O(1)
		std::cout << p->to_String() << std::endl;
		result.pop(); // Complejidad O(1)
	}

    // Plot de los puntos finales
	drawPlot(tmp, "plot2.png");    
}

// Liga de srand: https://stackoverflow.com/questions/18678089/time-complexity-for-c-program-which-uses-random-numbers
int main() {
	srand(time(NULL)); // Complejidad O(2^n) 
	convexHull(); // Complejidad O(n log n) 
	return 0;
}