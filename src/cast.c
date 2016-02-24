#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "data.h"
#include "vecmath.h"
#include "collisions.h"
#include "cast.h"

#define MAX_COLOR 255
#define POINT_EPSILON 0.01

/* Private data structures for types of color contribution */
typedef struct {
   double red;
   double green;
   double blue;
} Ambient, Diffuse, Specular;

/* Initialize a canvas struct to compartmentalize input data */
void InitCanvas(Canvas *pic, double minX, double maxX, double minY, double maxY, int width, int height) {
   pic->minWidth = minX;
   pic->maxWidth = maxX;
   pic->minHeight = minY;
   pic->maxHeight = maxY;
   pic->picWidth = width;
   pic->picHeight = height;
}

/* Initialize a pixel struct that holds data relevant to computing color */
void InitPixel(Pixel *pixel, Sphere sphere, MaybePoint mbp, Color ambient, Light light) {
   pixel->sphere = sphere;
   pixel->mbp = mbp;
   pixel->ambient = ambient;
   pixel->light = light;
   pixel->sphereNorm = SphereNormalAt(sphere, mbp.p);
   pixel->offPoint = TranslatePoint(mbp.p, ScaleVector(pixel->sphereNorm, POINT_EPSILON));
}

double distance(Point p1, Point p2) {
   double dx = p2.x - p1.x;
   double dy = p2.y - p1.y;
   double dz = p2.z - p1.z;

   return sqrt(dx*dx + dy*dy + dz*dz);
}


/* Convert double-representation of color to P3 readable int */
int convertColor(double doubleVal) {
   double temp = doubleVal * MAX_COLOR;
   if (temp > MAX_COLOR)
      return MAX_COLOR;
   else if (temp < 0)
      return 0;
   else 
      return (int) temp;
}

/* Compute the ambient light component's addition to the sphere color. 
 * 
 * This component displays how the sphere would look without light. */
Ambient computeAmbient(Sphere sphere, Color ambient) {
   Ambient amb;

   amb.red = sphere.color.red  * sphere.finish.ambient * ambient.red;
   amb.green = sphere.color.green * sphere.finish.ambient * ambient.green;
   amb.blue = sphere.color.blue * sphere.finish.ambient * ambient.blue;

   return amb;
}

/* Compute the diffusion of light component's addition to sphere color. 
 * If the light is not visible from the point of intersection, then it
 * does not contribute to the color. 
 *
 * This component gives depth to the scene. */
Diffuse computeDiffuse(Pixel *pixel, Sphere *spheres, Intersected *list) {
   Diffuse diffuse;
   diffuse.red = 0.0;
   diffuse.green = 0.0;
   diffuse.blue = 0.0;
   
   Vector pointToLight = fromTo(pixel->offPoint, pixel->light.position);  //
   Vector lightNormal = NormalizeVector(pointToLight); //used in dotprod
 
   //Light is not visible is result non-positive
   double result = DotProduct(pixel->sphereNorm, lightNormal);
   if (result <= 0.0)
      result = 0.0;

   Ray lightRay = CreateRay(pixel->offPoint, pointToLight);
   int collisions = FindIntersectionPoints(spheres, lightRay, 2, list);
   if (!collisions) {
      diffuse.red = result * pixel->light.color.red * pixel->sphere.color.red * pixel->sphere.finish.diffuse;
      diffuse.green = result * pixel->light.color.green * pixel->sphere.color.green * pixel->sphere.finish.diffuse;
      diffuse.blue = result * pixel->light.color.blue * pixel->sphere.color.blue * pixel->sphere.finish.diffuse;
   }
   return diffuse;
}

/* Compute the specular component of light's addition to sphere color.
 * If the light is not visible from the point of intersection, then it
 * doesn't contribute to the color. 
 *
 * This component gives the sphere a glossy finish.*/
