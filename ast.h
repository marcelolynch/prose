#ifndef __ast_h
#define __ast_h

#include "variable_manager.h"

#define BOOL_TRUE 1
#define BOOL_FALSE 0

typedef enum
{
	TRUE_LITERAL,
	FALSE_LITERAL,
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
	INT_LITERAL, 
	FLOAT_LITERAL,
	STR_LITERAL,
	ARRAY_LITERAL,
	ARIT_UNARY_MINUS,
	ARIT_SUM,
	ARIT_SUB,
	ARIT_PROD,
	ARIT_DIV
} expr_type;


typedef enum{
	ASSIGNMENT,
	PRINT_CALL,
	WHILE_LOOP,
	IF_THEN_ELSE
} stmnt_type;



typedef struct StNode{
	stmnt_type type;
	void * body;
	struct StNode * next;
} Statements;


typedef struct block{
	void * node;
	stmnt_type type;
} Block;



typedef struct bc{
	bool_operation type;
	void * left;
	void * right;
} BoolNode;


typedef struct ar_n{
	expr_type type;
	void * left;
	void * right;
} ExpressionNode;


typedef struct expList{
	ExpressionNode * expression;
	struct expList* next;
} ExpressionList;

typedef struct wn{
	BoolNode * condition;
	Statements * body;
} WhileNode;


typedef struct in{
	BoolNode * condition;
	Statements * body;
	struct in * elseif;
} IfNode;


typedef struct asn{
	int var_id;
	ExpressionNode * value;
} AssignmentNode;


void produce(Statements * block);

#endif
