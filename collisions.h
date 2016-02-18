#ifndef COLLISIONS_H
#define COLLISIONS_H
#include "data.h"
#include "vecmath.h"

typedef struct {
   int isPoint; /* Boolean to determine if point exists or not */
   Point p;     /* The point we are questioning */
} MaybePoint;

typedef struct {
   Sphere *hitSpheres; /* Pointer to array of spheres hit */
   Point *hitPoints;   /* Pointer to array of points hit */
} Intersected;

/* Initializes a MaybePoint struct. */
MaybePoint CreateMaybe(int isPoint, Point p);

/* Cast a ray to a sphere and check if it intersects the sphere or not. */
MaybePoint SphereIntersectionPoint(Ray r, Sphere s);

/* Function that checks for an intersecting between the given ray and 
 * all the spheres in the list. If a ray intersects a sphere, it is added
 * into the Intersected list. */
int FindIntersectionPoints(Sphere *slist, Ray r, int num, Intersected *list);

/* Compute the normal vector of a point on an intersected sphere. This is
 * used to determine whether or not the point is visible to the viewer. */
Vector SphereNormalAt(Sphere s, Point p);

#endif