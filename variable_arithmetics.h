#ifndef __var_arithmetics
#define __var_arithmetics
#include "variable_manager.h"

typedef VAR (*binaryOp)(VAR l , VAR r);



VAR var_sum(VAR left, VAR right);
VAR var_sub(VAR left, VAR right);
VAR var_prod(VAR left, VAR right);
VAR var_div(VAR left, VAR right);
VAR var_minus(VAR var);




#endif