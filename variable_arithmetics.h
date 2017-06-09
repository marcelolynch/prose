#ifndef __var_arithmetics
#define __var_arithmetics
#include "variable_manager.h"

typedef VAR (*binaryOp)(VAR l , VAR r);



typedef enum{
	SUM=0,
	SUB,
	PROD,
	DIV
} binary_op;


VAR sum(VAR left, VAR right);
VAR sub(VAR left, VAR right);
VAR prod(VAR left, VAR right);
VAR division(VAR left, VAR right);


VAR binaryOperation(VAR left, VAR right, binary_op op);


#endif