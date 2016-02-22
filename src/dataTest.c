#include <stdio.h>
#include <assert.h>
#include "data.h"

void testCreatePoint1() {
   Point p = CreatePoint(1.0, 2.0, 3.0);
   assert(p.x == 1.0);
   assert(p.y == 2.0);
   assert(p.z == 3.0);
}

void testCreatePoint2() {
   Point p = CreatePoint(2.0, 4.0, 6.0);
   assert(p.x == 2.0);
   assert(p.y == 4.0);
   assert(p.z == 6.0);
}

void testCreatePoint3() {
   Point p = CreatePoint(1.71, 3.57, 3.78);
   assert(p.x == 1.71);
   assert(p.y == 3.57);
   assert(p.z == 3.78);
}

void testCreatePoint4() {
   Point p = CreatePoint(0.8912, -4.567, 15.634);
   assert(p.x == 0.8912);
   assert(p.y == -4.567);
   assert(p.z == 15.634);
}

void testPoints() {
   testCreatePoint1();
   testCreatePoint2();
   testCreatePoint3();
   testCreatePoint4();
}

void testCreateVector1() {
   Vector v = CreateVector(1.0, 2.0, 3.0);
   assert(v.x == 1.0);
   assert(v.y == 2.0);
   assert(v.z == 3.0);
}

void testCreateVector2() {
   Vector v = CreateVector(2.0, 4.0, 6.0);
   assert(v.x == 2.0);
   assert(v.y == 4.0);
   assert(v.z == 6.0);
}

void testCreateVector3() {
   Vector v = CreateVector(0.9, 0.75,-5.6);
   assert(v.x == 0.9);
   assert(v.y == 0.75);
   assert(v.z == -5.6);
}

void testVectors() {
   testCreateVector1();
   testCreateVector2();
   testCreateVector3();
}

int main() {
   testPoints();
   testVectors();
   printf("All data tests passed\n");
}
