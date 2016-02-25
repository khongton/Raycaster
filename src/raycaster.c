#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "vecmath.h"
#include "collisions.h"
#include "cast.h"
#include "cmdline.h"

int main(int argc, char **argv) {
   int numSpheres, curArg, width = WIDTH, height = HEIGHT;
   char *flag;
   Sphere *spheres;
   FILE *input;
   double minX = MIN_X, minY = MIN_Y, maxX = MAX_X, maxY = MAX_Y;
   double eyeX = 0.0, eyeY = 0.0, eyeZ = -14.0;
   double lightX = -100.0, lightY = 100.0, lightZ = - 100.0; 
   double lightR = 1.5, lightG = 1.5, lightB = 1.5;
   double ambientR = 1.0, ambientG = 1.0, ambientB = 1.0;

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

   for (curArg = 0; curArg < argc; curArg++) {
      flag = argv[curArg];
      switch (flag[1]) {
         case 'e':
            if (!strcmp(flag, "-eye")) {
               sscanf(argv[curArg + 1], "%lf", &eyeX);
               sscanf(argv[curArg + 2], "%lf", &eyeY);
               sscanf(argv[curArg + 3], "%lf", &eyeZ);
               curArg += 3;
            }
            break;
         case 'v':
            if (!strcmp(flag, "-view")) {
               sscanf(argv[curArg + 1], "%lf", &minX);
               sscanf(argv[curArg + 2], "%lf", &maxX);
               sscanf(argv[curArg + 3], "%lf", &minY);
               sscanf(argv[curArg + 4], "%lf", &maxY);
               sscanf(argv[curArg + 5], "%d", &width);
               sscanf(argv[curArg + 6], "%d", &height);
               curArg += 6;
            }
            break;
         case 'l':
            if (!strcmp(flag, "-light")) {
               sscanf(argv[curArg + 1], "%lf", &lightX);
               sscanf(argv[curArg + 2], "%lf", &lightY);
               sscanf(argv[curArg + 3], "%lf", &lightZ);
               sscanf(argv[curArg + 4], "%lf", &lightR);
               sscanf(argv[curArg + 5], "%lf", &lightG);
               sscanf(argv[curArg + 6], "%lf", &lightB);
               curArg += 6;
            
            }
            break;
         case 'a':
            if (!strcmp(flag, "-ambient")) {
               sscanf(argv[curArg + 1], "%lf", &ambientR);
               sscanf(argv[curArg + 2], "%lf", &ambientG);
               sscanf(argv[curArg + 3], "%lf", &ambientB);
               curArg += 3;
            }
            break;
         default:
            break;
      }
   }

   Canvas canvas;
   InitCanvas(&canvas, minX, maxX, minY, maxY, width, height);

   Point eye = CreatePoint(eyeX, eyeY, eyeZ);
   Point lightPoint = CreatePoint(lightX, lightY, lightZ);
   Color lightColor = CreateColor(lightR, lightG, lightB);
   Color ambient = CreateColor(ambientR, ambientG, ambientB);
   Light light = CreateLight(lightPoint, lightColor);

   castAllRays(&canvas, eye, spheres, ambient, light, numSpheres);
   return 0;
}
