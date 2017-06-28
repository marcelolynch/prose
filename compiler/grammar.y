
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/ast.h"

#define MAX_IDS 10000


int yylex();
void yyerror (char const *s);


int var_count = 0;

char * identifiers[MAX_IDS] = {0};

int getId(char * strId){
	int i;

	for(i = 0 ; i < MAX_IDS && identifiers[i] != NULL ; i++){
		if(strcmp(identifiers[i], strId) == 0){
			return i;
		}
	}

	if(i == MAX_IDS){
		return -1;
	}

	identifiers[i] = malloc(strlen(strId) + 1);
	strcpy(identifiers[i], strId);
	printf("map_name(%d, \"%s\");\n", i, strId);

	return i;

}

int list_length(ExpressionList * list){
	int len = 0;
	while(list != NULL){
		len++;
		list = list->next;
	}
	return len;
}

%}


%union {
  int intval;
  char * strval;
  float floatval;

  AssignmentNode * assignment;
  ArrayAssignment * arr_assign;

  WhileNode * whilenode;
  IfNode * ifnode;
  BoolNode * boolnode;
  FunctionNode* fnnode;

  ExpressionNode * exprnode;

  ExpressionList * explist;

  Block * block;


  StatementList * statements;

  bool_operation boolop;
}

%error-verbose

%token <strval> IDENTIFIER;
%token <strval> STR;
%token <intval> NUM;
%token <floatval> FLOAT;

%token PRINT;
%token ANEXAR;
%token A;
%token MAYUSCULA;
%token MINUSCULA;
%token DECREMENTAR;
%token INCREMENTAR;
%token PASAR;

%token QUE;
%token VALGA;

%token SEP;

%token WHILE;
%token UNTIL;
%token IF;
%token ELSEIF;
%token ELSE;

%token DO;
%token END;
%token WEND;

%token AND;
%token OR;
%token NOT;

%token LE;
%token GE;
%token LT;
%token GT;
%token EQ;
%token NEQ;

%token TRUE FALSE;

%token EXIT;


%left LE GE EQ AND OR NOT '+' '*' '/' '-';


%type <assignment> asig;
%type <arr_assign> arr_asig;

%type <statements> program;
%type <exprnode> print;
%type <block> block;
%type <explist> explist;
%type <explist> array;

%type <fnnode> func_call;

%type <whilenode> while;

%type <ifnode> if;
%type <ifnode> elseif;

%type <boolop> bool_comp;
%type <boolnode> condition;
%type <exprnode> expression;
%type <exprnode> arr_indexing

%start entry

%%




entry : program {

		produce($1);

	  	}



program :

		block
		   {
		   	$$ = malloc(sizeof(*$$));
			$$->type = $1->type;;
			$$->body = $1->node;
			$$->next = NULL;

			free($1);

			}

		| block program

			{
			$$ = malloc(sizeof(*$$));

			$$->type = $1->type;
			$$->body = $1->node;
			$$->next = $2;

			free($1);
			}

		;


block	: asig{

			$$ = malloc(sizeof(*$$));
			$$->type = ASSIGNMENT;
			$$->node = $1;

		}
		| arr_asig {
			$$ = malloc(sizeof(*$$));
			$$->type = ARRAY_ASSIGNMENT;
			$$->node = $1;
		}
		| print {

			$$ = malloc(sizeof(*$$));
			$$->type = PRINT_CALL;
			$$->node = $1;
		}

		| while {
			$$ = malloc(sizeof(*$$));
			$$->type = WHILE_LOOP;
			$$->node = $1;
		}
		| if {
			$$ = malloc(sizeof(*$$));
			$$->type = IF_THEN_ELSE;
			$$->node = $1;
		}
	  | func_call {
	 		$$ = malloc(sizeof(*$$));
	 		$$->type = FUNCTION_CALL;
	 		$$->node = $1;
	 	}
		| exit {
			$$ = malloc(sizeof(*$$));
			$$->type = EXIT_CALL;
		}
		;

