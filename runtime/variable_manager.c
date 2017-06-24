#include "include/variables.h"
#include "include/prose_arrays.h"
#include "include/prose_functions.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

VAR * var_table[MAX_VARS] = {0};
char* name_table[MAX_VARS] = {0};


void map_name(VAR_ID id, char * name){
	name_table[id] = name;
}


char* get_typename(int type){
	switch(type){
		case INT_T:
		case FLOAT_T:
			return "número";
		case STR_T:
			return "texto";
		case ARRAY_T:
			return "lista";	
		default:
			return "(algo desconocido)";
	}
	return "";
}


VAR get_var(VAR_ID id){
	if(var_table[id] == NULL){
		fprintf(stderr, "Error fatal: usted intentó utilizar una variable nunca antes definida, de nombre '%s'.\nAsegúrese de no haberse equivocado y recompile. \n", name_table[id]);
		exit(1);
	}
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



VAR anon_arr(int num, ...){
	VAR var;
	var.type = ARRAY_T;

	var.value.arrValue = new_array();

	va_list valist;
	int i;

	va_start(valist, num);
	
	for (i = 0; i < num; i++) {
      array_push(var.value.arrValue, va_arg(valist, VAR));
  	}
	
   	va_end(valist);

	return var;
}

VAR array_index(VAR array, VAR index){
	if(array.type != ARRAY_T){
		printf("Error fatal: se intenta acceder a un elemento de algo que no es una lista\n");
		exit(1);
	}

	if(index.type != INT_T){
		printf("Error fatal: se intenta acceder a un elemento no entero de una lista.\n");
		exit(1);
	}

	return array_access(array.value.arrValue, index.value.intValue);
}


void array_assign(VAR array, VAR index, VAR new){
	if(array.type != ARRAY_T){
		printf("Error fatal: se intenta acceder a un elemento de algo que no es una lista\n");
		exit(1);
	}

	if(index.type != INT_T){
		printf("Error fatal: se intenta acceder a un elemento no entero de una lista.\n");
		exit(1);
	}

	array_modify(array.value.arrValue, index.value.intValue, new);
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
			VAR clone;
			clone.type = ARRAY_T;
			clone.value.arrValue = array_clone(var.value.arrValue);
			return clone;
		}
	}
}


VAR assign(VAR_ID id, VAR assigned){

	// Se crea un objeto nuevo cada vez que se asigna
	VAR * var = malloc(4 * sizeof(*var_table[0]));

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

	//Se liberan los recursos anteriores
	free_var_resources(var_table[id]);
	var_table[id] = var;

	
	return *var;

}


void free_var_resources(VAR* v){
	if(v == NULL) return;

	switch(v->type){
		case STR_T:
			free(v->value.strValue);
			break;
		case ARRAY_T:
			array_free(v->value.arrValue);
			break;
	}

}