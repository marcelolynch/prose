#include "ast.h"
#include <stdio.h>

void doPrint(PrintNode * p);
void doAssign(AssignmentNode * a);
void doBooleanBinary(BoolNode*node, char* op);
void doBooleanCondition(BoolNode * node);
void doBooleanComp(BoolNode * node, char* op);


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
	switch(a->type){
		case STR_T:
			printf("(char*)assign(%d, \"%s\", STR_T);\n", a->var_id, *((char**)a->value));
			//free(*(a->value));
		break;
		
		case INT_T:
	 		printf("intHolder = %d;\n", *((int*)a->value));
			printf("(int)assign(%d, &intHolder, INT_T);\n", a->var_id);
		break;

		case FLOAT_T:
	 		printf("floatHolder = %f;\n", *((float*)a->value));
			printf("(float)assign(%d, &floatHolder, FLOAT_T);\n", a->var_id);
		break;

	}
}

void doPrint(PrintNode * p){
	printf("print_var(%d);\n", p->var_id);
}


void doBooleanCondition(BoolNode * node){
	switch(node->type){

		case BOOL_LITERAL:
			printf("%d", *((int*)node->left));
			break;

		case BOOL_NOT:
			printf("!(");
			doBooleanCondition((BoolNode*)node->left);
			printf(")");
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
	printf("(compare(%d, %d) %s 0)", *((int*)node->left), *((int*)node->right), op);
}