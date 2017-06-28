#include "include/variables.h"

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define EPSILON 0.00001

static int compare_to_int(VAR intVar, VAR other);
static int compare_to_float(VAR floatVar, VAR other);
static int compare_to_str(VAR strVar, VAR other);

/*
	Funciones para comparar dos variables de cualquier tipo;
	las variables no comparables tienen comportamiento indefinido.

	Se retorna un numero positivo si el primr parametro es mayor
	que el segundo, negativo en el caso opuesto, cero si son iguales.
*/
int compare(VAR first, VAR second){
	switch(first.type){
		case INT_T:
			return compare_to_int(first, second);

		case FLOAT_T:
			return compare_to_float(first, second);

		case STR_T:
			return compare_to_str(first, second);

		default:
			printf("Error. Valores incomparables: %s con %s\n", get_typename(first.type), get_typename(second.type));
			exit(0);
	}
}

/*
	Devuelve 1 si las variables first y second son iguales, 0 sino.
	Notar que si las variables no son del mismo tipo devuelve 0.
*/
int is_equals(VAR first, VAR second){
	if (first.type == second.type)
		return compare(first, second) == 0;
	else
		return 0;
}


static int compare_to_int(VAR intVar, VAR other){
	int i = intVar.value.intValue;

	switch(other.type){
		case INT_T:
			return i - other.value.intValue;

		case FLOAT_T:
			return fabs(i - other.value.floatValue) < EPSILON ? 0 :
					(i - other.value.floatValue < 0) ? -1 : 1;

		default:
			printf("Error. Valores incomparables: %s con %s\n", get_typename(intVar.type), get_typename(other.type));
			exit(0);
	}
}


static int compare_to_float(VAR floatVar, VAR other){
	float i = floatVar.value.floatValue;
	switch(other.type){
		case INT_T:
			return -compare_to_int(other, floatVar);

		case FLOAT_T:
			return fabs(i - other.value.floatValue) < EPSILON ? 0 :
					(i - other.value.floatValue < 0) ? -1 : 1;

		default:
			printf("Error. Valores incomparables: %s con %s\n", get_typename(floatVar.type), get_typename(other.type));
			exit(0);
	}
}


static int compare_to_str(VAR strVar, VAR  other){
		switch(other.type){
		case STR_T:
			return strcmp(strVar.value.strValue, other.value.strValue);

		default:
			printf("Error. Valores incomparables: %s con %s\n", get_typename(strVar.type), get_typename(other.type));
			exit(0);
	}
}
