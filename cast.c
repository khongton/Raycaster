//when making PPM format print out header first 
//printf("P3 %d %d %d\n", width, height, 255);
//then print out each pixel so
//printf("%d %d %d\n", red color, green color, blue color);

#include <stdlib.h>
#include <stdio.h>
#include "data.h"

//cast_ray(ray r, sphere spheres[], int numSpheres, color ambient, light light, point eye)

//we assume that there are two spheres in the viewport - kind of fragile
//and hardcoded tbh

int castRay(Ray ray, Sphere *spheres, Intersected *list) {
   int numHits = FindIntersectionPoints(spheres, ray, 100, list);
   return numHits;
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
