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

/*Color castRay(Ray ray, Sphere *spheres, Intersected *list) {
   //int numHits = FindIntersectionPoints(spheres, ray, 2, list);
   MaybePoint mbp = SphereIntersectionPoint(ray, spheres[0]), mbp2;
   Sphere closest = spheres[0];
   for (int i = 1; i < 2; i++) {
      mbp2 = SphereIntersectionPoint(ray, spheres[i]);
   }
   if (distance(ray, mbp.p) > distance(ray, mbp2.p))
   calculate distance somehow and use that to find the nearest sphere     
}*/

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
