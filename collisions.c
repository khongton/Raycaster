#include "data.h"
#include <math.h>
#include <stdio.h>

MaybePoint CreateMaybePoint(int boolean, Point point) {
   MaybePoint maybe;
   
   maybe.isPoint = boolean;
   maybe.p = point;

   return maybe;
}

double discriminant(double a, double b, double c) {
   return sqrt(b * b - 4 * a * c);   
}

Point CalculatePoint(double tVal, Ray rayDir) {
   Vector scaled = ScaleVector(rayDir.dir, tVal);
   return TranslatePoint(rayDir.pt, scaled);
}

MaybePoint rootSolver(double root1, double root2, Ray ray) {
   Point curPoint;
   int pointBool;

   if (root1 >= 0 && root2 >= 0) {
      pointBool = 1;
      if (root1 <= root2)
         curPoint = CalculatePoint(root1, ray);
      else
         curPoint = CalculatePoint(root2, ray);
   }
   else if ((root1 < 0 && root2 < 0) || (isnan(root1) && isnan(root2))) {
      pointBool = 0;
      curPoint = CreatePoint(0, 0, 0);
   }
   else {
      pointBool = 1;
      if (root1 >= 0 && root2 < 0)
            curPoint = CalculatePoint(root1, ray);
      else if (root2 >= 0 && root1 < 0) 
            curPoint = CalculatePoint(root2, ray);
   }

   return CreateMaybePoint(pointBool, curPoint);
}

MaybePoint SphereIntersectionPoint(Ray ray, Sphere sphere) {
   MaybePoint mbp;

   Vector quadVec = fromTo(sphere.center, ray.pt);
   double aComp = DotProduct(ray.dir, ray.dir);
   double bComp = DotProduct(ScaleVector(quadVec, 2), ray.dir);
   double cComp = DotProduct(quadVec, quadVec) - sphere.radius * sphere.radius;

   //solve with x = (-b plus/minus sqrt(b^2 - 4ac))/2a
   double root1 = (-bComp + discriminant(aComp, bComp, cComp))/(2 * aComp);
   double root2 = (-bComp - discriminant(aComp, bComp, cComp))/(2 * aComp);

   mbp = rootSolver(root1, root2, ray);
   return mbp;
}

int FindIntersectionPoints(Sphere *slist, Ray r, int num, Intersected *list) {
   int i = 0;
   int numHit = 0;
   for (i = 0; i < num; i++) {
      MaybePoint mbp = SphereIntersectionPoint(r, slist[i]);
      if (mbp.isPoint) {
         list->hitSpheres[numHit] = slist[i];
         list->hitPoints[numHit] = mbp.p;
         numHit++;
      }
   }
   return numHit;
}

Vector SphereNormalAt(Sphere s, Point p) {
   return NormalizeVector(fromTo(s.center, p));
}
