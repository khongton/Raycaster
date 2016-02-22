#ifndef VECMATH_H
#define VECMATH_H
#include "data.h"

/* Scale a vector given a scalar value 
 * Used to determine if a vector intersects a sphere*/ 
Vector ScaleVector(Vector toScale, double scalar);

/* Compute the dot product of two vectors.
 * Used to determine if a point is on the sphere. */
double DotProduct(Vector vec1, Vector vec2);

/* Return the length of a given vector */
double VectorLength(Vector len);

/* Return a normal vector. 
 * Will be used to determine if point is visible to the viewer.*/
Vector NormalizeVector(Vector toNormalize);

/* Produces a vector given the difference of two points.
 * This gives us a vector we can use to find whether or not
 * a point is on the sphere or not. */
Vector PointDiff(Point point1, Point point2);

/* Produces a vector given the difference of two vectors */
Vector VecDiff(Vector vec1, Vector vec2);

/* Slides a point along a vector.
 * Will be used to determine if any point along
 * the vector intersects the sphere. */
Point TranslatePoint(Point toTrans, Vector dir);

/* A convenience function to enhance readability.
 * Same functionality as point difference. */
Vector fromTo(Point from, Point to);

#endif
