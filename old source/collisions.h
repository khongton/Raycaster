#ifndef COLLISIONS_H
#define COLLISIONS_H

struct maybe_point
{
	int isPoint;
	struct point p;
};

struct maybe_point create_maybe_point(int isPoint, struct point p);

struct maybe_point sphere_intersection_point(struct ray r, struct sphere s);

int find_intersection_points(struct sphere spheres[], int num_spheres,
	struct ray r, struct sphere hit_spheres[], 
	struct point intersection_points[]);

struct vector sphere_normal_at_point(struct sphere s, struct point p);

#endif
