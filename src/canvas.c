#include "canvas.h"

cnv_canvas* cnv_new(int width, int height) {
    cnv_canvas* canvas = malloc(sizeof(cnv_canvas));
    if (!canvas) abort();

    canvas->width = width;
    canvas->height = height;
    canvas->x = 0;
    canvas->y = 0;
    
    canvas->canvas = (cnv_pixel**) malloc(sizeof(cnv_pixel*) * height);

    for (int i = 0; i < height; i++) {
        canvas->canvas[i] = (cnv_pixel*) malloc(sizeof(cnv_pixel) * width);
    }

    if (!canvas->canvas) {
        free(canvas);
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

ERR_ERROR cnv_put_pixel_next(cnv_canvas* c, int r, int g, int b) {
    if (!c) return ERR_NULL_VALUE;

    if (!cnv_is_in_bounds(c, c->x, c->y)) {
        return ERR_SOFT_OUT_OF_BOUNDS;
    }

    cnv_pixel* position = &c->canvas[c->x][c->y];

    position->r = r;
    position->g = g;
    position->b = b;

    printf("\nX: %d, Y: %d", c->x, c->y);

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
            int r = current_pixel->r;
            int g = current_pixel->g;
            int b = current_pixel->b;
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
    free(c);

    return ERR_NO_ERROR;
}