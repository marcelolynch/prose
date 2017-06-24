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

/* Deep copy del arreglo */
Array array_clone(Array other){
	if(other == NULL){
		return NULL;
	}
	Array clone = new_array();
	
	int i;
	for(i=0 ; i < other->size ; i++){
		array_push(clone, var_clone(other->values[i]));
	}

	return clone;
}


/*Devuelve el valor de la posición index*/
VAR array_access(Array arr, int index){
	if(index >= arr->size){
		printf("Array index out of bounds");
		exit(1);
	}
	return arr->values[index];
}

/* Actualiza el valor de la posicion index */
void array_modify(Array arr, int index, VAR value){
	if(index >= arr->size){
		printf("Index out of bounds");
		exit(1);
	}
	arr->values[index] = var_clone(value);
}

/* Agrega al final del arreglo */
void array_push(Array arr, VAR value){
	if(arr == NULL){ //TODO: Error
		return;
	}

	if(arr->size == arr->capacity){
		increaseCapacity(arr);
	}

	arr->values[arr->size] = var_clone(value);
	arr->size++;
}	

/* Append del arreglo other al arreglo arr */
void array_cat(Array arr, Array other){
	if(arr == NULL || other == NULL){
		return;
	}
	
	int i;
	for(i=0 ; i < other->size ; i++){
		array_push(arr, var_clone(other->values[i]));
	}
}


void array_print(Array arr){
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


void array_free(Array arr){
	int i;
	for(i=0 ; i < arr->size ; i++){
		free_var_resources(&arr->values[i]);
	}
	free(arr->values);
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
