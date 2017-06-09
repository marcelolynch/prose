#include "ast.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void doPrint(PrintNode * p);
void doAssign(AssignmentNode * a);
void doBooleanBinary(BoolNode*node, char* op);
void doBooleanCondition(BoolNode * node);
void doBooleanComp(BoolNode * node, char* op);
char* getArith(ArithNode * operation);


void produce(Statements * block, char * indent){
	while(block != NULL){
		printf("%s", indent);
		switch(block->type){

			case ASSIGNMENT:
				doAssign((AssignmentNode*)block->expressionNode);
				break;
				
			case PRINT_CALL:
				doPrint((PrintNode*)block->expressionNode);
				break;

			case WHILE_LOOP:
				printf("\n\nwhile(");
				WhileNode* w_node = (WhileNode*) block->expressionNode;
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
	char * expression = getArith(a->value);
	printf("assign(%d, %s);\n", a->var_id, expression);
	free(expression);
}


#define STR_OVERHEAD 25
#define MAX_DIGITS 30
char* getArith(ArithNode * operation){
	char * result;
	switch(operation->type){
		case STR_TYPE:
		{
			char * str = *((char**)operation->left);
			result = malloc(STR_OVERHEAD + strlen(str));
			sprintf(result, "anon_str(\"%s\")", str);
			break;
		}

		case INT_TYPE:
		{
			result = malloc(STR_OVERHEAD + MAX_DIGITS);
			sprintf(result, "anon_int(%d)", *((int*)operation->left));
			break;
		}

		case FLOAT_TYPE:
		{
			result = malloc(STR_OVERHEAD + MAX_DIGITS);
			sprintf(result, "anon_float(%.10f)", *((float*)operation->left));
			break;
		}

		case ARIT_SUM:
		{
			char * left = getArith((ArithNode*)operation->left);
			char * right = getArith((ArithNode*)operation->right);
			result = malloc(STR_OVERHEAD + strlen(left) + strlen(right) + 1);
			sprintf(result, "sum(%s, %s)", left, right);
			free(left);
			free(right);
			break;
		}
	}
	return result;
}

void doPrint(PrintNode * p){
	char * expr = getArith(p->expression);
	printf("print(%s);\n", expr);
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
