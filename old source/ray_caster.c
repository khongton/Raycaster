#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "vector_math.h"
#include "collisions.h"
#include "cast.h"
#include "commandline.h"
#define MIN_ARGS 1
#define FILE_IN_ARGS 1
#define FILE_OUT_ARGS 1

FILE* open_file(const char filename[], const char mode[])
{
   FILE *file = fopen(filename,mode);
   if (filename == NULL)
   {
      perror(filename);
      exit(1);
   }
   return file;
}

struct sphere_args create_sphere_array(FILE *in)
{
   int i = 0;
   double x;
   double y;
   double z;
   double radius;
   double r;
   double g;
   double b;
   double ambient;
   double diffuse;
   double specular;
   double roughness;
   int num_spheres = 0;
   struct sphere spheres[10000];
/*  
 int ret = fscanf(in, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
      &x, &y, &z, &radius, &r, &g, &b, &ambient, &diffuse, &specular, 
      &roughness);
   if (ret != 11)
   {
      printf("Not enough sphere arguments \n");
      exit(1);
   }
*/
   struct point center = create_point(x,y,z);
   double sphere_radius = radius;
   struct color color = create_color(r,g,b);
   struct finish finish = create_finish(ambient,diffuse,specular,roughness);
   printf("Hello world \n");
   int ret = fscanf(in, "%lf %lf %lf %lf  %lf %lf %lf %lf %lf %lf %lf",
     &x, &y, &z, &radius, &r, &g, &b, &ambient, &diffuse, &specular, 
     &roughness);
   for (i = 1; ret != EOF && i < 10000; i++)
   { 
      if (ret != 11)
      {
         printf("nope \n");
         exit(1);
      }
      else
      {
         spheres[i] = create_sphere(center, sphere_radius, color, finish);
         num_spheres = i++;
         printf("moisturize me \n");
      }
      ret = fscanf(in, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
         &x, &y, &z, &radius, &r, &g, &b, &ambient, &diffuse, &specular,
         &roughness);
   }
   struct sphere_args sphere_args;
   sphere_args =  create_sphere_args(num_spheres, spheres);
   printf("i am here \n");
   return sphere_args;
}

void print_file(FILE *in, int argc, char* argv[])
{
   printf("Hello warudo \n");
   FILE* image = open_file("image.ppm", "w");
   printf("is tis the offender \n");
   struct sphere_args arguments = create_sphere_array(in);
   struct eye_args eye_values = commandline_eye(argc, argv);
   struct view_args view_values = commandline_view(argc, argv);
   struct light_args light_values = commandline_light(argc, argv);
   struct ambient_args ambient_values = commandline_ambient(argc, argv);

   struct point eye_point = create_point(eye_values.eye_x, eye_values.eye_y,
     eye_values.eye_z);
   struct color varied_ambient = create_color(ambient_values.r, 
     ambient_values.g, ambient_values.b);
   struct point varied_light_p = create_point(light_values.x,
     light_values.y, light_values.z);
   struct color varied_light_col = create_color(light_values.r,
     light_values.g, light_values.b);
   struct light varied_light = create_light(varied_light_p,varied_light_col);

   cast_all_rays(view_values.min_x, view_values.max_x, view_values.min_y,
      view_values.max_y, view_values.width, view_values.height, eye_point,
      arguments.spheres, arguments.num_spheres,
      varied_ambient, varied_light);
   printf("send me to jesus please \n");
   for (int i = 0; i < 10000; i++)
   {
      fprintf(image, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
         arguments.spheres[i].center.x, 
         arguments.spheres[i].center.y,
         arguments.spheres[i].center.z, 
         arguments.spheres[i].radius,
         arguments.spheres[i].color.r, 
         arguments.spheres[i].color.g,
         arguments.spheres[i].color.b, 
         arguments.spheres[i].ambient.ambient,
         arguments.spheres[i].ambient.diffuse,
         arguments.spheres[i].ambient.specular,
         arguments.spheres[i].ambient.roughness);
   }
   fclose(image);
}

int main(int argc, char *argv[])
{
   usage(argc);   
   FILE* in = open_file(argv[FILE_IN_ARGS], "r");
   print_file(in, argc, argv);
   fclose(in);
   return 0;
}
