#ifndef DATA_H
#define DATA_H

/* A data structure to represent color in RGB format. */
typedef struct {
   double red;
   double green;
   double blue;
} Color;

/* A point in 3D space */
typedef struct {
   double x;
   double y;
   double z;
} Point; 

/* A 3D vector */
typedef struct {
   double x;
   double y;
   double z;
} Vector;

/* A ray that extends in one direction in 3D space. 
 * This data structure is used to simulate light */
typedef struct {
   Point pt;
   Vector dir;
} Ray; 

/* A sphere floating in space. 
 * We will be reflecing the light off the ray */
typedef struct {
   Point center;
   float radius;
   Color color;
} Sphere; 

/* Initialize a point in 3D space */
Point CreatePoint(double x, double y, double z);

/* Initialize a vector in 3D space */
Vector CreateVector(double x, double y, double z);

/* Initialize a ray given a point and a direction */
Ray CreateRay(Point origin, Vector direction);

/* Initialize a sphere given a point and radius */
Sphere CreateSphere(Point origin, float rad, Color col);

/* Initialize a color given the RGB values */
Color CreateColor(double r, double g, double b);

#endif
