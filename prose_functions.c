#include "variable_manager.h"
#include "prose_functions.h"
#include <stdlib.h>
#include <stdio.h>

void print_var(VAR var){
		switch(var.type){
			case INT_T:
				printf("%d \n", var.value.intValue);
				break;
			case STR_T:
				printf("%s \n", var.value.strValue);
				break;
			case FLOAT_T:
				printf("%f \n", var.value.floatValue);
				break;
		}
}
