#include <stdio.h>
#include <assert.h>
#include "data.h"

void testScale1() {
   Vector v = CreateVector(1.0, 2.0, 3.0);
   Vector scaled = ScaleVector(v, 2.0);

   assert(scaled.x == 2.0);
   assert(scaled.y == 4.0);
   assert(scaled.z == 6.0);
}

void testScale2() {
   Vector v = CreateVector(2.0, 4.0, 6.0);
   Vector scaled = ScaleVector(v, 3.0);

   assert(scaled.x == 6.0);
   assert(scaled.y == 12.0);
   assert(scaled.z == 18.0);
}

void testScale() {
   testScale1();
   testScale2();
}