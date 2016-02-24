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

typedef struct {
   Sphere sphere;
   MaybePoint mbp;
   Color ambient;
   Light light;
   Vector sphereNorm;
   Point offPoint;
} Pixel;

void InitCanvas(Canvas *picture, double, double, double, double, int, int);

void InitPixel(Pixel *pixel, Sphere s, MaybePoint mbp, Color ambient, Light light);

/* Coonvenience function to compute distance between two points */
double distance(Point p1, Point p2);

/* Cast a ray from the eye into the scene to determine the color 
 * we should print to the screen. Prints the color of the sphere hit 
 * or white if it hit nothing */
Color castRay(int numHits, Ray r, Intersected *i, Color ambient, Light light, 
      Sphere *spheres, Point eye, int numSpheres);

/* Cast a ray to every single pixel in the scene. Prints to a file in PPM
 * format. */
void castAllRays(Canvas *pic, Point eye, Sphere *s, Color ambient, Light light, int numSpheres);

#endif
