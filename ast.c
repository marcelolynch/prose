#include "ast.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void doPrint(ExpressionNode * p);
void doAssign(AssignmentNode * a);
void doBooleanBinary(BoolNode*node, char* op);
void doBooleanCondition(BoolNode * node);
void doBooleanComp(BoolNode * node, char* op);
char* getExpr(ExpressionNode * operation);
char * doAritBinary(ExpressionNode* expr, char* funcName);
void * doArrayCreation(AssignmentNode * a);


void produce(Statements * block){
	while(block != NULL){
		switch(block->type){

			case ASSIGNMENT:
				doAssign((AssignmentNode*)block->body);
				break;
				
			case PRINT_CALL:
				doPrint((ExpressionNode*)block->body);
				break;

			case WHILE_LOOP:
				printf("\n\nwhile(");
				WhileNode* w_node = (WhileNode*) block->body;
				doBooleanCondition(w_node->condition);
				printf("){\n");
				produce(w_node->body);
				printf("}\n\n");
				break;

			case IF_THEN_ELSE:
				printf("\n\nif(");
				IfNode* if_node = (IfNode*)block->body;
				doBooleanCondition(if_node->condition);
				printf("){\n");
				produce(if_node->body);
				printf("}\n");
				while(if_node->elseif != NULL){
					if_node = if_node->elseif;
					printf("else if(");
					doBooleanCondition(if_node->condition);
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



void doAssign(AssignmentNode * a){
	if(a->value->type == ARRAY_LITERAL){
		doArrayCreation(a);
	}
	else{ 
		char * expression = getExpr(a->value);
		printf("assign(%d, %s);\n", a->var_id, expression);
		free(expression);
	}
}


#define STR_OVERHEAD 25
#define MAX_DIGITS 30
char* getExpr(ExpressionNode * operation){
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

		case ARIT_UNARY_MINUS: {
			char * expr = getExpr((ExpressionNode*)operation->left);
			result = malloc(strlen(expr) + STR_OVERHEAD);
			sprintf(result, "var_minus(%s)", expr);

			free(expr);
			break;
		}


		case ARIT_SUM:
		{
			result = doAritBinary(operation, "var_sum");
			break;
		}


		case ARIT_SUB:
		{
			result = doAritBinary(operation, "var_sub");
			break;
		}

		case ARIT_PROD:
		{
			result = doAritBinary(operation, "var_prod");
			break;
		}

		case ARIT_DIV:
		{
			result = doAritBinary(operation, "var_div");
		}

	}

	free(operation);

	return result;
}


void * doArrayCreation(AssignmentNode * a){
	printf("assign(%d, anon_arr());\n", a->var_id);
	ExpressionList * list = (ExpressionList*)a->value->left;
	while(list != NULL){
		printf("array_add(%d, %s);\n", a->var_id, getExpr(list->expression));
		list = list->next;
	}
}


char * doAritBinary(ExpressionNode* expr, char* funcName){
			char * left = getExpr((ExpressionNode*)expr->left);
			char * right = getExpr((ExpressionNode*)expr->right);
			char * result = malloc(STR_OVERHEAD + strlen(left) + strlen(right) + 1);
			sprintf(result, "%s(%s, %s)", funcName, left, right);
			free(left);
			free(right);
			return result;
}

void doPrint(ExpressionNode * p){
	char * expr = getExpr(p);
	printf("print_var(%s, 1);\n", expr);
	free(expr);
}


void doBooleanCondition(BoolNode * node){
	switch(node->type){

		case TRUE_LITERAL:
			printf("%d", BOOL_TRUE);
			break;

		case FALSE_LITERAL:
			printf("%d", BOOL_FALSE);
			break;

		case BOOL_NOT:
			printf("!");
			doBooleanCondition((BoolNode*)node->left);
			break;

		case BOOL_AND:
			doBooleanBinary(node, "&&");
			break;

		case BOOL_OR:
			doBooleanBinary(node, "||");
			break;

		case COMP_LT:
			doBooleanComp(node, "<");
			break;

		case COMP_LE:
			doBooleanComp(node, "<=");
			break;

		case COMP_EQ:
			doBooleanComp(node, "==");
			break;

		case COMP_NEQ:
			doBooleanComp(node, "!=");
			break;

		case COMP_GT:
			doBooleanComp(node, ">");
			break;

		case COMP_GE:
			doBooleanComp(node, ">=");
			break;
	}
}


void doBooleanBinary(BoolNode*node, char* op){
			printf("(");
			doBooleanCondition((BoolNode*)node->left);
			printf(" %s ", op);
			doBooleanCondition((BoolNode*)node->right);
			printf(")");
}

void doBooleanComp(BoolNode * node, char* op){

	char * first = getExpr((ExpressionNode*)node->left);
	char * second = getExpr((ExpressionNode*)node->right);

	printf("(compare(%s, %s) %s 0)", first, second, op);

	free(first);
	free(second);
}
