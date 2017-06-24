#ifndef __ast_h
#define __ast_h

#define BOOL_TRUE 1
#define BOOL_FALSE 0

/*
	Este header file contiene definiciones de tipos
	para construir el arbol abstracto de sintaxis (desde ast.c)

*/

typedef enum
{
	TRUE_LITERAL,
	FALSE_LITERAL,
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
	INDEXED_ARRAY,
	NESTED_INDEXING,
	ARIT_UNARY_MINUS,
	ARIT_SUM,
	ARIT_SUB,
	ARIT_PROD,
	ARIT_DIV
} expr_type;


typedef enum{
	ASSIGNMENT,
	ARRAY_ASSIGNMENT,
	PRINT_CALL,
	WHILE_LOOP,
	IF_THEN_ELSE
} stmnt_type;


/* 
    Statements funciona como lista encadenada 
	de sentencias aisladas (los tipos posibles
	son los definidos en el enum stmnt_type).
	
	Body apunta al nodo correspondiente a la sentencia,
	que debe ser casteado oportunamente a alguna estructura
	de nodo segun corresponda al tipo que indica el campo type
*/
typedef struct StNode{
	stmnt_type type;
	void * body;
	struct StNode * next;
} Statements;


/*
	Nodo para la lista encadenada Statements,
	se utiliza en el parser como intermediario de 
	nodos aislados (en las reducciones)
	antes de construir la lista.

*/
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




/*
	Se utiliza para expresiones como 
	"que a[1+2][2] valga 3 + 4".

	En value se guarda la expresion a asignar (3+4)
	y array apunta a la expresion de acceso al arreglo,
	que puede ser INDEXED_ARRAY (a[1+2]) o NESTED_INDEXING (a[1][2]).
	
	INDEXED_ARRAY utiliza el campo left de ExpressionNode para guardar 
		el ID de la variable que tiene el arreglo, y
		el campo right para la expresion correspondiente al indice.
		En el caso a[1+2] seria:
			{
				type: INDEXED_ARRAY
				left: id de variable a
				right: ExpressionNode para 1+2
			}

	NESTED_INDEXING utiliza el campo right de ExpressionNode para guardar el indice
	y el left para apuntar al acceso anterior del arreglo: en a[1][2] el nodo seria
		{ type : NESTED_INDEXING
		  left -> 2
		  right : puntero a ExpressionNode de INDEXED_ARRAY como se describio arriba
		 }
	
	Vease el metodo de construccion do_array_assignment en ast.c para ver como se acceden
	y castean los campos correspondientes.

*/
typedef struct arr_as {
	ExpressionNode * array;
	ExpressionNode * value;
} ArrayAssignment;





/* Produce el codigo a partir de la raiz del AST */
void produce(Statements * block);

#endif
