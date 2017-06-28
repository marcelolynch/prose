#include "include/ast.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void do_print(ExpressionNode * p);
void do_assign(AssignmentNode * a);
void do_while(WhileNode* w_node);
void do_if(IfNode* if_node);
void do_function_call(FunctionNode * fn);
void do_exit_call();

void do_boolean_binary(BoolNode*node, char* op);
void do_boolean_condition(BoolNode * node);
void do_boolean_comp(BoolNode * node, char* op);
void do_equals(BoolNode * node);
void do_not_equals(BoolNode * node);
char* get_expression(ExpressionNode * operation);
char * get_arith_binary(ExpressionNode* expr, char* funcName);
void do_array_assignment(ArrayAssignment* a);


/* Recibe una lista de bloques de codigo (raices de arboles sintacticos)
 y produce output por salida estandar del codigo C correspondiente  */
void produce(StatementList * block){
	while(block != NULL){
		switch(block->type){
			/*
				Cada tipo de statement tiene un nodo asignado: se castea y procesa
				śegún corresponda.
			*/
			case ASSIGNMENT:
				do_assign((AssignmentNode*)block->body);
				break;

			case ARRAY_ASSIGNMENT:
				do_array_assignment((ArrayAssignment*)block->body);
				break;

			case PRINT_CALL:
				do_print((ExpressionNode*)block->body);
				break;

			case WHILE_LOOP:
				do_while((WhileNode*) block->body);
				break;

			case IF_THEN_ELSE:
				do_if((IfNode*)block->body);
				break;

			case FUNCTION_CALL:
				do_function_call((FunctionNode*)block->body);
				break;

			case EXIT_CALL:
				do_exit_call();
				break;

			default:
				break;
		}

		StatementList * prev = block;

		block = block->next;

		free(prev);
	}
}

void do_function_call(FunctionNode * fn){
	switch(fn->function){
		case ARR_APPEND: 
		{
			char * expr = get_expression(fn->second);
			printf("append(%d, %s);\n", *((int*)fn->first), expr);
			free(expr);
			break;
		}
		case TO_UPPER:
			printf("toupper_str(%d);\n", *((int*)fn->first));
			break;
		case TO_LOWER:
			printf("tolower_str(%d);\n", *((int*)fn->first));
			break;
		case INCREMENT:
			printf("inc(%d);\n", *((int*)fn->first));
			break;
		case DECREMENT:
			printf("dec(%d);\n", *((int*)fn->first));
			break;
		case SCAN_READ:
			printf("scan(%d, %d);\n", *((int*)fn->first), *((int*)fn->second));
			break;
		default:
			fprintf(stderr, "Error. Operacion desconocida: %d", fn->function);
			exit(1);
			break;
	}
}

/* Produce output por salida estandar:
	codigo para un while loop */
void do_while(WhileNode* w_node){
		printf("\n\nwhile(");

		do_boolean_condition(w_node->condition); //Se outputea la condicion

		printf("){\n");

		produce(w_node->body);	// El codigo dentro del while es lo mismo que un programa entero
								// (una serie de Statements)

		printf("}\n\n");

}



/* Produce output por salida estandar:
	codigo para una serie de if-then-else */
void do_if(IfNode* if_node){
	printf("\n\nif(");
	do_boolean_condition(if_node->condition); //Se outputea la condicion
	printf("){\n");

	produce(if_node->body); // El codigo dentro del if es lo mismo que un programa entero
							// (una serie de Statements)

	printf("}\n");

	/* De aca para adelante se encadenan los else-if*/
	while(if_node->elseif != NULL){
		if_node = if_node->elseif;
		printf("else if(");
		do_boolean_condition(if_node->condition);
		printf("){\n");
		produce(if_node->body);
		printf("} ");
	}


}

/* Produce output por salida estandar:
	codigo de asignación de un valor a una variable nombrada (con ID) */
void do_assign(AssignmentNode * a){
	char * expression = get_expression(a->value);
	printf("assign(%d, %s);\n", a->var_id, expression);
	free(expression);
}

#define STR_OVERHEAD 25
#define MAX_DIGITS 30

/* Produce output por salida estandar:
	codigo de asignación de un valor a una posicion de un arreglo) */
void do_array_assignment(ArrayAssignment* a){
	ExpressionNode* array = a->array;
	ExpressionNode* value = a->value;
	printf("array_assign(");
	switch(array->type){
		case INDEXED_ARRAY:
		{
			char * idx = get_expression((ExpressionNode*)array->right);
			char * val = get_expression(value);
			printf("get_var(%d), %s, %s);\n", *((int*)array->left), idx, val);

			free(idx);

			break;
		}

		case NESTED_INDEXING:
		{
			/* right apunta a la expresion de indice: en a[10-1] apunta al nodo de expresion para "10-1" */
			char * idx = get_expression((ExpressionNode*)array->right);

			/* left apunta a un ExpressionNode correspondiente
				al arreglo que se esta accediendo anidado: ejemplo
				en arr[1][2], left es la expresion que resuelve arr[1] y
				devuelve ese arreglo.
			*/
			char * ary = get_expression((ExpressionNode*)array->left);

			// Value tiene la expresion a asignar
			char * val = get_expression(value);
			printf("%s, %s, %s);", ary, idx, val);


			free(idx);
			break;
		}

		default:
			//This should never happen
			break;

	}
}


/* Produce output por salida estandar:
	codigo para imprimir una expresion */
void do_print(ExpressionNode * p){
	char * expr = get_expression(p);
	printf("print_var(%s, 1);\n", expr);
	free(expr);
}

/* Produce output por salida estandar:
	codigo asociado a una expresion booleana */
