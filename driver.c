#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "vecmath.h"
#include "collisions.h"
#include "cast.h"

int main() {
   /* Debugging Code */ 
   //double minX = 0.05859357, maxX = 0.44921857;
   //double minY = 2.03125, maxY = 2.421875;
   //int width = 20, height = 20;

   double minX = -10, maxX = 10, minY = -7.5, maxY = 7.5;
   int width = 512, height = 384;
   
   Point eye = CreatePoint(0.0, 0.0, -14.0);
   Point blueSphere = CreatePoint(1.0, 1.0, 0.0);
   Point redSphere = CreatePoint(0.5, 1.5, -3.0);
   Point lightPoint = CreatePoint(-100.0, 100.0, -100.0);

   Color blue = CreateColor(0.0, 0.0, 1.0);
   Color red = CreateColor(1.0, 0.0, 0.0);
   Color ambient = CreateColor(1.0, 1.0, 1.0);
   Color lightColor = CreateColor(1.5, 1.5, 1.5);
   
   Finish largeFinish = CreateFinish(0.2, 0.4);
   Finish smallFinish = CreateFinish(0.4, 0.4);

   Light light = CreateLight(lightPoint, lightColor);
   Sphere spheres[2];
   spheres[0] = CreateSphere(blueSphere, 2.0, blue, largeFinish);
   spheres[1] = CreateSphere(redSphere, 0.5, red, smallFinish);
   
   castAllRays(minX, maxX, minY, maxY, width, height, eye, spheres, ambient,
         light);
   return 0;
}
