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
	switch(a->value->type){
		case STR_TYPE:
			printf("assign(%d, anon_str(\"%s\"));\n", a->var_id, *((char**)a->value->left));
			//free(*(a->value));
		break;
		
		case INT_TYPE:
			printf("assign(%d, anon_int(%d));\n", a->var_id, *((int*)a->value->left));
		break;

		case FLOAT_TYPE:
			printf("assign(%d, anon_float(%f));\n",a->var_id , *((float*)a->value->left));
		break;

		case ARIT_SUM:
			printf("assign(%d, sum(", a->var_id);

	}
}


char* getArith(ArithNode * operation){

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