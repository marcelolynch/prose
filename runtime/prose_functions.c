#include "include/variables.h"
#include "include/prose_functions.h"
#include "include/prose_arrays.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

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
			array_print((Array)var.value.arrValue);
			break;
	}

	if(newline){
		printf("\n");
	}
}

void append(int source_id, VAR elem){
	VAR source_var = get_var(source_id);

	if (source_var.type != STR_T && source_var.type != ARRAY_T){
		printf("Error: se intenta anexar a algo que no es una %s ni un %s. El programa no puede continuar\n",
			get_typename(ARRAY_T), get_typename(STR_T));
		exit(1);
	}

	assign(source_id, var_sum(source_var, elem));
}

void toupper_str(int str_id){
	VAR str_var = get_var(str_id);
	char * str;
	int i;

	if (str_var.type != STR_T){
		printf("Error: se intenta pasar a mayuscula algo que no es un %s", get_typename(STR_T));
		exit(1);
	}

	str = str_var.value.strValue;

	for (i = 0; str[i] != '\0'; i++)
		str[i] = toupper(str[i]);
}

void tolower_str(int str_id){
	VAR str_var = get_var(str_id);
	char * str;
	int i;

	if (str_var.type != STR_T){
		printf("Error: se intenta pasar a minuscula algo que no es un %s", get_typename(STR_T));
		exit(1);
	}

	str = str_var.value.strValue;

	for (i = 0; str[i] != '\0'; i++)
		str[i] = tolower(str[i]);
}

void inc(int num_id) {
	VAR num_var = get_var(num_id);

	if (num_var.type != INT_T && num_var.type != FLOAT_T){
		printf("Error: se intenta incrementar algo que no es un %s", get_typename(INT_T));
		exit(1);
	}

	assign(num_id, var_sum(num_var, anon_int(1)));
}

void dec(int num_id) {
	VAR num_var = get_var(num_id);

	if (num_var.type != INT_T && num_var.type != FLOAT_T){
		printf("Error: se intenta decrementar algo que no es un %s", get_typename(INT_T));
		exit(1);
	}

	assign(num_id, var_sub(num_var, anon_int(1)));
}

void scan(int type, VAR_ID elem) {
	if (type == 0) { // NUMERO
		float read;
		scanf("%g", &read);
		while(getchar() != '\n');
		assign(elem, anon_float(read));
	} else if (type == 1) { // TEXTO
		char * text = malloc(256);
		scanf("%255[^\n]", text);
		assign(elem, anon_str(text));
		free(text);
	}
}
