
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ast.h"

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

	identifiers[i] = malloc(strlen(strId));
	strcpy(identifiers[i], strId);

	return i;

}

%}


%union {
  int intval;
  char * strval;
  float floatval;

  AssignmentNode * assignment;
  PrintNode * printnode;
  WhileNode * whilenode; 
  BoolNode * boolnode;
  ArithNode * arithnode;

  Block * block;

  
  Statements * statements;

  bool_operation boolop;
}


%token <strval> IDENTIFIER;
%token <strval> STR;
%token <intval> NUM;
%token <floatval> FLOAT;
%token PRINT;

%token VALE;

%token SEP;

%token WHILE;
%token UNTIL;

%token DO;
%token END;

%token AND;
%token OR;
%token NOT;

%token LE;
%token GE;
%token EQ;
%token NEQ;

%token TRUE FALSE;


%left LE GE EQ AND OR NOT '+';


%type <assignment> asig;
%type <statements> program;
%type <printnode> print;
%type <block> block;
%type <whilenode> while;
%type <boolop> bool_comp;
%type <boolnode> condition;
%type <arithnode> arithmetic;

%start entry

%%




entry : program {

		produce($1,"");
	
	  	}



program : 

		block
		   {
		   	$$ = malloc(sizeof(*$$));
			$$->type = $1->type;;
			$$->expressionNode = $1->node;
			$$->next = NULL;
			
			free($1);

			}

		| block program

			{
			$$ = malloc(sizeof(*$$));
		
			$$->type = $1->type;
			$$->expressionNode = $1->node;
			$$->next = $2;
			
			free($1);		
			}

		;


block	: asig{
		
			$$ = malloc(sizeof(*$$));
			$$->type = ASSIGNMENT;
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
		;



asig : IDENTIFIER VALE arithmetic
	 	{	 		
	 		$$ = malloc(sizeof(*$$));
	 		$$->var_id = getId($1);

	 		$$->value = $3;
	 	}
	 ;



arithmetic : STR 
		{
			$$ = malloc(sizeof(*$$));
			
			$$->type = STR_TYPE;

			char * str = malloc(strlen($1) + 1);

			strcpy(str, $1);

			free($1);
			
			$$->left = malloc(sizeof(char*));

			memcpy($$->left, &str, sizeof(char*));
			}

	 | NUM
	 	{	
	 		$$ = malloc(sizeof(*$$));
			$$->type = INT_TYPE;

			$$->left = malloc(sizeof(int));

			memcpy($$->left, &$1, sizeof(int));
		}

	 | FLOAT
	 	{
	 		$$ = malloc(sizeof(*$$));
	 		
			$$->type = FLOAT_TYPE;

			$$->left = malloc(sizeof(float));

			memcpy($$->left, &$1, sizeof(float));

	 	}
	 |	arithmetic '+' arithmetic
			{
				$$ = malloc(sizeof(*$$));
				$$->type = ARIT_SUM;
				$$->left = $1;
				$$->right = $3;
			}


print : PRINT IDENTIFIER
		{
			$$ = malloc(sizeof(*$$));
			$$->var_id = getId($2);
		}
	  ;




while 	: WHILE SEP condition SEP DO program END
			{
				$$ = malloc(sizeof(*$$));
				$$->condition = $3;
				$$->body = $6;
			}
		;

condition		: IDENTIFIER bool_comp NUM
				{
					$$ = malloc(sizeof(*$$));
					$$->type = $2;

					int id = getId($1);
					$$->left = malloc(sizeof(int));
					memcpy($$->left, &id, sizeof(int));

					$$->right = malloc(sizeof(int));
					memcpy($$->right, &$3, sizeof(int));

				}
			| IDENTIFIER bool_comp IDENTIFIER
				{
					$$ = malloc(sizeof(*$$));
					$$->type = $2;

					int id = getId($1);
					$$->left = malloc(sizeof(int));
					memcpy($$->left, &id, sizeof(int));

					id = getId($3);
					$$->right = malloc(sizeof(int));
					memcpy($$->right, &id, sizeof(int));

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
			| GE { $$ = COMP_GE;  } 
			| EQ { $$ = COMP_EQ;  }
			;


%%


void main()
{

	printf("#include \"variable_manager.h\"\n");
	printf("#include \"prose_functions.h\"\n");
	printf("float floatHolder;\n");
	printf("int intHolder;\n");
    printf("void main(void) { \n\n");
    
    // Start the Parsing (yacc)
    yyparse();
    
    printf("}\n");
} 


int yywrap()
{
        return 1;
} 
