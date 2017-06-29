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


/* Mapea el id de una variable nombrada al nombre puesto por el programador
	(para mostrar errores)
 El compilador debería setear esto cuando corresponda.  */
void map_name(VAR_ID id, char * name){
	name_table[id] = name;
}


/* Devuelve el tipo de la variable (para mostrar errores) */
char* get_typename(type_t type){
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


/* Devuelve el valor de la variable asociada al ID id */
VAR get_var(VAR_ID id){
	if(var_table[id] == NULL){
		fprintf(stderr, "Error fatal: usted intentó utilizar una variable nunca antes definida, de nombre '%s'.\nAsegúrese de no haberse equivocado y recompile. \n", name_table[id]);
		exit(1);
	}
	return *var_table[id];
}


/*

*/

/* Construye una variable del tipo float y la retorna */
VAR anon_float(float value){
	VAR var;
	var.type = FLOAT_T;
	var.value.floatValue = value;
	return var;
}


/* Construye una variable del tipo entero y la retorna */
VAR anon_int(int value){
	VAR var;
	var.type = INT_T;
	var.value.intValue = value;
	return var;
}


/* Construye una variable del tipo texto y la retorna */
VAR anon_str(char * value){
	VAR var;
	var.type = STR_T;

	var.value.strValue = malloc(strlen(value) + 1);
	strcpy(var.value.strValue, value);

	return var;
}



/* Construye una variable del tipo lista y la retorna
 El primer argumento corresponde al numero de elementos con que se inicializa.
 Si es mayor a cero, se deben pasar como el resto de los parámetros las
 variables (VAR) con las que se inicializa la lista */
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

/* Devuelve la variable en la posicion index de la lista array */
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



/* Actualiza la posición index de la lista array con la variable new */
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


/* Deep copy de la variable que se pasa como parametro */
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

		default:
			fprintf(stderr, "Error. Tipo desconocido: %d\n", var.type);
			exit(0);
	}
}

/* Se asigna el objeto VAR assigned a la variable nombrada de ID id */
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

/*Libera los recursos alocados para la variable apuntada
(en el caso de string, la cadena, y si es una variable de
tipo lista, se liberan los recursos de la misma */
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
