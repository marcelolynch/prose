#include "variable_manager.h"

#ifndef __ast_h
#define __ast_h



#define ASSIGNMENT 1
#define PRINT_CALL 2

#define COMPARISON

#define WHILE_LOOP

typedef int exp_t; 




typedef struct StNode{
	int type;
	void * expressionNode;
	struct StNode * next;
} Statements;  


typedef struct block{
	void * node;
	exp_t type;
} Block;


typedef struct bc{

} BoolCheck;




typedef struct wn{	
	BoolCheck * condition; 
	Statements * body;
} WhileNode;


typedef struct in{
	BoolCheck * condition;
	Statements * body;
} IfNode;

typedef struct asn{
	int var_id;
	int type;
	void * value;
} AssignmentNode;


typedef struct prn{
	int var_id;
} PrintNode;


void produce(Statements * block);

#endif