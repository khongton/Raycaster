#ifndef DATA_H
#define DATA_H

typedef struct {
   double x;
   double y;
   double z;
} Point; // a point in 3D space

typedef struct {
   double x;
   double y;
   double z;
} Vector; //A vector with magnitudes x y z

typedef struct {
   Point pt;
   Vector dir;
} Ray; //A ray going off into space

typedef struct {
   Point center;
   float radius;
} Sphere; //A sphere which we will intersect

typedef struct {
   int isPoint; //boolean if have a point or not
   Point p; //the point we are looking at
} MaybePoint;

typedef struct {
   Sphere *hitSpheres;
   Point *hitPoints;
} Intersected;

//Initialize a point
Point CreatePoint(double x, double y, double z);

//Initialize a vector
Vector CreateVector(double x, double y, double z);

//Initialize a ray
Ray CreateRay(Point origin, Vector direction);

//Initialize a sphere
Sphere CreateSphere(Point origin, float rad);

//Scale a vector by a double value
Vector ScaleVector(Vector toScale, double scalar);

//returns dot product of two vectors
double DotProduct(Vector vec1, Vector vec2);

//returns scalar length of a vector
double VectorLength(Vector len);

//returns the normalized vector
Vector NormalizeVector(Vector toNormalize);

//returns a vector from the different of two points
Vector PointDiff(Point point1, Point point2);

//returns a vector from the differnce of two vectors
Vector VecDiff(Vector vec1, Vector vec2);

//returns a point's position after moved along a vector
Point TranslatePoint(Point toTrans, Vector dir);

//convenience function for point diff
Vector fromTo(Point from, Point to);

MaybePoint CreateMaybe(int isPoint, Point p);

MaybePoint SphereIntersectionPoint(Ray r, Sphere s);

int FindIntersectionPoints(Sphere *slist, Ray r, int num, Intersected *list);

Vector SphereNormalAt(Sphere s, Point p);

int castRay(Ray r, Sphere *s, Intersected *i);

void castAllRays(double, double, double, double, int, int, Point, Sphere *s);

#endif
