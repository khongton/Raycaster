 #include "data.h"

struct light create_light(struct point p, struct color color) 
{
	struct light light;
	light.p = p;
	light.color = color;
	return light;
}


struct finish create_finish(double ambient, double diffuse, double specular,
   double roughness)
{
	struct finish finish;
	finish.ambient = ambient;
	finish.diffuse = diffuse;
        finish.specular = specular;
	finish.roughness = roughness;
	return finish;
}

struct color create_color(double r, double g, double b)
{
	struct color color;
	color.r=r;
	color.g=g;
	color.b=b;
	return color;
}

struct point create_point(double x, double y, double z)
{
	struct point p;
	p.x = x;
	p.y = y;
	p.z = z;
	return p;
}

struct vector create_vector(double x, double y, double z)
{
	struct vector dir;
	dir.x = x;
	dir.y = y;
	dir.z = z;
	return dir;
}

struct ray create_ray(struct point p, struct vector dir)
{
	struct ray r;
	r.point = p;
	r.vector = dir;
	return r;
}

struct sphere create_sphere(struct point center, double radius, 
   struct color color, struct finish ambient)
{
	struct sphere s;
	s.center = center;
	s.radius = radius;
	s.color=color;
	s.ambient=ambient;
	return s;
}

