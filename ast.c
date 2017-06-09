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


void produce(Statements * block, char * indent){
	while(block != NULL){
		printf("%s", indent);
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
				produce(w_node->body, "\t");
				printf("%s}\n\n",indent);
				break;
		}

		block = block->next;
	}
}



void doAssign(AssignmentNode * a){
	char * expression = getExpr(a->value);
	printf("assign(%d, %s);\n", a->var_id, expression);
	free(expression);
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

		case ARIT_SUM:
		{
			char * left = getExpr((ExpressionNode*)operation->left);
			char * right = getExpr((ExpressionNode*)operation->right);
			result = malloc(STR_OVERHEAD + strlen(left) + strlen(right) + 1);
			sprintf(result, "sum(%s, %s)", left, right);
			free(left);
			free(right);
			break;
		}
	}

	free(operation);

	return result;
}

void doPrint(ExpressionNode * p){
	char * expr = getExpr(p);
	printf("print_var(%s);\n", expr);
	free(expr);
}


void doBooleanCondition(BoolNode * node){
	switch(node->type){

		case BOOL_LITERAL:
			printf("%d", *((int*)node->left));
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
			doBooleanBinary(node, "<");
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
	printf("(compare(get_var(%d), get_var(%d)) %s 0)", *((int*)node->left), *((int*)node->right), op);
}
