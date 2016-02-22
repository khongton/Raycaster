#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "data.h"
#include "vecmath.h"
#include "collisions.h"
#include "cast.h"

typedef struct {
   double red;
   double green;
   double blue;
} DiffuseComp;

/* Compute the distance between two points. */
double distance(Point p1, Point p2) {
   double dx = p2.x - p1.x;
   double dy = p2.y - p1.y;
   double dz = p2.z - p1.z;

   return sqrt(dx*dx + dy*dy + dz*dz);
}

/* Converts a color from double to int so that it can be used in P3
 * file format.
 *
 * NOTE: (int) doubleVal * 255 does not work because of C precedence rules.
 * doubleVal will be casted first, then multipled by 255, giving us the wrong
 * result. */
int convertColor(double doubleVal) {
   double temp = doubleVal * 255;
   if (temp > 255)
      return 255;
   else if (temp < 0)
      return 0;
   else 
      return (int) temp;
}

DiffuseComp computeDiffuse(Sphere sphere, MaybePoint mbp, Color ambient, Light light, Sphere *spheres, 
      Intersected *list) {
   DiffuseComp diffuse;
   diffuse.red = 0.0;
   diffuse.green = 0.0;
   diffuse.blue = 0.0;
   
   Vector sphereNormal = SphereNormalAt(sphere, mbp.p);
   Vector scaleNormal = ScaleVector(sphereNormal, 0.01);
   Point offPoint = TranslatePoint(mbp.p, scaleNormal); 
   Vector pointToLight = fromTo(offPoint, light.position); 
   Vector lightNormal = NormalizeVector(pointToLight);
   double result = DotProduct(sphereNormal, lightNormal);
   if (result <= 0.0)
      result = 0.0;

   Ray lightRay = CreateRay(offPoint, pointToLight);
   int collisions = FindIntersectionPoints(spheres, lightRay, 2, list);
   if (collisions <= 0) {
      diffuse.red = result * light.color.red * sphere.color.red * sphere.finish.diffuse;
      diffuse.green = result * light.color.green * sphere.color.green * sphere.finish.diffuse;
      diffuse.blue = result * light.color.blue * sphere.color.blue * sphere.finish.diffuse;
   }
   return diffuse;
}

Color computeFinish(Sphere sphere, MaybePoint mbp, Color ambient, Light light, Sphere *spheres,
      Intersected *list) {
   Color color;
   DiffuseComp diffuse;

   diffuse = computeDiffuse(sphere, mbp, ambient, light, spheres, list);

   color.red = (sphere.color.red * sphere.finish.ambient * ambient.red) + diffuse.red;
   color.green = (sphere.color.green * sphere.finish.ambient * ambient.green) + diffuse.green;
   color.blue = (sphere.color.blue * sphere.finish.ambient * ambient.blue) + diffuse.blue;
   return color;
}

Color castRay(int numHits, Ray ray, Intersected *list, Color ambient,
      Light light, Sphere *spheres) {
   MaybePoint mbp = SphereIntersectionPoint(ray, list->hitSpheres[0]), mbp2;
   Sphere closest = list->hitSpheres[0];
   
   for (int sphereIndex = 1; sphereIndex < numHits; sphereIndex++) {
      mbp2 = SphereIntersectionPoint(ray, list->hitSpheres[sphereIndex]);
      if (distance(ray.pt, mbp.p) > distance(ray.pt, mbp2.p)) {
         mbp = mbp2;
         closest = list->hitSpheres[sphereIndex];
      }
   }
   return computeFinish(closest, mbp, ambient, light, spheres, list);
}

void castAllRays(double minX, double maxX, double minY, double maxY, int width, 
      int height, Point eye, Sphere *spheres, Color ambient, Light light) {
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
            sphereColor = castRay(numHits, r, &list, ambient, light, spheres);
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
