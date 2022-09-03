#include "canvas.h"
#include "debug/error.h"
#include <stdlib.h>

#define ASPECT_RATIO 9.0 / 16.0
#define CANVAS_WIDTH 400
#define CANVAS_HEIGHT (int)(CANVAS_WIDTH * ASPECT_RATIO)

int main() {
    cnv_canvas canvas = cnv_new(CANVAS_WIDTH, CANVAS_HEIGHT);
    
    for (int y = 0; y < CANVAS_HEIGHT; y++) {
        printf("\rLines rendered: %d", y);
        for (int x = 0; x < CANVAS_WIDTH; x++) {
            int r = 56;
            int g = 200;
            int b = 64;

            if (cnv_put_pixel_next(&canvas, r, g, b) == ERR_SOFT_OUT_OF_BOUNDS) {
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