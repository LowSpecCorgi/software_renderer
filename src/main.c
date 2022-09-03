#include "canvas.h"
#include "debug/error.h"
#include "math/vec3.h"
#include "math/ray.h"

#include <stdlib.h>

#define ASPECT_RATIO 9.0 / 16.0
#define CANVAS_WIDTH 400
#define CANVAS_HEIGHT CANVAS_WIDTH * ASPECT_RATIO

// TESTING FUNCTION!
v3_colour ray_colour(ry_ray* r) {
    v3_vec3 direction = v3_normalise(r->direction);

    double t = 0.5 * (direction.y + 1.0);

    v3_vec3 start_value = v3_new(1.0, 1.0, 1.0);
    v3_vec3 end_value = v3_new(0.5, 0.7, 1.0);

    return v3_add(
        v3_multiply_scalar(start_value, 1.0 - t), 
        v3_multiply_scalar(end_value, t));
}

int main() {
    cnv_canvas canvas = cnv_new(CANVAS_WIDTH, CANVAS_HEIGHT);

    // Virtual camera
    double viewport_height = 2.0;
    double viewport_width = ASPECT_RATIO * viewport_height;
    double focal_length = 1.0;

    v3_point3 origin = v3_new(0, 0, 0);
    v3_point3 horizontal = v3_new(viewport_width, 0, 0);
    v3_point3 vertical = v3_new(0, viewport_height, 0);
    v3_point3 lower_left_corner = v3_subtract(
        v3_subtract(origin, v3_divide_scalar(horizontal, 2)),
        v3_subtract( v3_divide_scalar(vertical, 2), v3_new(0, 0, focal_length)
    ));
    
    for (int y = 0; y < CANVAS_HEIGHT; y++) {
        printf("\rLines rendered: %d", y);
        for (int x = 0; x < CANVAS_WIDTH; x++) {
            double u = (double)x / (CANVAS_WIDTH - 1);
            double v = (double)y / (CANVAS_HEIGHT - 1);

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