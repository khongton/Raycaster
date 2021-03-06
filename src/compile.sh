#!/bin/bash

case $1 in
   -data)
      gcc -Wall -Werror -lm -std=c99 -pedantic data.c dataTest.c;;
   -vec)
      gcc -Wall -Werror -lm -std=c99 -pedantic data.c vecmath.c vecmathTest.c;;
   -intersect)
      gcc -Wall -Werror -lm -std=c99 -pedantic data.c vecmath.c collisions.c collisiontest.c;;
   -cast)
      gcc -Wall -Werror -lm -std=c99 -pedantic data.c vecmath.c collisions.c cast.c driver.c;;
   -dist)
      gcc -Wall -Werror -lm -std=c99 -pedantic data.c vecmath.c collisions.c cast.c distanceDriver.c;;
   -main)
      gcc -Wall -Werror -lm -std=c99 -pedantic data.c vecmath.c collisions.c cast.c cmdline.c raycaster.c;;
   -g)
      gcc -g -Wall -Werror -lm -std=c99 -pedantic data.c vecmath.c collisions.c cast.c cmdline.c raycaster.c;;
   -h)
      echo "-data for data struct tests"
      echo "-vec for vector math tests"
      echo "-intersect for intersection tests"
      echo "-cast for casting tests"
      echo "-dist for checking distance"
      echo "-main for main program"
      echo "-g to debug raycaster";;
   *)
      echo "-h for help"
      exit;;
esac 

