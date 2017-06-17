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
void add_to_array(Array arr, VAR value);
void print_array(Array arr);
void free_array(Array arr);

#endif