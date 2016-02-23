#ifndef CAST_H
#define CAST_H
#include "data.h"
#include "vecmath.h"
#include "collisions.h"

typedef struct {
   double minWidth;
   double maxWidth;
   double minHeight;
   double maxHeight;
   int picWidth;
   int picHeight;
} Canvas;

void InitCanvas(Canvas *picture, double, double, double, double, int, int);

/* Coonvenience function to compute distance between two points */
double distance(Point p1, Point p2);

/* Cast a ray from the eye into the scene to determine the color 
 * we should print to the screen. Prints the color of the sphere hit 
 * or white if it hit nothing */
Color castRay(int numHits, Ray r, Intersected *i, Color ambient, Light light, 
      Sphere *spheres, Point eye);

/* Cast a ray to every single pixel in the scene. Prints to a file in PPM
 * format. */
void castAllRays(Canvas *pic, Point eye, Sphere *s, Color ambient, Light light);

#endif
