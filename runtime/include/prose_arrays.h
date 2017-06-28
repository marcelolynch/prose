#ifndef __p_arrays
#define __p_arrays
#include "variables.h"

typedef struct arr{
	VAR * values;
	int size;
	int capacity;
} ArrayCDT;


typedef ArrayCDT* Array;

Array new_array();
void array_push(Array arr, VAR value);
Array array_substract(Array source, Array other);
int array_contains(Array arr, VAR value);
void array_print(Array arr);
void array_free(Array arr);
Array array_clone(Array arr);
void array_cat(Array arr, Array other);

VAR array_access(Array arr, int index);
void array_modify(Array arr, int index, VAR value);

#endif