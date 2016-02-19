#ifndef CAST_H
#define CAST_H
#include "data.h"
#include "vecmath.h"
#include "collisions.h"

double distance(Point p1, Point p2);

Color castRay(Ray r, Sphere *s, Intersected *i);

void castAllRays(double, double, double, double, int, int, Point, Sphere *s);

#endif
