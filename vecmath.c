#include "data.h"
#include <math.h>

Vector ScaleVector(Vector toScale, double scalar) {
   Vector scaled;
   scaled.x = toScale.x * scalar;
   scaled.y = toScale.y * scalar;
   scaled.z = toScale.z * scalar;
   return scaled;
}

double DotProduct(Vector vec1, Vector vec2) {
   double xProd = vec1.x * vec2.x;
   double yProd = vec1.y * vec2.y;
   double zProd = vec1.z * vec2.z;

   return xProd + yProd + zProd;
}

double VectorLength(Vector vec) {
   double toRoot = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
   return sqrt(toRoot);
}

Vector NormalizeVector(Vector toNorm) {
   Vector toReturn;
   double length = VectorLength(toNorm);
   
   toReturn.x = toNorm.x / length;
   toReturn.y = toNorm.y / length;
   toReturn.z = toNorm.z / length;

   return toReturn;
}

Vector PointDiff(Point point1, Point point2) {
   Vector pDiff;

   pDiff.x = point1.x - point2.x;
   pDiff.y = point1.y - point2.y;
   pDiff.z = point1.z - point2.z;

   return pDiff;
}

Vector VecDiff(Vector vec1, Vector vec2) {
   Vector vDiff;

   vDiff.x = vec1.x - vec2.x;
   vDiff.y = vec1.y - vec2.y;
   vDiff.z = vec1.z - vec2.z;

   return vDiff;
}

Point TranslatePoint(Point toTrans, Vector dir) {
   Point newPoint;

   newPoint.x = toTrans.x + dir.x;
   newPoint.y = toTrans.y + dir.y;
   newPoint.z = toTrans.z + dir.z;

   return newPoint;
}

Vector fromTo(Point from, Point to) {
   return PointDiff(to, from);
}
