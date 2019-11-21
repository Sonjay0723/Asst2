#ifndef _MULTITEST_H
#define _MULTITEST_H
#include <stdio.h>
#include <stdlib.h>

/* Redefining the search function, using macros. */
#define searchArr(array, target, size) search(array, target, size)

/* Determine if process or thread is running. */
extern const char *name;

/* Function Signatures. */
int search(int* array, int target, int size);

#endif

