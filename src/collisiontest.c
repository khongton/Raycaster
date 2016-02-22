#include <stdio.h>
#include <assert.h>
#include "data.h"

void testIntersection1() {
   //Doesn't pass
   Point sp = CreatePoint(0.0, 2.0, 0.0);
   Sphere s = CreateSphere(sp, 1.0);

   Point rp = CreatePoint(0.0, 0.0, 0.0);
   Vector dir = CreateVector(0.0, 1.0, 0.0);
   Ray r = CreateRay(rp, dir);

   MaybePoint mp = SphereIntersectionPoint(r, s);

   printf("Intersection 1: Along y-axis.\n");
   assert(mp.isPoint == 1);
   printf("Expected: 0.0, 1.0, 0.0\n");
   printf("Actual: %.1f, %.1lf, %.1lf\n", mp.p.x, mp.p.y, mp.p.z);
}

void testIntersection2() {
   Point sp = CreatePoint(0.0, 0.0, 0.0);
   Sphere s = CreateSphere(sp, 1.0);

   Point rp = CreatePoint(0.0, 0.0, 0.0);
   Vector dir = CreateVector(1.0, 0.0, 0.0);
   Ray r = CreateRay(rp, dir);

   MaybePoint mp = SphereIntersectionPoint(r, s);

   printf("\nIntersection 2: From within sphere at origin.\n");
   assert(mp.isPoint == 1);
   printf("Actual: %.1lf %.1lf %.1lf\n", mp.p.x, mp.p.y, mp.p.z);
   printf("Expected: 1.0, 0.0, 0.0\n");
}

void testIntersection3() {
   Point sp = CreatePoint(1.0, 1.0, 0.0);
   Sphere s = CreateSphere(sp, 1.0);

   Point rp = CreatePoint(0.0, 0.0, 0.0);
   Vector dir = CreateVector(1.0, 0.0, 0.0);
   Ray r = CreateRay(rp, dir);

   MaybePoint mp = SphereIntersectionPoint(r, s);
   printf("\nIntersection 3: Single intersection at <1,0,0>.\n");
   assert(mp.isPoint == 1);
   printf("Expected: 1.0, 0.0, 0.0\n");
   printf("Actual: %.1lf, %.1lf, %.1lf\n", mp.p.x, mp.p.y, mp.p.z);
}

void testIntersection4() {
   Point sp = CreatePoint(2.0, 2.0, 0.0);
   Sphere s = CreateSphere(sp, 1.0);

   Point rp = CreatePoint(0.0, 0.0, 0.0);
   Vector dir = CreateVector(1.0, 0.0, 0.0);
   Ray r = CreateRay(rp, dir);

   MaybePoint mp = SphereIntersectionPoint(r,s);
   printf("\nIntersection 4: No intersection.\n");
   assert(mp.isPoint == 0);
   printf("If this prints, test4 passed\n");
}

void testIntersection5() {
   Point sp = CreatePoint(0.0, 0.0, 0.0);
   Sphere s = CreateSphere(sp, 4.0);

   Point rp = CreatePoint(0.0, 2.0, -4.0);
   Vector dir = CreateVector(0.658281, -0.557005, 0.506370);
   Ray r = CreateRay(rp, dir);

   MaybePoint mp = SphereIntersectionPoint(r,s);

   printf("\nIntersection 5: Sphere at origin, ray through sphere.\n");
   assert(mp.isPoint == 1);
   printf("Expect: 0.47362624786864, 1.599239329218808, -3.635672117471643\n");
   printf("Actual: %lf, %lf, %lf\n", mp.p.x, mp.p.y, mp.p.z);
}

void testIntersection6() {
   Point sp = CreatePoint(0.0, -2.0, 0.0);
   Sphere s = CreateSphere(sp, 1.0);

   Point rp = CreatePoint(0.0, 0.0, 0.0);
   Vector dir = CreateVector(0.0, 1.0, 0.0);
   Ray r = CreateRay(rp, dir);

   MaybePoint mp = SphereIntersectionPoint(r,s);

   printf("\nIntersection 6: Sphere \"behind\" ray; does not intersect\n");
   assert(mp.isPoint == 0);
   printf("If this prints, it works\n");
}

void testSphereNormal1() {
   Point sp = CreatePoint(0.0, 0.0, 0.0);
   Sphere s = CreateSphere(sp, 4.0);

   Point p = CreatePoint(0.0, 0.0, 4.0);
   Vector n = SphereNormalAt(s, p);

   printf("\nNormal 1: Along z-axis for origin-centered sphere.\n");
   printf("Expected: 0.0, 0.0, 1.0\n");
   printf("Actual: %.1lf, %.1lf, %.1lf\n", n.x, n.y, n.z);
}

