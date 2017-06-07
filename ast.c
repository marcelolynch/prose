#include "ast.h"
#include <stdio.h>

void doPrint(PrintNode * p);
void doAssign(AssignmentNode * a);

void produce(Statements * block){
	while(block != NULL){
		switch(block->type){
			case ASSIGNMENT: 
				doAssign((AssignmentNode*)block->expressionNode);
				break;
			case PRINT_CALL:
				doPrint((PrintNode*)block->expressionNode);
				break;
		}

		block = block->next;
	}
}


void doAssign(AssignmentNode * a){
	switch(a->type){
		case STR_T:
			printf("assign(%d, \"%s\", STR_T);\n", a->var_id, *((char**)a->value));
			//free(*(a->value));
		break;
		
		case INT_T:
	 		printf("intHolder = %d;\n", *((int*)a->value));
			printf("assign(%d, &intHolder, INT_T);\n", a->var_id);
		break;

		case FLOAT_T:
	 		printf("floatHolder = %f;\n", *((float*)a->value));
			printf("assign(%d, &intHolder, FLOAT_T);\n", a->var_id);
		break;

	}
}

void doPrint(PrintNode * p){
	printf("print_var(%d);\n", p->var_id);
}