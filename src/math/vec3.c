#include "vec3.h"

v3_vec3 v3_new(double x, double y, double z) {
    v3_vec3 vector = {x, y, z};
    return vector;
}

v3_vec3 v3_negate(v3_vec3 a) {
    return v3_new(a.x * -1, a.y * -1, a.z * -1);
}

v3_vec3 v3_add(v3_vec3 a, v3_vec3 b) {
    return v3_new(a.x + b.x, a.y + b.y, a.z + b.z);
}

v3_vec3 v3_subtract(v3_vec3 a, v3_vec3 b) {
    return v3_new(a.x - b.x, a.y - b.y, a.z - b.z);
}
v3_vec3 v3_multiply(v3_vec3 a, v3_vec3 b) {
    return v3_new(a.x * b.x, a.y * b.y, a.z * b.z);
}
double v3_dot(v3_vec3 a, v3_vec3 b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

v3_vec3 v3_cross(v3_vec3 a, v3_vec3 b) {
    v3_vec3 vector = {
        (a.y * b.z) - (a.z * b.y), 
        (a.z * b.x) - (a.x * b.z), 
        (a.x * b.y) - (a.y * b.x) 
    };

    return vector;
}

v3_vec3 v3_normalise(v3_vec3 a) {
    return v3_divide_scalar(a, v3_get_length(a));
}

v3_vec3 v3_multiply_scalar(v3_vec3 a, double t) {
    return v3_new(a.x * t, a.y * t, a.z * t);
}

v3_vec3 v3_add_scalar(v3_vec3 a, double t) {
    return v3_new(a.x + t, a.y + t, a.z + t);
}

v3_vec3 v3_divide_scalar(v3_vec3 a, double t) {
    return v3_new(a.x / t, a.y / t, a.z / t);
}

double v3_get_length(v3_vec3 a) {
    return sqrt(v3_get_length_squared(a));
}

double v3_get_length_squared(v3_vec3 a) {
    return (a.x * a.x) + (a.y * a.y) + (a.z * a.z);
}