/**
 * \file error_handler.h
 * \brief Error related function definition.
 *
 *
 * Here are defined the error related functions
 */

#ifndef AUDIO_SYNTH_ERROR_HANDLER_H
#define AUDIO_SYNTH_ERROR_HANDLER_H

#include <stdio.h>

#ifdef TEST
#define sys_print_error(mesage)   // No print
#define sys_print_error_test(message) fprintf(stderr, "ERROR %s : in function %s at %s (line %d)\n", message, __func__, __FILE__, __LINE__)
#endif

#ifndef TEST
#define sys_print_error(message) fprintf(stderr, "ERROR %s : in function %s at %s (line %d)\n", message, __func__, __FILE__, __LINE__)
#endif

#endif //AUDIO_SYNTH_ERROR_HANDLER_H
