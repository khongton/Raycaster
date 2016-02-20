#ifndef CAST_H
#define CAST_H
#include "data.h"
#include "vecmath.h"
#include "collisions.h"


/* Coonvenience function to compute distance between two points */
double distance(Point p1, Point p2);

/* Cast a ray from the eye into the scene to determine the color 
 * we should print to the screen. Prints the color of the sphere hit 
 * or white if it hit nothing */
Color castRay(int numHits, Ray r, Intersected *i, Color ambient);

/* Cast a ray to every single pixel in the scene. Prints to a file in PPM
 * format. */
void castAllRays(double, double, double, double, int, int, Point, Sphere *s,
      Color ambient);

#endif
