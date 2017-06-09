#include "variable_manager.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define EPSILON 0.00001

static int compareToInt(VAR* intVar, VAR* other);
static int compareToFloat(VAR * floatVar, VAR* other);
static int compareToStr(VAR * strVar, VAR * other);

VAR * var_table[MAX_VARS] = {0};

VAR * get_var(VAR_ID id){
	return var_table[id];	
}


VAR_ID assign(VAR_ID id, void * value, type_t type){
	if(var_table[id] == NULL){
		var_table[id] = malloc(4 * sizeof(*var_table[0]));
	}
	
	VAR * var = var_table[id];

	var->type = type;

	switch(type){
		case INT_T:
			var->value.intValue =  *((int*)value);
		break;

		case STR_T:
			var->value.strValue = malloc(strlen(value));
			strcpy(var->value.strValue, value);
		break;

		case FLOAT_T:
			var->value.floatValue = *((float*)value);
		break;
	}

	
	return VAR_ID;

}


int compare(VAR_ID a, VAR_ID b){
	if(get_var(a) == NULL || get_var(b) == NULL){
		return -1;
	}


	VAR* first = get_var(a);
	VAR* second = get_var(b);

	switch(first->type){
		case INT_T:
			return compareToInt(first, second);
		
		case FLOAT_T:
			return compareToFloat(first, second);

		case STR_T:
			return compareToStr(first, second);

	}

}


static int compareToInt(VAR* intVar, VAR* other){
	int i = intVar->value.intValue;

	switch(other->type){
		case INT_T:
			return i - other->value.intValue;

		case FLOAT_T:
			return fabs(i - other->value.floatValue) < EPSILON ? 0 : 
					(i - other->value.floatValue < 0) ? -1 : 1;

		case STR_T:
			return 1;
	}
}


static int compareToFloat(VAR * floatVar, VAR* other){
	float i = floatVar->value.floatValue;
	switch(other->type){
		case INT_T:
			return -compareToInt(other, floatVar);

		case FLOAT_T:
			return fabs(i - other->value.floatValue) < EPSILON ? 0 : 
					(i - other->value.floatValue < 0) ? -1 : 1;

		case STR_T:
			return 1;
	}
}


static int compareToStr(VAR * strVar, VAR * other){
		switch(other->type){
		case INT_T:
			return -1;

		case FLOAT_T:
			return -1;

		case STR_T:
			return strcmp(strVar->value.strValue, other->value.strValue);
	}
}

type_t getType(){

}
