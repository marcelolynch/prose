#include "include/variables.h"
#include "include/prose_arrays.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

VAR * var_table[MAX_VARS] = {0};

VAR get_var(VAR_ID id){
	return *var_table[id];	
}


VAR anon_float(float value){
	VAR var;
	var.type = FLOAT_T;
	var.value.floatValue = value;
	return var;
}

VAR anon_int(int value){
	VAR var;
	var.type = INT_T;
	var.value.intValue = value;
	return var;
}

VAR anon_str(char * value){
	VAR var;
	var.type = STR_T;
	
	var.value.strValue = malloc(strlen(value) + 1);
	strcpy(var.value.strValue, value);

	return var;
}


VAR anon_arr(){
	VAR var;
	var.type = ARRAY_T;

	var.value.arrValue = new_array();
	return var;
}


VAR var_clone(VAR var){
	switch(var.type){
		case INT_T:
		case FLOAT_T:
			return var;

		case STR_T:
			return anon_str(var.value.strValue);

		case ARRAY_T:
		{
			VAR new;
			new.type = ARRAY_T;
			new.value.arrValue = array_clone(var.value.arrValue);
			return new;
		}
	}
}

void add_to_array(VAR_ID id, VAR new_elem){
	VAR * var = var_table[id];
	if(var->type != ARRAY_T){
		printf("Error fatal: agregando a algo distinto de arreglo\n");
		exit(0);
	} 
	array_add((Array)(var->value.arrValue), var_clone(new_elem));
}

VAR assign(VAR_ID id, VAR assigned){
	if(var_table[id] == NULL){
		var_table[id] = malloc(4 * sizeof(*var_table[0]));
	}
	
	VAR * var = var_table[id];

	free_var_resources(var);

	var->type = assigned.type;

	switch(assigned.type){
		case INT_T:
			var->value.intValue =  assigned.value.intValue;
		break;

		case STR_T:
			var->value.strValue = malloc(strlen(assigned.value.strValue) + 1);
			strcpy(var->value.strValue, assigned.value.strValue);
		break;

		case FLOAT_T:
			var->value.floatValue = assigned.value.floatValue;
		break;
		case ARRAY_T:
			var->value.arrValue = array_clone(assigned.value.arrValue);
		break;
	}

	
	return *var;

}


void free_var_resources(VAR* v){
	switch(v->type){
		case STR_T:
			free(v->value.strValue);
			break;
		case ARRAY_T:
			array_free(v->value.arrValue);
			break;
	}

}