#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef CANVAS_H
#define CANVAS_H

#include "debug/error.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>

typedef struct {
    int r;
    int g;
    int b;
} cnv_pixel;

typedef struct {
    int width, height, x, y;

    cnv_pixel** canvas;
} cnv_canvas;

/**
 * @brief Create a new canvas
 * 
 * @param width The width of the canvas
 * @param height The height of the canvas
 * @return cnv_canvas* The resulting canvas
 */
cnv_canvas* cnv_new(int width, int height);

/**
 * @brief This will check whether the specified position is in bounds of the canvas
 * @return ERR_ERROR will return 0 -> in bounds, 1 -> out of bounds, other -> error
 */
ERR_ERROR cnv_is_in_bounds(cnv_canvas* c, int x, int y);

/**
 * @brief Inserts a pixel in the next available pixel in the canvas
 * 
 * @param c The canvas
 * @param r Red channel
 * @param g Green channel
 * @param b Blue channel
 * @return A potential ERROR
 */
ERR_ERROR cnv_put_pixel_next(cnv_canvas* c, int r, int g, int b);

/**
 * @brief Outputs the canvas to a file. Uses the .ppm image format
 * 
 * @param file_name  The name of the file with the .ppm extension
 * @return ERR_ERROR Whether there were any errors in writing to the file
 */
ERR_ERROR cnv_write_to_file_ppm(cnv_canvas* c, const char* file_name);

/**
 * @brief Cleans the canvas to avoid memory leaks and so on
 * 
 * @param c The canvas
 */
ERR_ERROR cnv_delete(cnv_canvas* c);

#endif