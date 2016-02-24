#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "vecmath.h"
#include "collisions.h"
#include "cast.h"
#include "cmdline.h"

int main(int argc, char **argv) {
   int numSpheres;
   Sphere *spheres;
   FILE *input;
   
   //input checking
   if (argc < 2) {
      printf("Usage: ./a.out <filename> [-eye x y z] [-view min_x max_x min_y max_y width height] [-light x y z r g b] [-ambient r g b]\n");
      exit(0);
   }
   else {
      input = fopen(argv[1], "r");
      if (input) {
         numSpheres = CountSpheres(input);
         spheres = malloc(sizeof(Sphere) * numSpheres);
         ParseFile(input, &spheres);
      }
      else {
         printf("Error: File not found.\n");
         exit(0);
      }
   } 
   fclose(input);
   /*
   while (*++argv) {
      printf("%s\n", *argv);
   }
   */
   
   double minX = -10, maxX = 10, minY = -7.5, maxY = 7.5;
   int width = 512, height = 384;
   
   Canvas canvas;
   InitCanvas(&canvas, minX, maxX, minY, maxY, width, height);

   Point eye = CreatePoint(0.0, 0.0, -14.0);
   Point lightPoint = CreatePoint(-100.0, 100.0, -100.0);
   Color lightColor = CreateColor(1.5, 1.5, 1.5);
   Color ambient = CreateColor(1.0, 1.0, 1.0);
   Light light = CreateLight(lightPoint, lightColor);

   castAllRays(&canvas, eye, spheres, ambient, light, numSpheres);
   return 0;
}
