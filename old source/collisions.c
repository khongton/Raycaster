#include <math.h>
#include "data.h"
#include "vector_math.h"
#include "collisions.h"
#include <stdio.h>

struct maybe_point create_maybe_point(int isPoint, struct point p)
{
	struct maybe_point mp;
	mp.isPoint=isPoint;
	mp.p=p;
	return mp;
}	

struct maybe_point sphere_intersection_point(struct ray r, struct sphere s)
{
	struct vector quadvector=difference_point(s.center,r.point);
	double a=dot_vector(r.vector,r.vector);
	double b=2*dot_vector(quadvector,r.vector);
	double c=dot_vector(quadvector,quadvector)-(s.radius*s.radius);
		
	double discrim=(b*b-4*a*c);
       	double root1=(-b+sqrt(discrim))/(2*a);
	double root2=(-b-sqrt(discrim))/(2*a);

	if(root1>0 && root2<0)
	{	
		int isPoint=1;
		struct vector scale=scale_vector(r.vector,root1);
		struct point p=translate_point(r.point,scale);
		struct maybe_point maybe_point=create_maybe_point(isPoint, p);
		return maybe_point;
	}
	else if(root1<0 && root2>0)
	{
		int isPoint=1;
		struct vector scale=scale_vector(r.vector,root2);
		struct point p=translate_point(r.point,scale);
		struct maybe_point maybe_point=create_maybe_point(isPoint, p);
		return maybe_point;
	}		
	else if(root1==0 && root2<0)
	{
		int isPoint=1;
		struct vector scale=scale_vector(r.vector,root1);
		struct point p=translate_point(r.point,scale);
		struct maybe_point maybe_point=create_maybe_point(isPoint, p);
		return maybe_point;
	}
	else if(root1<0 && root2==0)
	{
		int isPoint=1;
		struct vector scale=scale_vector(r.vector,root2);
		struct point p=translate_point(r.point,scale);
		struct maybe_point maybe_point=create_maybe_point(isPoint, p);
		return maybe_point;
	}
	else if(root1<0 && root2<0)
	{
		int isPoint=0;
		struct point p=create_point(0,0,0);
		struct maybe_point maybe_point=create_maybe_point(isPoint,p);
		return maybe_point;
	}
	else if(root1>0 && root2>0)
	{
	int isPoint=1;
	{
	if(root1>root2)
	  {
	    struct vector scale=scale_vector(r.vector,root2);
	    struct point p=translate_point(r.point,scale);
	    struct maybe_point maybe_point=create_maybe_point(isPoint,p);
	    return maybe_point;
	  }
	else if(root2>root1)
	  {
	    struct vector scale=scale_vector(r.vector,root1);
	    struct point p=translate_point(r.point,scale);
	    struct maybe_point maybe_point=create_maybe_point(isPoint,p);
	    return maybe_point;
	  }
	}
	}	 	
	int isPoint=0;
	struct point p=create_point(0,0,0);
 	struct maybe_point maybe_point=create_maybe_point(isPoint,p);
	return maybe_point;			
}

int find_intersection_points(struct sphere spheres[],int num_spheres,struct ray r,
				struct sphere hit_spheres[], struct point intersection_points[])
{
	int x=0; 
	for(int i=0; i<num_spheres;i++)
	{
		struct maybe_point maybe_point;
		maybe_point=sphere_intersection_point(r,spheres[i]);
		if(maybe_point.isPoint==1)
		{
			hit_spheres[x]=spheres[i];
			intersection_points[x]=maybe_point.p;
			x++;
		}
		else
		{
			return 0;
		}
	}
	return x;
}

struct vector sphere_normal_at_point(struct sphere s, struct point p)
{
	struct vector fromto=vector_from_to(p, s.center);
	struct vector normal=normalize_vector(fromto);
	return normal;
}

