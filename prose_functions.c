#include "variable_manager.h"
#include "prose_functions.h"
#include "prose_arrays.h"
#include <stdlib.h>
#include <stdio.h>

void print_var(VAR var, int newline){
		switch(var.type){
			case INT_T:
				printf("%d", var.value.intValue);
				break;
			case STR_T:
				printf("%s", var.value.strValue);
				break;
			case FLOAT_T:
				printf("%f", var.value.floatValue);
				break;
			case ARRAY_T:
				printArray((Array)var.value.arrValue);
				break;
		}

	if(newline){
		printf("\n");
	}
}