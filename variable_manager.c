#include "variable_manager.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

VAR * var_table[MAX_VARS] = {0};

VAR * get_var(VAR_ID id){
	return var_table[id];	
}


void assign(VAR_ID id, void * value, type_t type){
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
}


type_t getType(){

}
