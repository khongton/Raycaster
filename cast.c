#include <stdlib.h>
#include <stdio.h>
#include "data.h"

//If a sphere is hit compute the distance from it to the 
//eye and determine what the nearest sphere is

Color castRay(Ray ray, Sphere *spheres, Intersected *list) {
   //int numHits = FindIntersectionPoints(spheres, ray, 2, list);
   return CreateColor(0.0, 0.0, 0.0) ;
}

void castAllRays(double minX, double maxX, double minY, double maxY, int width,  int height, Point eye, Sphere *spheres) {
   double picWidth, picHeight;
   double pixWidth = (maxX  - minX)/width;
   double pixHeight = (maxY - minY)/height;

   Intersected list;
   Sphere sphereHit[100];
   Point pointHit[100];
   list.hitSpheres = sphereHit;
   list.hitPoints = pointHit;
   
   Point p;
   Vector v;
   Ray r;

   printf("P3\n%d %d %d\n", width, height, 255);
   for (picHeight = maxY; picHeight > minY; picHeight -= pixHeight) {
      for (picWidth = minX; picWidth < maxX; picWidth += pixWidth) {
         p = CreatePoint(picWidth, picHeight, 0.0);
         v = fromTo(eye, p);
         r = CreateRay(eye, v);
         if (FindIntersectionPoints(spheres, r, 2, &list)) {
            printf("0 0 0\n");
         }
         else {
            printf("255 255 255\n");
         }
      }
   }
}
