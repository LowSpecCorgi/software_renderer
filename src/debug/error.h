#ifndef ERROR_H
#define ERROR_H

/**
 * @brief ERROR constants
 * 0 & 1 are reserved for booleans!
 * 
 */

typedef enum  {
    ERR_NO_ERROR = 10,
    ERR_FAILED_IO_WRITE = 11,
    ERR_FAILED_MALLOC = 12,
    ERR_SOFT_OUT_OF_BOUNDS = 13,
    ERR_NULL_VALUE = 14,
} ERR_ERROR;
#endif