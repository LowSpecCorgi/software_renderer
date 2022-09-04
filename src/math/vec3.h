#ifndef VEC3_H
#define VEC3_H

#include <math.h>

typedef struct {
    double x;
    double y;
    double z;
} v3_vec3;

v3_vec3 v3_new(double x, double y, double z);

v3_vec3 v3_negate(v3_vec3 a);
v3_vec3 v3_add(v3_vec3 a, v3_vec3 b);
v3_vec3 v3_subtract(v3_vec3 a, v3_vec3 b);
v3_vec3 v3_multiply(v3_vec3 a, v3_vec3 b);

/*
Projection of b onto plane a
|a| * |b|  cosx
-> Commutative
*/
double v3_dot(v3_vec3 a, v3_vec3 b);

/*
Vector that is exactly 90 degrees to the other 2 vectors

Important for calculating normals

-> Non commutative
*/
v3_vec3 v3_cross(v3_vec3 a, v3_vec3 b);

v3_vec3 v3_normalise(v3_vec3 a);

v3_vec3 v3_multiply_scalar(v3_vec3 a, double t);
v3_vec3 v3_add_scalar(v3_vec3 a, double t);
v3_vec3 v3_subtract_scalar(v3_vec3 a, double t);
v3_vec3 v3_divide_scalar(v3_vec3 a, double t);

double v3_get_length(v3_vec3 a);
double v3_get_length_squared(v3_vec3 a);

// Type aliases
typedef v3_vec3 v3_point3;
typedef v3_vec3 v3_colour;

#endif