void do_boolean_condition(BoolNode * node){
	switch(node->type){

		case TRUE_LITERAL:
			printf("%d", BOOL_TRUE);
			break;

		case FALSE_LITERAL:
			printf("%d", BOOL_FALSE);
			break;

		case BOOL_NOT:
			printf("!");
			do_boolean_condition((BoolNode*)node->left);
			break;

		case BOOL_AND:
			do_boolean_binary(node, "&&");
			break;

		case BOOL_OR:
			do_boolean_binary(node, "||");
			break;

		case COMP_LT:
			do_boolean_comp(node, "<");
			break;

		case COMP_LE:
			do_boolean_comp(node, "<=");
			break;

		case COMP_EQ:
			do_equals(node);
			break;

		case COMP_NEQ:
			do_not_equals(node);
			break;

		case COMP_GT:
			do_boolean_comp(node, ">");
			break;

		case COMP_GE:
			do_boolean_comp(node, ">=");
			break;
	}
}

/* Produce output por salida estandar:
	codigo asociado a una expresion booleana logica con dos operandos
	(se pasa el operador por parametro) */
void do_boolean_binary(BoolNode*node, char* op){
	printf("(");
	do_boolean_condition((BoolNode*)node->left);
	printf(" %s ", op);
	do_boolean_condition((BoolNode*)node->right);
	printf(")");
}

/* Produce output por salida estandar:
	codigo asociado a una expresion booleana de comparacion
	(se pasa el operador por parametro) */
void do_boolean_comp(BoolNode * node, char* op){
	char * first = get_expression((ExpressionNode*)node->left);
	char * second = get_expression((ExpressionNode*)node->right);

	printf("(compare(%s, %s) %s 0)", first, second, op);

	free(first);
	free(second);
}

void do_equals(BoolNode * node){
	char * first = get_expression((ExpressionNode*)node->left);
	char * second = get_expression((ExpressionNode*)node->right);

	printf("(is_equals(%s, %s))", first, second);

	free(first);
	free(second);
}

void do_not_equals(BoolNode * node){
	printf("!");
	do_equals(node);
}

void do_exit_call() {
	printf("exit(0);\n");
}

/* Genera un string con el codigo asociado a una expresion
(un valor literal, expresion aritmetica o booleana, una variable nombrada o acceso a la posicion de un arreglo)*/
char* get_expression(ExpressionNode * operation){
	char * result;
	switch(operation->type){
		case VARIABLE:
		{
			result = malloc(STR_OVERHEAD + MAX_DIGITS);
			sprintf(result, "get_var(%d)", *(int*)operation->left);
			free(operation->left);
			break;
		}
		case STR_LITERAL:
		{
			char * str = (char*)operation->left;
			result = malloc(STR_OVERHEAD + strlen(str));
			sprintf(result, "anon_str(\"%s\")", str);
			free(operation->left);
			break;
		}

		case INT_LITERAL:
		{
			result = malloc(STR_OVERHEAD + MAX_DIGITS);
			sprintf(result, "anon_int(%d)", *((int*)operation->left));
			free(operation->left);
			break;
		}

		case FLOAT_LITERAL:
		{
			result = malloc(STR_OVERHEAD + MAX_DIGITS);
			sprintf(result, "anon_float(%.5f)", *((float*)operation->left));
			free(operation->left);
			break;
		}

		case ARRAY_LITERAL:
		{
				result = malloc(STR_OVERHEAD);
				sprintf(result, "anon_arr(%d", *((int*)operation->right));
				ExpressionList * list = (ExpressionList*)operation->left;

				while(list != NULL){
					char * expr = get_expression(list->expression);
					int len = strlen(result);
					result = realloc(result, len + strlen(expr) + 3); //+3 para coma, espacio y '\0'.
					sprintf(result+len, ", %s", expr);
					free(expr);
					list = list->next;
				}
				int len = strlen(result);
				result = realloc(result, len + 2); //Parentesis y el '\0'
				sprintf(result+len, ")");

				return result;
			}

		case INDEXED_ARRAY:
		{
			char * idx = get_expression((ExpressionNode*)operation->right);

			result = malloc(STR_OVERHEAD + strlen(idx));
			sprintf(result, "array_index(get_var(%d), %s)", *((int*)operation->left), idx);

			free(idx);

			break;
		}

		case NESTED_INDEXING:
		{
			char * idx = get_expression((ExpressionNode*)operation->right);
			char * ary = get_expression((ExpressionNode*)operation->left);

			result = malloc(STR_OVERHEAD + strlen(idx) + strlen(ary));
			sprintf(result, "array_index(%s, %s)", ary, idx);


			free(idx);
			break;
		}

		case ARIT_UNARY_MINUS: {
			char * expr = get_expression((ExpressionNode*)operation->left);
			result = malloc(strlen(expr) + STR_OVERHEAD);
			sprintf(result, "var_minus(%s)", expr);

			free(expr);
			break;
		}

		case ARIT_SUM:
		{
			result = get_arith_binary(operation, "var_sum");
			break;
		}


		case ARIT_SUB:
		{
			result = get_arith_binary(operation, "var_sub");
			break;
		}

		case ARIT_PROD:
		{
			result = get_arith_binary(operation, "var_prod");
			break;
		}

		case ARIT_DIV:
		{
			result = get_arith_binary(operation, "var_div");
		}

	}

	free(operation);

	return result;
}

/* Genera un string con el codigo asociado a una expresion  aritmetica binaria (+, -, *) */
char * get_arith_binary(ExpressionNode* expr, char* funcName){
			char * left = get_expression((ExpressionNode*)expr->left);
			char * right = get_expression((ExpressionNode*)expr->right);
			char * result = malloc(STR_OVERHEAD + strlen(left) + strlen(right) + 1);
			sprintf(result, "%s(%s, %s)", funcName, left, right);
			free(left);
			free(right);
			return result;
}
