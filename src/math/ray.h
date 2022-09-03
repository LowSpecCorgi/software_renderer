#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct {
    v3_point3 origin;
    v3_vec3 direction;
} ry_ray;

ry_ray ry_new_ray(v3_point3 origin, v3_vec3 direction);
v3_point3 ry_at(ry_ray ray, double t);

#endif