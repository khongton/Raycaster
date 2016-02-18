#include <stdlib.h>
#include <stdio.h>
#include "data.h"

Color CreateColor(double r, double g, double b) {
   Color color;
   color.red = r;
   color.green = g;
   color.blue = b;
   return color;
}

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

Sphere CreateSphere(Point origin, float rad, Color col) {
   Sphere sphere;
   sphere.center = origin;
   sphere.radius = rad;
   sphere.color = col;
   return sphere;
}
