#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "data.h"
#include "vecmath.h"
#include "collisions.h"
#include "cast.h"

void distanceTest1() {
   Point p1 = CreatePoint(-7.0, -4.0, 3.0);
   Point p2 = CreatePoint(17.0, 6.0, 2.5);

   printf("**Distance Test 1**\n");
   double result = distance(p1, p2);
   printf("Actual: %lf\n", result);
   printf("Expected: 26.004807\n");
}

void distanceTest2() {
   Point p1 = CreatePoint(12.5, 65.3, 102);
   Point p2 = CreatePoint(1, 2, 3);
   printf("\n**Distance Test 2**\n");
   double result = distance(p1, p2);
   printf("Actual: %lf\n", result);
   printf("Expected: 118.06837\n");
}

void basicDistanceTests() {
   distanceTest1();
   distanceTest2();
}

void closestPoint1() {
   Point origin = CreatePoint(0, 0, 0);
   Point p1 = CreatePoint(5, 5, 5);
   Point p2 = CreatePoint(1, 1, 1);
  
   double p1Dist = distance(origin, p1);
   double p2Dist = distance(origin, p2);

   printf("\n**Finding Closest Point 1**\n");
   printf("Expected: p2Dist should be closer/smaller.\n");
   printf("Actual distance: p1 - %lf, p2 - %lf\n", p1Dist, p2Dist);
}

void closestPoint2() {
   Point origin = CreatePoint(0, 0, -14);
   Point p1 = CreatePoint(2, 5, 2); //16.88
   Point p2 = CreatePoint(1, 6, 1); //16.18

   double p1Dist = distance(origin, p1);
   double p2Dist = distance(origin, p2);
   
   printf("\n**Finding Closest Point 2**\n");
   printf("Expected: p2Dist should be closer/smaller.\n");
   printf("Actual distance: p1 - %lf, p2 - %lf\n", p1Dist, p2Dist);
}

void closestPoint3() {
   Point origin = CreatePoint(0, 0, -14);
   Point p1 = CreatePoint(-1.2, 4.5, 2.3);
   Point p2 = CreatePoint(-1.2, 2.3, 5.6);

   double p1Dist = distance(origin, p1);
   double p2Dist = distance(origin, p2);

   printf("\n**Finding Closest Point 3**\n");
   printf("Expected p1Dist should be closer/smaller.\n");
   printf("Actual distance: p1 - %lf, p2 - %lf\n", p1Dist, p2Dist);
}

void closestPointTests() {
   closestPoint1();
   closestPoint2();
   closestPoint3();
}

int main() {
   basicDistanceTests();
   closestPointTests();
   return 0;
}
