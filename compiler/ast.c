#include "include/ast.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void do_print(ExpressionNode * p);
void do_assign(AssignmentNode * a);
void do_boolean_binary(BoolNode*node, char* op);
void do_boolean_condition(BoolNode * node);
void do_boolean_comp(BoolNode * node, char* op);
char* get_expression(ExpressionNode * operation);
char * do_arith_binary(ExpressionNode* expr, char* funcName);
void do_array_creation(AssignmentNode * a);
void do_array_assignment(ArrayAssignment* a);

void produce(Statements * block){
	while(block != NULL){
		switch(block->type){

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
				printf("\n\nwhile(");
				WhileNode* w_node = (WhileNode*) block->body;
				do_boolean_condition(w_node->condition);
				printf("){\n");
				produce(w_node->body);
				printf("}\n\n");
				break;

			case IF_THEN_ELSE:
				printf("\n\nif(");
				IfNode* if_node = (IfNode*)block->body;
				do_boolean_condition(if_node->condition);
				printf("){\n");
				produce(if_node->body);
				printf("}\n");
				while(if_node->elseif != NULL){
					if_node = if_node->elseif;
					printf("else if(");
					do_boolean_condition(if_node->condition);
					printf("){\n");
					produce(if_node->body);
					printf("} ");
				}

				break;
			default:
				break;
		}

		free(block);
		
		block = block->next;
	}
}



void do_assign(AssignmentNode * a){
	if(a->value->type == ARRAY_LITERAL){
		do_array_creation(a);
	}
	else{ 
		char * expression = get_expression(a->value);
		printf("assign(%d, %s);\n", a->var_id, expression);
		free(expression);
	}
}

#define STR_OVERHEAD 25
#define MAX_DIGITS 30


void do_array_assignment(ArrayAssignment* a){
	ExpressionNode* array = a->array;
	ExpressionNode* value = a->value;
	printf("array_assign(");	
	switch(array->type){
		case INDEXED_ARRAY:
		{
			char * idx = get_expression((ExpressionNode*)array->right);
			char * val = get_expression(value);
			printf("get_var(%d), %s, %s);", *((int*)array->left), idx, val);
	
			free(idx);

			break;
		}

		case NESTED_INDEXING:
		{
			
			char * idx = get_expression((ExpressionNode*)array->right);
			char * ary = get_expression((ExpressionNode*)array->left);
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
			sprintf(result, "anon_float(%.10f)", *((float*)operation->left));
			free(operation->left);
			break;
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
			result = do_arith_binary(operation, "var_sum");
			break;
		}


		case ARIT_SUB:
		{
			result = do_arith_binary(operation, "var_sub");
			break;
		}

		case ARIT_PROD:
		{
			result = do_arith_binary(operation, "var_prod");
			break;
		}

		case ARIT_DIV:
		{
			result = do_arith_binary(operation, "var_div");
		}

	}

	free(operation);

	return result;
}


void do_array_creation(AssignmentNode * a){
	printf("v = anon_arr(NULL);\n");
	ExpressionList * list = (ExpressionList*)a->value->left;
	while(list != NULL){
		printf("array_add(v.value.arrValue, %s);\n", get_expression(list->expression));
		list = list->next;
	}
	printf("assign(%d, v);\n", a->var_id);
	printf("free_var_resources(&v);\n");

}


char * do_arith_binary(ExpressionNode* expr, char* funcName){
			char * left = get_expression((ExpressionNode*)expr->left);
			char * right = get_expression((ExpressionNode*)expr->right);
			char * result = malloc(STR_OVERHEAD + strlen(left) + strlen(right) + 1);
			sprintf(result, "%s(%s, %s)", funcName, left, right);
			free(left);
			free(right);
			return result;
}

void do_print(ExpressionNode * p){
	char * expr = get_expression(p);
	printf("print_var(%s, 1);\n", expr);
	free(expr);
}


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
			do_boolean_comp(node, "==");
			break;

		case COMP_NEQ:
			do_boolean_comp(node, "!=");
			break;

		case COMP_GT:
			do_boolean_comp(node, ">");
			break;

		case COMP_GE:
			do_boolean_comp(node, ">=");
			break;
	}
}


void do_boolean_binary(BoolNode*node, char* op){
			printf("(");
			do_boolean_condition((BoolNode*)node->left);
			printf(" %s ", op);
			do_boolean_condition((BoolNode*)node->right);
			printf(")");
}

void do_boolean_comp(BoolNode * node, char* op){

	char * first = get_expression((ExpressionNode*)node->left);
	char * second = get_expression((ExpressionNode*)node->right);

	printf("(compare(%s, %s) %s 0)", first, second, op);

	free(first);
	free(second);
}
