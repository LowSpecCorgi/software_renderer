#include "ray.h"

ry_ray ry_new_ray(v3_point3 origin, v3_vec3 direction) {
    ry_ray ray = {origin, direction};

    return ray;
}

v3_point3 ry_at(ry_ray ray, double t) {
    return v3_add(ray.origin, v3_multiply_scalar(ray.direction, t));
}