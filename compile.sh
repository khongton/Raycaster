#!/bin/bash

case $1 in 
   -intersect)
      gcc -Wall -Werror -lm -std=c99 -pedantic data.c vecmath.c collisions.c collisiontest.c;;
   -cast)
      gcc -Wall -Werror -lm -std=c99 -pedantic data.c vecmath.c collisions.c cast.c driver.c;;
   -h)
      echo "-intersect for intersection tests"
      echo "-cast for casting tests"
      exit;;
esac 

