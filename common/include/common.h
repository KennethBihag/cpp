#ifndef COMMON_H
#define COMMON_H

#include "exports.hpp"

#ifdef __cplusplus
extern "C"
{
#endif
    int encrypt_char(char ch, int key);
    const char *load_file_to_buffer(const char *filename);
    const char *get_file_ext(const char *filename);
    
    // Prints all elements of an array with a desired string format per element,
    // separated by a space
    COMMON_API void print_intarr_elems(int *array,int length);
    COMMON_API void print_fltarr_elems(float *array, int length);
#ifdef __cplusplus
}
#endif

#endif