Specular computeSpec(Pixel *pixel, Intersected *list, Point eye) {
   Specular spec;
   spec.red = 0.0;
   spec.green = 0.0;
   spec.blue = 0.0;
   double roughVal = 1 / pixel->sphere.finish.roughness;

   Vector pointToLight = fromTo(pixel->offPoint, pixel->light.position);  
   Vector lightNormal = NormalizeVector(pointToLight); 
   Vector eyeDir = fromTo(pixel->offPoint, eye); 
   double result = DotProduct(pixel->sphereNorm, lightNormal);
   Vector reflect = VecDiff(ScaleVector(pixel->sphereNorm, 2 * result), lightNormal);
   double specIntensity = DotProduct(reflect, NormalizeVector(eyeDir));
 
   //Color has specular component if the specular intensity is non-negative
   if (specIntensity > 0) {
      double intensity = pow(specIntensity, roughVal);
      spec.red = pixel->light.color.red * pixel->sphere.finish.specular * intensity;
      spec.green = pixel->light.color.green * pixel->sphere.finish.specular * intensity;
      spec.blue = pixel->light.color.blue * pixel->sphere.finish.specular * intensity;
   }
   return spec;
}

/* Calculate the color contribution of light and ambient color to the sphere's color. */
Color computeFinish(Sphere sphere, MaybePoint mbp, Color ambient, Light light, Sphere *spheres,
      Intersected *list, Point eye) {
   Color color;
   Ambient ambientComp;
   Diffuse diffuseComp;
   Specular specComp;
   Pixel pixel;
   InitPixel(&pixel, sphere, mbp, ambient, light);

   ambientComp = computeAmbient(sphere, ambient);
   diffuseComp = computeDiffuse(&pixel, spheres, list);
   specComp = computeSpec(&pixel, list, eye);

   color.red = ambientComp.red + diffuseComp.red + specComp.red;
   color.green = ambientComp.green + diffuseComp.green + specComp.green;
   color.blue = ambientComp.blue + diffuseComp.blue + specComp.blue;
   return color;
}

Color castRay(int numHits, Ray ray, Intersected *list, Color ambient,
      Light light, Sphere *spheres, Point eye) {
   MaybePoint mbp = SphereIntersectionPoint(ray, list->hitSpheres[0]), mbp2;
   Sphere closest = list->hitSpheres[0];
   
   for (int sphereIndex = 1; sphereIndex < numHits; sphereIndex++) {
      mbp2 = SphereIntersectionPoint(ray, list->hitSpheres[sphereIndex]);
      if (distance(ray.pt, mbp.p) > distance(ray.pt, mbp2.p)) {
         mbp = mbp2;
         closest = list->hitSpheres[sphereIndex];
      }
   }
   return computeFinish(closest, mbp, ambient, light, spheres, list, eye);
}

void castAllRays(Canvas *pic, Point eye, Sphere *spheres, Color ambient, Light light) {
   int numHits;
   double curWidth, curHeight;
   double pixWidth = (pic->maxWidth  - pic->minWidth)/pic->picWidth;
   double pixHeight = (pic->maxHeight - pic->minHeight)/pic->picHeight;

   Intersected list;
   Sphere sphereHit[sizeof(spheres)];
   Point pointHit[sizeof(spheres)];
   list.hitSpheres = sphereHit;
   list.hitPoints = pointHit;
   
   Point p;
   Vector v;
   Ray r;
   Color sphereColor;

   printf("P3\n%d %d %d\n", pic->picWidth, pic->picHeight, MAX_COLOR);
   for (curHeight = pic->maxHeight; curHeight > pic->minHeight; curHeight -= pixHeight) {
      for (curWidth = pic->minWidth; curWidth < pic->maxWidth; curWidth += pixWidth) {
         p = CreatePoint(curWidth, curHeight, 0.0);
         v = fromTo(eye, p);
         r = CreateRay(eye, v);
         if ((numHits = FindIntersectionPoints(spheres, r, 2, &list))) {
            sphereColor = castRay(numHits, r, &list, ambient, light, spheres, eye);
            printf("%d %d %d\n",
                  convertColor(sphereColor.red),
                  convertColor(sphereColor.green),
                  convertColor(sphereColor.blue));
         }
         else {
            printf("%d %d %d\n", MAX_COLOR, MAX_COLOR, MAX_COLOR);
         }
      }
   }
}
