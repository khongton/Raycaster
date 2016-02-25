#ifndef DATA_H
#define DATA_H

struct finish
{
	double ambient;
	double diffuse;
	double specular;
	double roughness;
};

struct color
{
	double r;
	double g;
	double b;
};

struct point
{
	double x;
	double y;
	double z;
};

struct vector
{
	double x;
	double y;
	double z;
};

struct ray
{
	struct point point;
	struct vector vector;
};

struct sphere
{
	struct point center;
	double radius;
	struct color color;
	struct finish ambient;
};

struct light
{
	struct point p;
	struct color color;
};

struct finish create_finish(double ambient, double diffuse, double specular,
   double roughness);

struct color create_color(double r, double g, double b);

struct point create_point(double x, double y, double z);

struct vector create_vector(double x, double y, double z);

struct ray create_ray(struct point p, struct vector v);

struct sphere create_sphere(struct point c, double r, struct color color,
	struct finish ambient);
 
struct light create_light(struct point p, struct color color);

#endif
