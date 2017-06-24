#include "include/variables.h"
#include "include/prose_arrays.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static VAR integer_sum(VAR left, VAR right, int sign);
static VAR float_sum(VAR left, VAR right, int sign);
static VAR string_sum(VAR left, VAR right);
static VAR array_sum(VAR left, VAR right);

static VAR integer_prod(VAR left, VAR right);
static VAR string_prod(VAR left, VAR right);
static VAR float_prod(VAR left, VAR right);

VAR var_sum(VAR left, VAR right){
	switch(left.type){
		case INT_T:
			return integer_sum(left, right, 1);
		case STR_T:
			return string_sum(left, right);
		case FLOAT_T:
			return float_sum(left, right, 1);
		case ARRAY_T:
			return array_sum(left, right);
	}
}

VAR var_sub(VAR left, VAR right){
		switch(left.type){
		case INT_T:
			return integer_sum(left, right, -1);
		case STR_T:
			return left;
		case FLOAT_T:
			return float_sum(left, right, -1);
	}

}

VAR var_prod(VAR left, VAR right){
			switch(left.type){
		case INT_T:
			return integer_prod(left, right);
		case STR_T:
			return string_prod(left, right);
		case FLOAT_T:
			return float_prod(left, right);
			break;

	}
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



static VAR integer_sum(VAR left, VAR right, int sign){
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


static VAR float_sum(VAR left, VAR right, int sign){
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
static VAR string_sum(VAR left, VAR right){
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


static VAR array_sum(VAR left, VAR right){
	switch(right.type){
		case ARRAY_T:
		{
			VAR ary;
			ary.type = ARRAY_T;
			ary.value.arrValue = array_clone(left.value.arrValue);
			array_cat(ary.value.arrValue, right.value.arrValue);
			return ary;
		}
		case INT_T:
		case FLOAT_T:
		case STR_T:
		{
			VAR ary;
			ary.type = ARRAY_T;
			ary.value.arrValue = array_clone(left.value.arrValue);
			array_push((Array)(ary.value.arrValue), var_clone(right));
			return ary;
		}
	}
}


static VAR integer_prod(VAR left, VAR right){
	switch(right.type){
		case INT_T:
		{
			int iresult = left.value.intValue * right.value.intValue;
			return anon_int(iresult);
		}
		case FLOAT_T:
		{
			float fresult = left.value.intValue * right.value.floatValue;
			return anon_float(fresult);
		}
		case STR_T:
		{
			// El string se concatena left.value.intValue veces
			int i;
			int len = strlen(right.value.strValue);
			char * str = malloc(len*left.value.intValue + 1);
			for(i=0 ; i < left.value.intValue ; i++){
				memcpy(str+i*len, right.value.strValue, len);
			}
			*(str+left.value.intValue*len + 1) = 0;

			VAR ret = anon_str(str);
			free(str);
			return ret;
		}
	}
}




static VAR float_prod(VAR left, VAR right){
	switch(right.type){
		case INT_T:
		{
			return integer_prod(right, left);
		}
		case FLOAT_T:
		{
			float fresult = left.value.floatValue * right.value.floatValue;
			return anon_float(fresult);
		}
		case STR_T:
		{
			return integer_prod(anon_int(left.value.floatValue), right);
		}
	}
}



static VAR string_prod(VAR left, VAR right){
	switch(right.type){
		case INT_T:
		{
			return integer_prod(right, left);
			break;
		}
		case FLOAT_T:
		{
			return float_prod(right, left);
			break;
		}
		case STR_T:
		{
			printf("Str * Str is not good \n");
			exit(1);
		}
	}
}

