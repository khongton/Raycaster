#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "vecmath.h"
#include "collisions.h"
#include "cast.h"
#include "cmdline.h"

/* Counts sphere properly */
int CountSpheres(FILE *input) {
   int numSpheres = 0;
   char ch;
   while (!feof(input)) {
      ch = fgetc(input);
      if (ch == '\n')
         numSpheres++;
   }
   rewind(input);
   return numSpheres;
}


int VerifyLine(char *line) {
   int count = 1, result = 0;
   char *copy = line;
   while ((copy = strchr(copy, ' '))) {
      count++;
      copy++;
   }

   if (count == 11) 
      result = 1;
   return result;
}

void ParseFile(FILE *input, Sphere **spheres) {
   int lineNum = 1, sphereIndex = 0;
   char line[MAX_BUFF];
   double x, y, z, radius, r, g, b;
   double ambient, diffuse, specular, rough;
   Point center;
   Color sphereColor;
   Finish finish;

   while (fgets(line, sizeof(line), input)) {
      if (!VerifyLine(line) || sscanf(line, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
         &x, &y, &z, &radius, &r, &g, &b, &ambient, &diffuse, &specular, &rough) != 11) {
         printf("malformed sphere on line %d...skipping\n", lineNum);
      }
      else {
         center = CreatePoint(x, y, z);
         sphereColor = CreateColor(r, g, b);
         finish = CreateFinish(ambient, diffuse, specular, rough);
         (*spheres)[sphereIndex] = CreateSphere(center, radius, sphereColor, finish);
         sphereIndex++;
      }
      lineNum++;
   }
}
