#include <stdlib.h>
#include <stdio.h>

#include "include/prose_arrays.h"
#include "include/prose_functions.h"

static void increaseCapacity(Array arr);

#define INITIAL_SIZE 15
Array new_array(){
	Array arr = malloc(sizeof(*arr));
	arr->values = malloc(INITIAL_SIZE * sizeof(VAR));
	arr->size = 0;
	arr->capacity = INITIAL_SIZE;
	return arr;
}


void add_to_array(Array arr, VAR value){
	if(arr == NULL){ //TODO: Error
		return;
	}

	if(arr->size == arr->capacity){
		increaseCapacity(arr);
	}

	arr->values[arr->size] = value;
	arr->size++;
}	


void print_array(Array arr){
	if(arr == NULL){
		printf("ERROR");
		exit(0);
	}
	int i;
	printf("[");
	for(i = 0; i < arr->size ; i++){
		print_var(arr->values[i],0);
		if(i < arr->size -1) printf(", ");
	}	
	printf("]");
}


void free_array(Array arr){
	int i;
	for(i=0 ; i < arr->size ; i++){
		free_var_resources(&arr->values[i]);
	}
	free(arr->values);
	free(arr);
}

static void increaseCapacity(Array arr){
	int cap = arr->capacity;
	VAR * new_values = realloc(arr->values, 2*arr->capacity*sizeof(VAR));
	if(new_values == NULL){
		printf("No memory\n");
		exit(0);
	}

	arr->values = new_values;
	arr->capacity += arr->capacity;

}
