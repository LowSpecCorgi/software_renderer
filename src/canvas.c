#include "canvas.h"

cnv_canvas cnv_new(int width, int height) {
    cnv_canvas canvas = {width, height, 0, 0, (cnv_pixel**) malloc(sizeof(cnv_pixel*) * width)};

    for (int i = 0; i < width; i++) {
        canvas.canvas[i] = (cnv_pixel*) malloc(sizeof(cnv_pixel) * height);
    }

    if (!canvas.canvas) {
        free(canvas.canvas);
        abort();
    }

    return canvas;
}

ERR_ERROR cnv_is_in_bounds(cnv_canvas* c, int x, int y) {
    if (!c) return ERR_NULL_VALUE;

    if (x < 0 || y < 0 || x >= c->width || y >= c->height) {
        return false;
    }

    return true;
}

ERR_ERROR cnv_put_pixel_next(cnv_canvas* c, v3_colour colour) {
    if (!c) return ERR_NULL_VALUE;

    if (!cnv_is_in_bounds(c, c->x, c->y)) {
        return ERR_SOFT_OUT_OF_BOUNDS;
    }

    cnv_pixel* position = &c->canvas[c->x][c->y];

    position->colour.x = colour.x;
    position->colour.y = colour.y;
    position->colour.z = colour.z;

    if (c->x >= c->width - 1) {
        c->x = 0;
        c->y ++;
    } else { c->x++; }

    return ERR_NO_ERROR;
}

ERR_ERROR cnv_write_to_file_ppm(cnv_canvas* c, const char* file_name) {
    FILE *file;

    if ((file = fopen(file_name, "w")) == NULL) return ERR_FAILED_IO_WRITE;

    // Declare colour type (ascii)
    fprintf(file, "P3\n%d %d\n255\n", c->width, c->height);

    for (int y = 0; y < c->height; y++) {
        for (int x = 0; x < c->width; x++) {
            cnv_pixel* current_pixel = &c->canvas[x][y];
            int r = current_pixel->colour.x;
            int g = current_pixel->colour.y;
            int b = current_pixel->colour.z;
            fprintf(file, "%d %d %d\n", r, g, b);
        }
    }

    // Close file
    fclose(file);

    return ERR_NO_ERROR;
}

ERR_ERROR cnv_delete(cnv_canvas* c) {
    if (!c) return ERR_NULL_VALUE;

    free(c->canvas);

    return ERR_NO_ERROR;
}