#include "include/variables.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static VAR integer_add(VAR left, VAR right, int sign);
static VAR float_add(VAR left, VAR right, int sign);
static VAR string_add(VAR left, VAR right);


VAR var_sum(VAR left, VAR right){
	switch(left.type){
		case INT_T:
			return integer_add(left, right, 1);
		case STR_T:
			return string_add(left, right);
		case FLOAT_T:
			return float_add(left, right, 1);
	}
}

VAR var_sub(VAR left, VAR right){
		switch(left.type){
		case INT_T:
			return integer_add(left, right, -1);
		case STR_T:
			return left;
		case FLOAT_T:
			return float_add(left, right, -1);
	}

}

VAR var_prod(VAR left, VAR right){

}


 
VAR var_div(VAR left, VAR right){

}


VAR var_minus(VAR var){

	switch(var.type){
		case INT_T:
		case FLOAT_T:
			var.value.intValue = -var.value.intValue;
			break;
		default:
			break;
	}

	return var;
}


static VAR integer_add(VAR left, VAR right, int sign){
	switch(right.type){
		case INT_T:
		{
			int iresult = left.value.intValue + sign * right.value.intValue;
			return anon_int(iresult);
		}
		case FLOAT_T:
		{
			float fresult = left.value.intValue + sign * right.value.floatValue;
			return anon_float(fresult);
		}
		case STR_T:
		{
			char * str = malloc(strlen(right.value.strValue) + 1000);
			sprintf(str, "%d%s", left.value.intValue, right.value.strValue);
			VAR ret = anon_str(str);
			free(str);
			return ret;
		}
	}
}


static VAR float_add(VAR left, VAR right, int sign){
	switch(right.type){
		case INT_T:
		{
			float iresult = left.value.floatValue + right.value.intValue;
			iresult *= sign;
			return anon_int(iresult);
		}
		case FLOAT_T:
		{
			float fresult = left.value.floatValue + right.value.floatValue;
			fresult *= sign;
			return anon_float(fresult);
		}
		case STR_T:
		{
			char * str = malloc(strlen(right.value.strValue) + 1000);
			sprintf(str, "%f%s", left.value.floatValue, right.value.strValue);
			VAR ret = anon_str(str);
			free(str);
			return ret;
		}
	}
}


#define MAX_DIGITS 30
static VAR string_add(VAR left, VAR right){
		switch(right.type){
		case INT_T:
		{
			char * str = malloc(MAX_DIGITS + strlen(left.value.strValue) + 1);
			sprintf(str, "%s%d", left.value.strValue, right.value.intValue);
			VAR ret = anon_str(str);
			free(str);
			return ret;
		}
		case FLOAT_T:
		{
			char * str = malloc(MAX_DIGITS + strlen(left.value.strValue) + 1);
			sprintf(str, "%s%3f", left.value.strValue, right.value.floatValue);
			VAR ret = anon_str(str);
			free(str);
			return ret;
		}
		case STR_T:
		{
			char * str = malloc(strlen(left.value.strValue) + strlen(right.value.strValue) + 1);
			sprintf(str, "%s%s", left.value.strValue, right.value.strValue);
			VAR ret = anon_str(str);
			free(str);
			return ret;
		}
	}
}