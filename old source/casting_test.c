#include "checkit.h"
#include "data.h"
#include "vector_math.h"
#include "collisions.h"
#include "cast.h"

void cast_test()
{
   double min_x= -10;
   double max_x= 10;
   double min_y= -7.5;
   double max_y= 7.5;
   int width= 1024;
   int height= 768;
    
   struct point center1=create_point(1.0,1.0,0.0);
   double radius1=2.0;
   struct color blue = create_color(0.0,0.0,1.0);   
   struct finish ambient_fin1 = create_finish(0.4,0.4,0.5,0.05);

   struct point center2=create_point(0.5,1.5,-3.0);
   double radius2=0.5;
   struct color red = create_color(1.0,0.0,0.0);
   struct finish ambient_fin2 = create_finish(0.2,0.4,0.5,0.05);
   	
   struct point eye = create_point(0.0,0.0,-14.0);
   struct color ambient_light = create_color(1.0,1.0,1.0);
   
   struct point light_point = create_point(-100.0,100.0,-100.0);
   struct color light_color = create_color(1.5,1.5,1.5);
   struct light scene_light = create_light(light_point, light_color);

   int num_spheres = 2;
   struct sphere spheres[2];
   spheres[0] = create_sphere(center1,radius1,blue,ambient_fin1);
   spheres[1] = create_sphere(center2,radius2,red,ambient_fin2);
 
   cast_all_rays(min_x, max_x, min_y, max_y, width, height, eye, spheres,
    num_spheres, ambient_light, scene_light);
}

int main(void)
{
   cast_test();
   return 0;
}
