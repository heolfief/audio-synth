/**
 * \file error_handler.c
 * \brief Error related functions.
 *
 *
 * Here are implemented the error related functions
 */
#include "error_handler.h"

void sys_print_error(char* message)
{
    fprintf(stderr, "ERROR %s : in function %s at %s (line %d)\n", message, __func__, __FILE__, __LINE__);
}