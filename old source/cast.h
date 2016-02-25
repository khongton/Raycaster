#ifndef CAST_H
#define CAST_H
#include "data.h"
#include "vector_math.h"
#include "collisions.h"


struct color cast_ray(struct ray r, struct sphere spheres[], int num_spheres,
   struct color ambient, struct light light, struct point eye);

void cast_all_rays(double min_x, double max_x, double min_y, double max_y,
    int width, int height, struct point eye, struct sphere spheres[],
    int num_spheres, struct color ambient, struct light light);

#endif
