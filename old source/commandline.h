#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include "data.h"
#include "vector_math.h"
#include "collisions.h"
#include "cast.h"


struct eye_args
{
   double eye_x;
   double eye_y;
   double eye_z;
};

struct view_args
{
   double min_x;
   double max_x;
   double min_y;
   double max_y;
   int width;
   int height;
};

struct light_args
{
    double x;
    double y;
    double z;
    double r;
    double g;
    double b;
};

struct ambient_args
{
    double r;
    double g;
    double b;
};

struct sphere_args
{
    int num_spheres;
    struct sphere spheres[];
};

struct eye_args create_eye_args(double eye_x, double eye_y, double eye_z);

struct view_args create_view_args(double min_x, double max_x, double min_y,
   double max_y, int width, int height);

struct light_args create_light_args(double x, double y, double z, double r,
   double g, double b);

struct ambient_args create_ambient_args(double r, double g, double b);

struct sphere_args create_sphere_args(int num_spheres, 
   struct sphere spheres[10000]);

void usage(int argc);

struct eye_args commandline_eye(int argc, char *argv[]);

struct view_args commandline_view(int argc, char *argv[]);

struct light_args commandline_light(int argc, char *argv[]);

struct ambient_args commandline_ambient(int argc, char *argv[]);

#endif

