#ifndef __ast_h
#define __ast_h

#include "variable_manager.h"

#define ASSIGNMENT 		1
#define PRINT_CALL 		2


#define WHILE_LOOP 		3


typedef enum
{
	BOOL_LITERAL,
	BOOL_COMPARISON,
	BOOL_AND,
	BOOL_NOT,
	BOOL_OR,
	COMP_LT,
	COMP_LE,
	COMP_EQ,
	COMP_NEQ,
	COMP_GT,
	COMP_GE
} bool_operation;


typedef enum{
	VARIABLE,
	INT_TYPE, FLOAT_TYPE, STR_TYPE,
	ARIT_SUM,
	ARIT_SUB,
	ARIT_PROD,
	ARIT_DIV
} arithm_operation;


typedef int exp_t; 


typedef struct StNode{
	exp_t type;
	void * expressionNode;
	struct StNode * next;
} Statements;  


typedef struct block{
	void * node;
	exp_t type;
} Block;



typedef struct bc{
	bool_operation type;
	void * left;
	void * right;
} BoolNode;


typedef struct ar_n{
	arithm_operation type;
	void * left;
	void * right;
} ArithNode;


typedef struct wn{	
	BoolNode * condition; 
	Statements * body;
} WhileNode;


typedef struct in{
	BoolNode * condition;
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


void produce(Statements * block, char * indent);

#endif