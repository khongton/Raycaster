#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

struct vector scale_vector(struct vector, double);

double dot_vector(struct vector, struct vector);

double length_vector(struct vector);

struct vector normalize_vector(struct vector);

struct vector difference_point(struct point, struct point);

struct vector difference_vector(struct vector, struct vector);

struct point translate_point(struct point, struct vector);

struct vector vector_from_to(struct point, struct point);

#endif
