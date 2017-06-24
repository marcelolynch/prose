#ifndef __dtype_h
#define __dtype_h


#include <stdint.h>

#define INT_T 1
#define STR_T 2
#define FLOAT_T 3
#define ARITHMETIC_EXP 4
#define ARRAY_T 5

#define MAX_VARS 1000

typedef uint8_t type_t;

typedef int VAR_ID;


typedef union{
		int intValue;
		float floatValue;
		char* strValue;
		void* arrValue;
	} varValue;

typedef struct{
  	varValue value;
		type_t type;
} VAR;



/* MANTENIMIENTO, CREACION DE VARIABLES */
void map_name(VAR_ID id, char * name);
VAR assign(VAR_ID id, VAR assigned);
VAR anon_var(uint64_t value, type_t type);
void free_var_resources(VAR* v);

VAR anon_float(float value);
VAR anon_int(int value);
VAR anon_str(char* value);
VAR anon_arr(int n, ...);

void add_to_array(VAR_ID id, VAR new_elem);
VAR array_index(VAR array, VAR index);
void array_assign(VAR array, VAR index, VAR new);

VAR_ID new_var(type_t type, void * value);
VAR get_var(VAR_ID id);
VAR var_clone(VAR var);


/* OPERACIONES ENTRE VARIABLES */
/*Comparacion */

int compare(VAR first, VAR second);



/* Operaciones aritmeticas */
VAR var_sum(VAR left, VAR right);
VAR var_sub(VAR left, VAR right);
VAR var_prod(VAR left, VAR right);
VAR var_div(VAR left, VAR right);
VAR var_minus(VAR var);








#endif
