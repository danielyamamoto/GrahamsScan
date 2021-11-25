#include "Intersection.h"

// Complejidad O(1)
Intersection::Intersection() {
    l1 = nullptr;
    l2 = nullptr;
}

// Complejidad O(1)
Intersection::Intersection(Line* _l1, Line* _l2) {
    l1 = _l1;
    l2 = _l2;
}

// Complejidad O(1)
Intersection::~Intersection() { }

// Complejidad O(1)
Intersection::INTERSECTION_TYPE Intersection::getOrientation(Point* a, Point* b, Point* c) {
    Line* s1 = new Line(a, b); // Complejidad O(1)
    Line* s2 = new Line(b, c); // Complejidad O(1)

    float m1 = s1->getM(); // Complejidad O(1)
    float m2 = s2->getM(); // Complejidad O(1)

    if (m2 > m1) return Intersection::INTERSECTION_TYPE::CCW;
    else if (m1 > m2) return Intersection::INTERSECTION_TYPE::CW;
    else return Intersection::INTERSECTION_TYPE::COLINEAR;
}

// Complejidad O(1)
bool Intersection::getDistribution() {
    Intersection::INTERSECTION_TYPE inter1 = getOrientation(l1->getPointA(), l1->getPointB(), l2->getPointA()); // Complejidad O(1)
    Intersection::INTERSECTION_TYPE inter2 = getOrientation(l1->getPointA(), l1->getPointB(), l2->getPointB()); // Complejidad O(1)
    Intersection::INTERSECTION_TYPE inter3 = getOrientation(l2->getPointA(), l2->getPointB(), l1->getPointA()); // Complejidad O(1)
    Intersection::INTERSECTION_TYPE inter4 = getOrientation(l2->getPointA(), l2->getPointB(), l1->getPointB()); // Complejidad O(1)

    std::cout << "ABC: " << std::to_string(inter1) << std::endl;
    std::cout << "ABD: " << std::to_string(inter2) << std::endl;
    std::cout << "CDA: " << std::to_string(inter3) << std::endl;
    std::cout << "CDB: " << std::to_string(inter4) << std::endl;

    return inter1 != inter2 || inter3 != inter4 ? true : false;
}