void testSphereNormal2() {
   Point sp = CreatePoint(0.0, 0.0, 0.0);
   Sphere s = CreateSphere(sp, 4.0);

   Point p = CreatePoint(0.0, 4.0, 0.0);
   Vector n = SphereNormalAt(s, p);

   printf("\nNormal 2: Along y-axis for origin-centered sphere.\n");
   printf("Expected: 0.0, 1.0, 0.0\n");
   printf("Actual: %.1lf, %.1lf, %.1lf\n", n.x, n.y, n.z);
}

void testSphereNormal3() {
   Point sp = CreatePoint(0.0, 0.0, 0.0);
   Sphere s = CreateSphere(sp, 4.0);

   Point p = 
      CreatePoint(0.47362624786864, 1.599239329218808, -3.635672117471643);

   Vector n = SphereNormalAt(s, p);
   printf("\nNormal 3: Less obvious test case.\n");
   printf("Expected: 0.118406567967, 0.399809832305. -0.908978029368\n");
   printf("Actual: %lf, %lf, %lf\n", n.x, n.y, n.z);
}

void testIntersections() {
   testIntersection1();
   testIntersection2();
   testIntersection3();
   testIntersection4();
   testIntersection5();
   testIntersection6();
}

void testSphereNormals() {
   //successful - fromto works, pointdiff works as expected
   testSphereNormal1();
   testSphereNormal2();
   testSphereNormal3();
}

void testFindPoints1() {
   int numSpheres = 4, hits;
   Sphere spheres[4];
   Sphere sphereHit[4];
   Point pointHit[4];
   Intersected list;
   list.hitSpheres = sphereHit;
   list.hitPoints = pointHit;

   Ray ray = CreateRay(CreatePoint(0.0, 0.0, 0.0), CreateVector(0.0, 1.0, 0.0));
   spheres[0] = CreateSphere(CreatePoint(0.0, 2.0, 0.0), 1.0);
   spheres[1] = CreateSphere(CreatePoint(0.0, 5.0, 0.0), 1.0);
   spheres[2] = CreateSphere(CreatePoint(0.0, -4.0, 0.0), 1.0);
   spheres[3] = CreateSphere(CreatePoint(0.0, 8.0, 0.0), 1.0);
   hits = FindIntersectionPoints(spheres, ray, numSpheres, &list);

   printf("\nFind intersection 1: hits 3/4 of spheres\n");
   assert(hits == 3);
   printf("3 spheres were hit\n");
   
   assert(sphereHit[0].center.x == spheres[0].center.x);
   assert(sphereHit[0].center.y == spheres[0].center.y);
   assert(sphereHit[0].center.z == spheres[0].center.z);
   assert(pointHit[0].x == 0.0);
   assert(pointHit[0].y == 1.0);
   assert(pointHit[0].z == 0.0);

   assert(sphereHit[1].center.x == spheres[1].center.x);
   assert(sphereHit[1].center.y == spheres[1].center.y);
   assert(sphereHit[1].center.z == spheres[1].center.z);
   assert(pointHit[1].x == 0.0);
   assert(pointHit[1].y == 4.0);
   assert(pointHit[1].z == 0.0);

   assert(sphereHit[2].center.x == spheres[3].center.x);
   assert(sphereHit[2].center.y == spheres[3].center.y);
   assert(sphereHit[2].center.z == spheres[3].center.z);
   assert(pointHit[2].x == 0.0);
   assert(pointHit[2].y == 7.0);
   assert(pointHit[2].z == 0.0);
   printf("FindPoints1 passed\n");
}

void testFindPoints2() {
   int numSpheres = 4, hits;
   Sphere spheres[4];
   Sphere sphereHit[4];
   Point pointHit[4];
   Ray ray = CreateRay(CreatePoint(0.0, 0.0, 0.0), CreateVector(0.0, 0.0, 1.0));
   Intersected list;
   list.hitSpheres = sphereHit;
   list.hitPoints = pointHit;

   spheres[0] = CreateSphere(CreatePoint(0.0, 2.0, 0.0), 1.0);
   spheres[1] = CreateSphere(CreatePoint(0.0, 5.0, 0.0), 1.0);
   spheres[2] = CreateSphere(CreatePoint(0.0, -4.0, 0.0), 1.0);
   spheres[3] = CreateSphere(CreatePoint(0.0, 8.0, 0.0), 1.0);

   hits = FindIntersectionPoints(spheres, ray, numSpheres, &list);
   printf("\nFind intersection 2: no hits\n");
   assert(hits == 0);
   printf("Test 2 passed\n");
}

void testFindPoints3() {
   int numSpheres = 0, hits = 0;
   Ray ray = CreateRay(CreatePoint(0.0, 0.0, 0.0), CreateVector(0.0, 0.0, 1.0));
   hits = FindIntersectionPoints(NULL, ray, numSpheres, NULL);
   printf("\nFind Intersection points 3: zero spheres passed.\n");
   assert(hits == 0);
   printf("Test 3 passed\n");
}

void testFindPoints() {
   testFindPoints1();
   testFindPoints2();
   testFindPoints3();
}

int main() {
   testIntersections();
   testFindPoints();
}
