#ifndef CAST_H
#define CAST_H
#include "data.h"
#include "vecmath.h"
#include "collisions.h"

Color castRay(Ray r, Sphere *s, Intersected *i);

void castAllRays(double, double, double, double, int, int, Point, Sphere *s);

#endif