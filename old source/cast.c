#include <math.h>
#include <stdio.h>
#include "data.h"
#include "vector_math.h"
#include "collisions.h"

double distance(struct point p1, struct point p2)
{
  return sqrt(pow((p2.x-p1.x),2)+pow((p2.y-p1.y),2)+pow((p2.z-p1.z),2));
}

struct color cast_ray(struct ray r, struct sphere spheres[], int num_spheres, 
   struct color ambient_light, struct light light, struct point eye)
{    
   int index_sphere = 0;
   struct maybe_point maybe_point;
   maybe_point = sphere_intersection_point(r, spheres[0]);
   for (int i = 1; i < num_spheres; i++)
   {
      struct maybe_point maybe_point2;
      maybe_point2= sphere_intersection_point(r,spheres[i]);
      if ( distance(r.point,maybe_point.p) > distance(r.point,maybe_point2.p))
      {
         maybe_point.p = maybe_point2.p;
         index_sphere = i;
      }
   }  
   if (maybe_point.isPoint==0)
   {
     struct color ambient_light=create_color(1.0,1.0,1.0);
     return ambient_light;
   }  
      
   struct vector normal = sphere_normal_at_point(spheres[index_sphere],
      maybe_point.p);
   struct vector normal_scale = scale_vector(normal,0.01);
   struct point pz = translate_point(maybe_point.p,normal_scale);
   struct vector to_light = vector_from_to(pz, light.p);
   struct vector light_dir = normalize_vector(to_light);
   double light_value = dot_vector(normal,light_dir);
   
   struct point intersection_points[num_spheres];	
   struct ray obscure = create_ray(light.p,light_dir);
   double diffuse = 0.4*1.5*light_value;
   
   int collisions = find_intersection_points(spheres,num_spheres,obscure,
      spheres,intersection_points);
   struct sphere obscured = spheres[index_sphere];
   if ( collisions > 0)
   {
      obscured.color.r = obscured.color.r*0.4;
      obscured.color.g = obscured.color.g;
      obscured.color.b = obscured.color.b*0.2;
      return obscured.color;
   }
      
   struct sphere sphere_no_light = spheres[index_sphere];
   if (light_value < 0)
   {
      sphere_no_light.color.r = sphere_no_light.color.r*0.4;
      sphere_no_light.color.g = sphere_no_light.color.g;
      sphere_no_light.color.b = sphere_no_light.color.b*0.2;   
      return sphere_no_light.color;
   }
   else
   {
     light_value = light_value;
   }
  
   double light_dot = 2*light_value;
   struct vector scale_light = scale_vector(normal,light_dot);
   struct vector reflection = difference_vector(light_dir,scale_light);
   struct vector to_viewer = vector_from_to(eye,pz);
   struct vector viewer_dir = normalize_vector(to_viewer);
   double specular_intensity = dot_vector(viewer_dir,reflection);

   struct sphere no_specular = spheres[index_sphere];
   if (specular_intensity < 0)
   {
      no_specular.color.r = no_specular.color.r*0.4+diffuse*no_specular.color.r;
      no_specular.color.g = no_specular.color.g+diffuse*no_specular.color.g;
      no_specular.color.b = no_specular.color.b*0.2+diffuse*no_specular.color.b;
      return no_specular.color;
   }
      
   double add_specular = 1.5*0.5*pow(specular_intensity,20);

   struct sphere unobscured = spheres[index_sphere];
   if (collisions == 0)
   {
      unobscured.color.r = unobscured.color.r*0.4+
         (diffuse*unobscured.color.r)+add_specular;
      unobscured.color.g = unobscured.color.g+
         (diffuse*unobscured.color.g)+add_specular;
      unobscured.color.b = unobscured.color.b*0.2+
         (diffuse*unobscured.color.b)+add_specular;
     }
     return unobscured.color;
   }

void cast_all_rays(double min_x, double max_x, double min_y, double max_y,
    int width, int height, struct point eye, struct sphere spheres[],
    int num_spheres, struct color ambient_light, struct light light)
{
   printf("P3 \n %d %d %d \n", width, height, 255);
   double w_pix = (max_x - min_x)/width;
   double h_pix = (max_y - min_y)/height;
   for(double i = min_y; i < max_y; i+= h_pix)
   {
      for(double j = min_x; j < max_x; j+= w_pix)
      {
         struct point p = create_point(j,i*-1,0.0);
         struct vector v = difference_point(eye,p);
         struct ray r = create_ray(eye,v);
         struct color color = cast_ray(r, spheres, num_spheres, ambient_light,
            light,eye);

         if (color.r > 1)
            color.r = 1.0;
         
         if (color.r < 0)
            color.r = 0.0;
           
         if (color.g > 1.0)
            color.g = 1.0;
        
         if (color.g < 0.0)
            color.g = 0.0;
        
         if (color.b > 1.0)
            color.b = 1.0;
      
         if (color.b < 0.0)
            color.b = 0.0;
         
         if (color.r ==  1 && color.g == 1 && color.b == 1)
         {
           printf("%d,%d,%d,\n",(int)ambient_light.r*255,
               (int)ambient_light.g*255, (int)ambient_light.b*255);
         }
         else 
         {
            printf("%d,%d,%d,\n",(int)(color.r*255),(int)(color.g*255),
               (int)(color.b*255)); 
         }   
      }//lol maybe fprintf ???? /?
   }
}


