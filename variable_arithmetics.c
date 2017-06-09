#include "variable_arithmetics.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static VAR sum(VAR left, VAR right);
static VAR sub(VAR left, VAR right);
static VAR prod(VAR left, VAR right);
static VAR division(VAR left, VAR right);
static VAR integerSum(VAR left, VAR right, int sign);
static VAR floatSum(VAR left, VAR right, int sign);
static VAR stringCat(VAR left, VAR right);

binaryOp operations[] = {sum, sub, prod, division};

VAR binaryOperation(VAR left, VAR right, binary_op op){
	return operations[op](left, right);
}


static VAR sum(VAR left, VAR right){
	switch(left.type){
		case INT_T:
			return integerSum(left, right, 1);
		case STR_T:
			return stringCat(left, right);
		case FLOAT_T:
			return floatSum(left, right, 1);
	}
}

static VAR sub(VAR left, VAR right){
		switch(left.type){
		case INT_T:
			return integerSum(left, right, -1);
		case STR_T:
			return left;
		case FLOAT_T:
			return floatSum(left, right, -1);
	}

}

static VAR prod(VAR left, VAR right){

}


 
static VAR division(VAR left, VAR right){

}



static VAR integerSum(VAR left, VAR right, int sign){
	switch(right.type){
		case INT_T:
		{
			int iresult = left.value.intValue + right.value.intValue;
			iresult *= sign;
			return anon_var(&iresult, INT_T);
		}
		case FLOAT_T:
		{
			float fresult = left.value.intValue + right.value.floatValue;
			fresult *= sign;
			return anon_var(&fresult, FLOAT_T);
		}
		case STR_T:
		{
			char * str = malloc(strlen(right.value.strValue) + 1000);
			sprintf(str, "%d%s", left.value.intValue, right.value.strValue);
			VAR ret = anon_var(str, STR_T);
			free(str);
			return ret;
		}
	}
}


static VAR floatSum(VAR left, VAR right, int sign){
	switch(right.type){
		case INT_T:
		{
			float iresult = left.value.floatValue + right.value.intValue;
			iresult *= sign;
			return anon_var(&iresult, INT_T);
		}
		case FLOAT_T:
		{
			float fresult = left.value.floatValue + right.value.floatValue;
			fresult *= sign;
			return anon_var(&fresult, FLOAT_T);
		}
		case STR_T:
		{
			char * str = malloc(strlen(right.value.strValue) + 1000);
			sprintf(str, "%f%s", left.value.floatValue, right.value.strValue);
			VAR ret = anon_var(str, STR_T);
			free(str);
			return ret;
		}
	}
}


static VAR stringCat(VAR left, VAR right){
		switch(right.type){
		case INT_T:
		{
			char * str = malloc(strlen(left.value.strValue) + strlen(right.value.strValue) + 1);
			sprintf(str, "%s%d", left.value.strValue, right.value.intValue);
			VAR ret = anon_var(str, STR_T);
			free(str);
			return ret;
		}
		case FLOAT_T:
		{
			char * str = malloc(strlen(left.value.strValue) + strlen(right.value.strValue) + 1);
			sprintf(str, "%s%f", left.value.strValue, right.value.floatValue);
			VAR ret = anon_var(str, STR_T);
			free(str);
			return ret;
		}
		case STR_T:
		{
			char * str = malloc(strlen(left.value.strValue) + strlen(right.value.strValue) + 1);
			sprintf(str, "%s%s", left.value.strValue, right.value.strValue);
			VAR ret = anon_var(str, STR_T);
			free(str);
			return ret;
		}
	}
}