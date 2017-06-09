#ifndef __dtype_h
#define __dtype_h


#include <stdint.h>

#define INT_T 1
#define STR_T 2
#define FLOAT_T 3
#define ARITHMETIC_EXP 4


#define MAX_VARS 1000

typedef uint8_t type_t;

typedef int VAR_ID;


typedef union{
		int intValue;
		float floatValue;
		char* strValue;
	} varValue;

typedef struct{
  	varValue value;
		type_t type;
} VAR;


VAR assign(VAR_ID id, VAR assigned);
VAR anon_var(uint64_t value, type_t type);

VAR anon_float(float value);
VAR anon_int(int value);
VAR anon_str(char* value);



int compare(VAR first, VAR second);

VAR_ID new_var(type_t type, void * value);
VAR get_var(VAR_ID id);


#endif
