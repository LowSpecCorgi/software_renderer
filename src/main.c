#include "canvas.h"
#include "debug/error.h"
#include "math/vec3.h"
#include "math/ray.h"

#include <stdlib.h>

#define ASPECT_RATIO 9.0 / 16.0
#define CANVAS_WIDTH 400
#define CANVAS_HEIGHT CANVAS_WIDTH * ASPECT_RATIO

double hit_sphere(ry_ray* r, double radius, v3_point3 centre) {
    v3_point3 oc = v3_subtract(r->origin, centre);
    double a = v3_get_length_squared(r->direction);
    double b = v3_dot(oc, r->direction);
    double c = v3_get_length_squared(oc) - radius * radius;
    double discriminant = b * b - a * c;

    if (discriminant < 0) {
        return -1.0; 
    } else {
        return (-b - sqrt(discriminant) / a);
    }
}

v3_colour ray_colour(ry_ray* r) {
    double t = hit_sphere(r, 0.5, v3_new(0.0, 0.0, -1.0));
    if (t > 0.0) { 
        v3_vec3 normal = v3_normalise(v3_subtract(ry_at(*r, t), v3_new(0, 0, -1)));
        return v3_multiply_scalar(v3_new(normal.x + 1, normal.y + 1, normal.z + 1), 0.5);
    }

    v3_vec3 direction = v3_normalise(r->direction);

    t = 0.5 * (direction.y + 1.0);

    v3_vec3 start_value = v3_new(1.0, 1.0, 1.0);
    v3_vec3 end_value = v3_new(0.5, 0.7, 1.0);

    return v3_add(
        v3_multiply_scalar(start_value, 1.0 - t), 
        v3_multiply_scalar(end_value, t));
}

int main() {
    cnv_canvas canvas = cnv_new(CANVAS_WIDTH, CANVAS_HEIGHT);

    // Virtual camera
    double viewport_width = 4.0;
    double viewport_height = (ASPECT_RATIO) * viewport_width;

    double focal_length = 1.0;

    v3_point3 origin = v3_new(0, 0, 0);
    v3_point3 horizontal = v3_new(viewport_width, 0, 0);
    v3_point3 vertical = v3_new(0, viewport_height, 0);
    v3_point3 lower_left_corner = v3_new(-2, -1, -1);
    
    for (int y = 0; y < CANVAS_HEIGHT; y++) {
        printf("\rLines rendered: %d", y);
        for (int x = 0; x < CANVAS_WIDTH; x++) {
            double u = (double)x / (CANVAS_WIDTH - 1);
            double v = (double)y / (CANVAS_HEIGHT - 1);

            /*
                This determines where on the screen to render

                l + u*h + v*v - o
                ^ Lower left corner + scaled up uv coordinates, which are then centreed in the camera
            */
            ry_ray r = ry_new_ray(origin, 
                v3_add(v3_add(
                    v3_multiply_scalar(horizontal, u), lower_left_corner),
                    v3_subtract(v3_multiply_scalar(vertical, v), origin)));
            
            v3_colour colour = v3_multiply_scalar(ray_colour(&r), 255);

            if (cnv_put_pixel_next(&canvas, colour) == ERR_SOFT_OUT_OF_BOUNDS) {
                printf("\nFinished rendering.");
                break;
            }
        }
    }

    ERR_ERROR error = cnv_write_to_file_ppm(&canvas, "test.ppm");

    if (error == ERR_FAILED_IO_WRITE) printf("Failed to write file");

    cnv_delete(&canvas);

    return 0;
}