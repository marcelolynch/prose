#include "include/variables.h"

#include <math.h>
#include <string.h>

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

	}
}


static int compare_to_int(VAR intVar, VAR other){
	int i = intVar.value.intValue;

	switch(other.type){
		case INT_T:
			return i - other.value.intValue;

		case FLOAT_T:
			return fabs(i - other.value.floatValue) < EPSILON ? 0 : 
					(i - other.value.floatValue < 0) ? -1 : 1;

		case STR_T:
			return 1;
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

		case STR_T:
			return 1;
	}
}


static int compare_to_str(VAR strVar, VAR  other){
		switch(other.type){
		case INT_T:
			return -1;

		case FLOAT_T:
			return -1;

		case STR_T:
			return strcmp(strVar.value.strValue, other.value.strValue);
	}
}