exit : EXIT;

asig : QUE IDENTIFIER VALGA expression
	 	{
	 		$$ = malloc(sizeof(*$$));
	 		$$->var_id = getId($2);

	 		$$->value = $4;
	 	}
	 ;

arr_asig: QUE arr_indexing VALGA expression
	{
		$$ = malloc(sizeof(*$$));
		$$->array = $2;
		$$->value = $4;
	}
	;

expression : STR
		{
			$$ = malloc(sizeof(*$$));

			$$->type = STR_LITERAL;

			$$->left = malloc(strlen($1) + 1);

			strcpy($$->left, $1);
			}

	 | NUM
	 	{
	 		$$ = malloc(sizeof(*$$));
			$$->type = INT_LITERAL;

			$$->left = malloc(sizeof(int));

			memcpy($$->left, &$1, sizeof(int));
		}

	 | FLOAT
	 	{
	 		$$ = malloc(sizeof(*$$));

			$$->type = FLOAT_LITERAL;

			$$->left = malloc(sizeof(float));

			memcpy($$->left, &$1, sizeof(float));

	 	}
	 | array {
	 	$$ = malloc(sizeof(*$$));
	 	$$->type = ARRAY_LITERAL;
	 	$$->left = $1;
	 	$$->right = malloc(sizeof(int));
	 	*((int*)$$->right) = list_length($1);
	 }

	 | IDENTIFIER
	 	{
			$$ = malloc(sizeof(*$$));
			$$->type = VARIABLE;
			$$->left = malloc(sizeof(int));
			int id = getId($1);
			memcpy($$->left, &id, sizeof(int));
	 	}

	 | arr_indexing
	 	{
	 		$$ = $1;
	 	}

	 |	expression '+' expression
			{
				$$ = malloc(sizeof(*$$));
				$$->type = ARIT_SUM;
				$$->left = $1;
				$$->right = $3;
			}
	 |  expression '*' expression
	 	{
	 		$$ = malloc(sizeof(*$$));
			$$->type = ARIT_PROD;
			$$->left = $1;
			$$->right = $3;

	 	}

	 | expression '-' expression {
	 		$$ = malloc(sizeof(*$$));
			$$->type = ARIT_SUB;
			$$->left = $1;
			$$->right = $3;
	 }

	 | expression '/' expression {
	 		$$ = malloc(sizeof(*$$));
			$$->type = ARIT_DIV;
			$$->left = $1;
			$$->right = $3;
	 }

	 | '-' expression
	 	{
	 		$$ = malloc(sizeof(*$$));
			$$->type = ARIT_UNARY_MINUS;
			$$->left = $2;
	 	}

	 |	'(' expression ')'
			{
				$$ = $2;
			}
		;


func_call : ANEXAR expression A IDENTIFIER
			{
				$$ = malloc(sizeof(*$$));
				$$->function = ARR_APPEND;
				$$->first = malloc(sizeof(int));
				*((int*)$$->first) = getId($4);
				$$->second = $2;
			}
		  | PASAR IDENTIFIER A MAYUSCULA
			{
				$$ = malloc(sizeof(*$$));
				$$->function = TO_UPPER;
				$$->first = malloc(sizeof(int));
				*((int*)$$->first) = getId($2);
			}

		  | PASAR IDENTIFIER A MINUSCULA
			{
				$$ = malloc(sizeof(*$$));
				$$->function = TO_LOWER;
				$$->first = malloc(sizeof(int));
				*((int*)$$->first) = getId($2);
			}
		  | INCREMENTAR IDENTIFIER
		  	{
		  		$$ = malloc(sizeof(*$$));
				$$->function = INCREMENT;
				$$->first = malloc(sizeof(int));
				*((int*)$$->first) = getId($2);
		  	}

		  | DECREMENTAR IDENTIFIER
		  	{
		  		$$ = malloc(sizeof(*$$));
				$$->function = DECREMENT;
				$$->first = malloc(sizeof(int));
				*((int*)$$->first) = getId($2);
		  	}
		  ;


