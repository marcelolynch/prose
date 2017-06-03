#include "variable_manager.h"
#include "prose_functions.h"
#include <stdlib.h>
#include <stdio.h>

void print_var(VAR_ID id){
	VAR * var = get_var(id);

	if(var == NULL){ 
		printf("Fatal error");
		exit(0); // Ponele
	}

	switch(var->type){
		case INT_T:
			printf("Integer: %d \n", var->value.intValue);
			break;
		case STR_T:
			printf("String: %s \n", var->value.strValue);
			break;
		case FLOAT_T:
			printf("Float %f \n", var->value.floatValue);
			break;
	}
}

