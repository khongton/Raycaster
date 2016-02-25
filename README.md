# Raycaster
A simple ray caster from a viewpoint onto some spheres in a scene. 
More detailed information can be found in the Wiki page.

Sample output of two spheres: 

![image](https://github.com/khongton/Raycaster/blob/master/images/image.png)

#Usage

Clone the repository and compile using the compile.sh script. The compiler used to build this project is gcc. 
The input files needed by the program are text files, with each line specifying 11 double-floating point numbers, like so:

1.0 1.0 0.0 2.0 1.0 0.0 1.0 0.2 0.4 0.5 0.05

8.0 -10.0 110.0 100.0 0.2 0.2 0.6 0.4 0.8 0.0 0.05

The 11 numbers are necessary in order to properly build a sphere in the scene.
Execute a.out. Instructions will appear on proper usage.

Last edit: 2/25/16 9:49
