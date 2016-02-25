#include <math.h>
#include "data.h"
#include "vector_math.h"

struct vector scale_vector(struct vector v, double s)
{
	struct vector new;
	new.x=v.x*s;
	new.y=v.y*s;
	new.z=v.z*s;
	return new;
}

double dot_vector(struct vector a, struct vector b)
{
	double c=a.x*b.x;
	double d=a.y*b.y;
	double e=a.z*b.z;
	return c+d+e;
}

double length_vector(struct vector v)
{
	double a=v.x*v.x;
	double b=v.y*v.y;
	double c=v.z*v.z;
	return sqrt(a+b+c);
}

struct vector normalize_vector(struct vector v)
{
	double a;
	a=v.x/length_vector(v);
	double b;
	b=v.y/length_vector(v);
	double c;
	c=v.z/length_vector(v);
	struct vector new;
	new.x=a;
	new.y=b;
	new.z=c;
	return new;
}
	
struct vector difference_point(struct point a, struct point b)
{
	double c=b.x-a.x;
	double d=b.y-a.y;
	double e=b.z-a.z;
	struct vector pointed;
	pointed.x=c;
	pointed.y=d;
	pointed.z=e;
	return pointed;
}

struct vector difference_vector(struct vector a, struct vector b)
{
	double c=b.x-a.x;
	double d=b.y-a.y;
	double e=b.z-a.z;
	struct vector newvector;
	newvector.x=c;
	newvector.y=d;
	newvector.z=e;
	return newvector;
}

struct point translate_point(struct point p, struct vector v)
{
	double a=p.x+v.x;
	double b=p.y+v.y;
	double c=p.z+v.z;
	struct point translate;
	translate.x=a;
	translate.y=b;
	translate.z=c;
	return translate;
}

struct vector vector_from_to(struct point from, struct point to)
{
	double a=to.x-from.x;
	double b=to.y-from.y;
	double c=to.z-from.z;
	struct vector fromto;
	fromto.x=a;
	fromto.y=b;
	fromto.z=c;
	return fromto;
}

	
	

	 
