#include "include/variables.h"
#include "include/prose_arrays.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static VAR integer_sum(VAR left, VAR right, int sign);
static VAR float_sum(VAR left, VAR right, int sign);
static VAR string_sum(VAR left, VAR right);
static VAR array_sum(VAR left, VAR right);

static VAR string_sub(VAR left, VAR right);
static VAR perform_string_sub(const char * left_str, const char * right_str);
static int is_initial_substr(const char * str, const char * sub);
static VAR array_sub(VAR left, VAR right);

static VAR integer_prod(VAR left, VAR right);
static VAR string_prod(VAR left, VAR right);
static VAR float_prod(VAR left, VAR right);

static VAR float_div(VAR left, VAR right);
static VAR string_div(VAR left, VAR right);
static VAR integer_div(VAR left, VAR right);

#define MAX_DIGITS 30

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
		default:
			fprintf(stderr, "Error. Tipo desconocido: %d\n", left.type);
			exit(0);
	}
}

VAR var_sub(VAR left, VAR right){
	switch(left.type){
		case INT_T:
			return integer_sum(left, right, -1);
		case STR_T:
			return string_sub(left, right);
		case FLOAT_T:
			return float_sum(left, right, -1);
		case ARRAY_T:
			return array_sub(left, right);
		default:
			fprintf(stderr, "Error. Tipo desconocido: %d\n", left.type);
			exit(0);
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
		default:
			fprintf(stderr, "Error. Tipo desconocido: %d\n", left.type);
			exit(0);
		}
}



VAR var_div(VAR left, VAR right){
	switch(left.type){
		case INT_T:
			return integer_div(left, right);
		case STR_T:
			return string_div(left, right);
		case FLOAT_T:
			return float_div(left, right);
		default:
			fprintf(stderr, "Error. Tipo desconocido: %d\n", left.type);
			exit(0);
	}


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

			if(sign < 0){
				printf("Error"); //TODO
				exit(1);
			}

			char * str = malloc(strlen(right.value.strValue) + MAX_DIGITS);
			sprintf(str, "%d%s", left.value.intValue, right.value.strValue);
			VAR ret = anon_str(str);
			free(str);
			return ret;
		}
		default:
			fprintf(stderr, "Error. Tipo desconocido: %d\n", right.type);
			exit(0);
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
			if(sign < 0){
				printf("Error"); //TODO
				exit(1);
			}

			char * str = malloc(strlen(right.value.strValue) + MAX_DIGITS);
			sprintf(str, "%f%s", left.value.floatValue, right.value.strValue);
			VAR ret = anon_str(str);
			free(str);
			return ret;
		}
		default:
			fprintf(stderr, "Error. Tipo desconocido: %d\n", right.type);
			exit(0);
	}
}


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
		default:
			fprintf(stderr, "Error. Tipo desconocido: %d\n", right.type);
			exit(0);
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
		default:
			fprintf(stderr, "Error. Tipo desconocido: %d\n", right.type);
			exit(0);
	}
}


static VAR string_sub(VAR left, VAR right){
	switch(right.type){
		case STR_T:
			return perform_string_sub(left.value.strValue, right.value.strValue);
		default:
			printf("Error: a un %s solo se le puede restar otro %s. El programa no puede continuar.\n", get_typename(STR_T), get_typename(STR_T));
			exit(1);
	}
}

static VAR perform_string_sub(const char * left_str, const char * right_str){
	char * str = malloc(strlen(left_str) + 1);
	int right_len = strlen(right_str);
	int i, j;

	for (i = j = 0; left_str[i] != '\0'; i++){
		if (is_initial_substr(&left_str[i], right_str))
			i += right_len - 1; /* Con el i++ avanza right_len */
		else
			str[j++] = left_str[i];
	}

	str[j] = '\0';

	VAR ans = anon_str(str);
	free(str);
	return ans;
}

static int is_initial_substr(const char * str, const char * sub){
	int i;

	for (i = 0; str[i] != '\0' && sub[i] != '\0'; i++)
		if (str[i] != sub[i])
			return 0;

	return sub[i] == '\0';
}

static VAR array_sub(VAR left, VAR right){
	VAR ans;
	ans.type = ARRAY_T;

	switch(right.type) {
		case ARRAY_T:
			ans.value.arrValue = array_substract(left.value.arrValue, right.value.arrValue);
			return ans;
		default:
			ans.value.arrValue = array_remove(left.value.arrValue, right);
			return ans;
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
		case ARRAY_T:
		{
			VAR multi = anon_arr(0);
			int i;
			for(i = 0 ; i < left.value.intValue ; i++){
				array_cat(multi.value.arrValue, right.value.arrValue);
			}
			return multi;
		}
		default:
			fprintf(stderr, "Error. Tipo desconocido: %d\n", right.type);
			exit(0);
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
		case ARRAY_T:
		{
			return integer_prod(anon_int(left.value.floatValue), right);
		}
		default:
			fprintf(stderr, "Error. Tipo desconocido: %d\n", right.type);
			exit(0);
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
		default:
			fprintf(stderr, "Error. Tipo desconocido: %d\n", right.type);
			exit(0);
	}
}




static VAR integer_div(VAR left, VAR right){
	switch(right.type){
		case INT_T:
		{
			int iresult = left.value.intValue / right.value.intValue;
			return anon_int(iresult);
		}
		case FLOAT_T:
		{
			float fresult = left.value.intValue / right.value.floatValue;
			return anon_float(fresult);
		}
		case STR_T:
		{
			printf("Error: se intenta dividir un numero por un texto. El programa no puede continuar\n");
			exit(1);
		}
		case ARRAY_T:
		{
			printf("Error: se intenta dividir un numero por una lista. El programa no puede continuar\n");
			exit(1);
		}
		default:
			fprintf(stderr, "Error. Tipo desconocido: %d\n", right.type);
			exit(0);
	}
}


static VAR float_div(VAR left, VAR right){
	switch(right.type){
		case INT_T:
		{
			float iresult = left.value.intValue / right.value.intValue;
			return anon_float(iresult);
		}
		case FLOAT_T:
		{
			float fresult = left.value.intValue / right.value.floatValue;
			return anon_float(fresult);
		}
		case STR_T:
		{
			printf("Error: se intenta dividir un numero por un texto. El programa no puede continuar\n");
			exit(1);
		}
		case ARRAY_T:
		{
			printf("Error: se intenta dividir un numero por una lista. El programa no puede continuar\n");
			exit(1);
		}
		default:
			fprintf(stderr, "Error. Tipo desconocido: %d\n", right.type);
			exit(0);
	}
}



static VAR string_div(VAR left, VAR right){
	switch(right.type){
		case INT_T:
		{
			int len = strlen(left.value.strValue) / right.value.intValue;
			char * str = malloc(len + 1);
			memcpy(str, left.value.strValue, len);
			*(str+len) = 0;
			VAR divided = anon_str(str);
			free(str);
			return divided;
		}
		case FLOAT_T:
		{
			float fresult = left.value.intValue / right.value.floatValue;
			return anon_float(fresult);
		}
		case STR_T:
		{
			printf("Error: se intenta dividir un texto por un texto. El programa no puede continuar\n");
			exit(1);
		}
		case ARRAY_T:
		{
			printf("Error: se intenta dividir un texto por una lista. El programa no puede continuar\n");
			exit(1);
		}
		default:
			fprintf(stderr, "Error. Tipo desconocido: %d\n", right.type);
			exit(0);
	}
}