array : '[' explist ']' {
	$$ = $2;
}


arr_indexing: IDENTIFIER '[' expression ']'
			{
				$$ = malloc(sizeof(*$$));
				$$->type = INDEXED_ARRAY;

				$$->left = malloc(sizeof(int));
				int id = getId($1);
				memcpy($$->left, &id, sizeof(int));

				$$->right = $3;
			}
			| arr_indexing '[' expression ']'
				{
					$$ = malloc(sizeof(*$$));
					$$->type = NESTED_INDEXING;
					$$->left = $1;
					$$->right = $3;
				}
			;

explist : expression
			{
				$$ = malloc(sizeof(*$$));
				$$->expression = $1;
				$$->next = NULL;
			}
		| expression ',' explist {
				$$ = malloc(sizeof(*$$));
				$$->expression = $1;
				$$->next = $3;
		}
		;



print : PRINT expression
		{
			$$ = $2;
		}
	  ;




while 	: WHILE SEP condition SEP DO program WEND
			{
				$$ = malloc(sizeof(*$$));
				$$->condition = $3;
				$$->body = $6;
			}
		| UNTIL SEP condition SEP DO program WEND
			{
				$$ = malloc(sizeof(*$$));
				$$->condition = malloc(sizeof(*$$->condition));

				$$->condition->type = BOOL_NOT;
				$$->condition->left = $3;

				$$->body = $6;
			}
		;


if 		: IF SEP condition SEP DO program END
		{
			$$ = malloc(sizeof(*$$));
			$$->condition = $3;
			$$->body = $6;
			$$->elseif = NULL;

		}
		| IF SEP condition SEP DO program elseif END
			{
				$$ = malloc(sizeof(*$$));
				$$->condition = $3;
				$$->body = $6;
				$$->elseif = $7;
			}



elseif : ELSEIF SEP condition SEP program
			{
				$$ = malloc(sizeof(*$$));
				$$->condition = $3;
				$$->body = $5;
				$$->elseif = NULL;

			}
		| ELSEIF SEP condition SEP program elseif
			{
				$$ = malloc(sizeof(*$$));
				$$->condition = $3;
				$$->body = $5;
				$$->elseif = $6;

			}
		| ELSE program
			{
				$$ = malloc(sizeof(*$$));
				$$->body = $2;
				$$->elseif = NULL;
				$$->condition = malloc(sizeof(*$$->condition));
				$$->condition->type = TRUE_LITERAL;
			};

condition		: expression bool_comp expression
				{
					$$ = malloc(sizeof(*$$));
					$$->type = $2;

					$$->left = $1;
					$$->right = $3;
				}
			| condition OR condition{
					$$ = malloc(sizeof(*$$));
					$$->type = BOOL_OR;

					$$->left = $1;
					$$->right = $3;
			}
			| condition AND condition{
				$$ = malloc(sizeof(*$$));
				$$->type = BOOL_AND;

				$$->left = $1;
				$$->right = $3;

			}
			| NOT condition{
				$$ = malloc(sizeof(*$$));
				$$->type = BOOL_NOT;

				$$->left = $2;
				$$->right = NULL;
			}
			;



bool_comp	: LE { $$ = COMP_LE;  }
			| LT { $$ = COMP_LT;  }
			| GT { $$ = COMP_GT;  }
			| GE { $$ = COMP_GE;  }
			| EQ { $$ = COMP_EQ;  }
			| NEQ{ $$ = COMP_NEQ; }
			;


%%


int main()
{
	printf("#include <stdlib.h>\n");

	printf("#include \"runtime/include/variables.h\"\n");

	printf("#include \"runtime/include/prose_arrays.h\"\n");

	printf("#include \"runtime/include/prose_functions.h\"\n");

    printf("int main(void) { \n\n");

    // Start the Parsing (yacc)
    yyparse();

    printf("}\n");

    return 0;
}


int yywrap()
{
        return 1;
}
