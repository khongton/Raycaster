#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "data.h"

//Initializes correctly.
//Consider using pointers to initialize

Point CreatePoint(double x, double y, double z) {
   Point point;
   point.x = x;
   point.y = y;
   point.z = z;
   return point;
}

Vector CreateVector(double x, double y, double z) {
   Vector dir;
   dir.x = x;
   dir.y = y;
   dir.z = z;
   return dir;
}

Ray CreateRay(Point origin, Vector direction) {
   Ray ray;
   ray.pt = origin;
   ray.dir = direction;
   return ray;
}

Sphere CreateSphere(Point origin, float rad) {
   Sphere sphere;
   sphere.center = origin;
   sphere.radius = rad;
   return sphere;
}
