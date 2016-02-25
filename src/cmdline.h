#ifndef CMDLINE_H
#define CMDLINE_H
#include "data.h"
#include "vecmath.h"
#include "collisions.h"
#include "cast.h"

#define MAX_BUFF 1024
#define SPHERE_ARGS 11
#define MIN_X -10
#define MAX_X 10
#define MIN_Y -7.5
#define MAX_Y 7.5
#define WIDTH 512
#define HEIGHT 384

int CountSpheres(FILE *input);

int VerifyLine(char *line);

void ParseFile(FILE *input, Sphere **spheres);

#endif
