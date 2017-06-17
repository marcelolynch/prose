#ifndef __p_arrays
#define __p_arrays
#include "variable_manager.h"

typedef struct arr{
	VAR * values;
	int size;
	int capacity;
} ArrayCDT;


typedef ArrayCDT* Array;

Array newArray();
void addToArray(Array arr, VAR value);
void printArray(Array arr);
void freeArray(Array arr);

#endif