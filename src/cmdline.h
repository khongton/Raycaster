#ifndef CMDLINE_H
#define CMDLINE_H
#include "data.h"
#include "vecmath.h"
#include "collisions.h"
#include "cast.h"

#define MAX_BUFF 1024

int CountSpheres(FILE *input);

int VerifyLine(char *line);

void ParseFile(FILE *input, Sphere **spheres);

#endif
