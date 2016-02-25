#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data.h"
#include "vector_math.h"
#include "collisions.h"
#include "cast.h"
#include "commandline.h"
#define MIN_ARGS 1

void usage(int argc)
{
   if (argc < MIN_ARGS)
   {
      printf("Usage is: a.out <filename> Optional arguments here. \n");
      exit(1);
   }
}

struct eye_args create_eye_args(double eye_x, double eye_y, double eye_z)
{
   struct eye_args values;
   values.eye_x = eye_x;
   values.eye_y = eye_y;
   values.eye_z = eye_z;
   return values;
}
   

struct eye_args commandline_eye(int argc, char *argv[])
{
   int i;
   double eye_x = 0;
   double eye_y = 0;
   double eye_z = 0;
   for (i = 0; i < argc; i++)
   {
      if (strcmp(argv[i], "-eye") == 0)
      {
         sscanf(argv[i], "%lf %lf %lf", &eye_x, &eye_y, &eye_z);
      }
      else
      {
         eye_x = 0.0;
         eye_y = 0.0;
         eye_z = -14.0;
      }
   }
   struct eye_args values;
   values = create_eye_args(eye_x, eye_y, eye_z);
   return values;
}   
   
struct view_args create_view_args(double min_x, double max_x, double min_y, 
   double max_y, int width, int height)
{
   struct view_args values;
   values.min_x = min_x;
   values.max_x = max_x;
   values.min_y = min_y;
   values.max_y = max_y;
   values.width = width;
   values.height = height;
   return values;
}

struct view_args commandline_view(int argc, char *argv[])
{
   int i;
   double min_x = 0;
   double max_x = 0;
   double min_y = 0;
   double max_y = 0;
   int width = 0;
   int height = 0;

   for (i = 0; i < argc; i++)
   {
       if (strcmp(argv[i], "-view") == 0)
       {
          sscanf(argv[i], "%lf %lf %lf %lf %d %d", &min_x, &max_x, &min_y,
             &max_y, &width, &height);
       }
       else
       {
          min_x = -10;
          max_x = 10;
          min_y = -7.5;
          max_y = 7.5;
          width = 1024;
          height = 768;
       }
    }
    struct view_args values;
    values = create_view_args(min_x, max_x, min_y, max_y, width, height);
    return values;
}

struct light_args create_light_args(double x, double y, double z, double r,
   double g, double b)
{
   struct light_args values;
   values.x = x;
   values.y = y;
   values.z = z;
   values.r = r;
   values.g = g;
   values.b = b;
   return values;
}

struct light_args commandline_light(int argc, char *argv[])
{
   int i;
   double light_x = 0;
   double light_y = 0;
   double light_z = 0;
   double light_r = 0;
   double light_g = 0;
   double light_b = 0;
   for (i = 0; i < argc; i++)
   {
      if (strcmp(argv[i],"-light") == 0)
      {
         sscanf(argv[i], "%lf %lf %lf %lf %lf %lf", &light_x, &light_y,
           &light_z, &light_r, &light_g, &light_b);
      }
      else
      {
         light_x = -100.0;
         light_y = 100.0;
         light_z = -100.0;
         light_r = 1.5;
         light_g = 1.5;
         light_b = 1.5;
      }
   }
   struct light_args values;
   values = create_light_args(light_x, light_y, light_z, light_r,
     light_g, light_b);
   return values;
}

struct ambient_args create_ambient_args(double r, double g, double b)
{
   struct ambient_args values;
   values.r = r;
   values.g = g;
   values.b = b;
   return values;
}

struct ambient_args commandline_ambient(int argc, char *argv[])
{
   int i;
   double ambient_r = 0;
   double ambient_g = 0;
   double ambient_b = 0;
   
   for (i = 0; i < argc; i++)
   {
      if (strcmp(argv[i], "-ambient") == 0)
      {
         sscanf(argv[i], "%lf %lf %lf", &ambient_r, &ambient_g, &ambient_b);  
      }
      else
      {
         ambient_r = 1.0;
         ambient_g = 1.0;
         ambient_b = 1.0;
      }
   }
   struct ambient_args values;
   values = create_ambient_args(ambient_r, ambient_g, ambient_b);
   return values;
}

struct sphere_args create_sphere_args(int num_spheres, 
   struct sphere spheres[10000])
{
    struct sphere_args sphere_args;
    sphere_args.num_spheres = num_spheres;
    sphere_args.spheres[10000] = spheres[10000];
    return sphere_args;
}
