#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "data.h"
#include "vecmath.h"
#include "collisions.h"
#include "cast.h"

double distance(Point p1, Point p2) {
   double dx = p2.x - p1.x;
   double dy = p2.y - p1.y;
   double dz = p2.z - p1.z;

   return sqrt(dx*dx + dy*dy + dz*dz);
}

int convertColor(double doubleVal) {
   return (int) doubleVal * 255;
}

Color computeFinish(Sphere sphere, Color ambient) {
   double red = sphere.color.red * ambient.red * sphere.finish.ambient;
   double green = sphere.color.green * ambient.green * sphere.finish.ambient;
   double blue = sphere.color.blue * ambient.green * sphere.finish.ambient;

   return CreateColor(red, green, blue);
}

Color castRay(int numHits, Ray ray, Intersected *list, Color ambient) {
   MaybePoint mbp = SphereIntersectionPoint(ray, list->hitSpheres[0]), mbp2;
   Sphere closest = list->hitSpheres[0];
   
   for (int sphereIndex = 1; sphereIndex < numHits; sphereIndex++) {
      mbp2 = SphereIntersectionPoint(ray, list->hitSpheres[sphereIndex]);
      if (distance(ray.pt, mbp.p) > distance(ray.pt, mbp2.p)) {
         mbp = mbp2;
         closest = list->hitSpheres[sphereIndex];
      }
   }
   return closest.color;
}

void castAllRays(double minX, double maxX, double minY, double maxY, int width,  int height, Point eye, Sphere *spheres, Color ambient) {
   int numHits;
   double picWidth, picHeight;
   double pixWidth = (maxX  - minX)/width;
   double pixHeight = (maxY - minY)/height;

   Intersected list;
   Sphere sphereHit[sizeof(spheres)];
   Point pointHit[sizeof(spheres)];
   list.hitSpheres = sphereHit;
   list.hitPoints = pointHit;
   
   Point p;
   Vector v;
   Ray r;
   Color sphereColor;

   printf("P3\n%d %d %d\n", width, height, 255);
   for (picHeight = maxY; picHeight > minY; picHeight -= pixHeight) {
      for (picWidth = minX; picWidth < maxX; picWidth += pixWidth) {
         p = CreatePoint(picWidth, picHeight, 0.0);
         v = fromTo(eye, p);
         r = CreateRay(eye, v);
         if ((numHits = FindIntersectionPoints(spheres, r, 2, &list))) {
            sphereColor = castRay(numHits, r, &list, ambient);
            printf("%d %d %d\n",
                  convertColor(sphereColor.red),
                  convertColor(sphereColor.green),
                  convertColor(sphereColor.blue));
         }
         else {
            printf("255 255 255\n");
         }
      }
   }
}
