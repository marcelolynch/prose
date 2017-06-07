
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
 
  Block * block;

  ProgramRoot * pgm;
  Statements * statements;
}


%token <strval> IDENTIFIER;
%token <strval> STR;
%token <intval> NUM;
%token <floatval> FLOAT;
%token PRINT;

%type <assignment> asig;
%type <pgm> entry;
%type <statements> program;
%type <printnode> print;
%type <block> block;

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
		;



asig : IDENTIFIER '=' STR 
		{
			$$ = malloc(sizeof(*$$));
			
			$$->var_id = getId($1);
			$$->type = STR_T;

			char * str = malloc(strlen($3) + 1);

			strcpy(str, $3);

			free($3);
			
			char* *value = malloc(sizeof(char*));

			memcpy(value, &str, sizeof(char*));
			$$->value = value;
		}

	 | IDENTIFIER '=' NUM
	 	{	
	 		$$ = malloc(sizeof(*$$));


			$$->var_id = getId($1);
			$$->type = INT_T;

			int * value = malloc(sizeof(int));

			memcpy(value, &$3, sizeof(int*));
			$$->value = value;
	 	}

	 | IDENTIFIER '=' FLOAT
	 	{
	 		$$ = malloc(sizeof(*$$));
	 		
			
			$$->var_id = getId($1);
			$$->type = FLOAT_T;

			float * value = malloc(sizeof(float));

			memcpy(value, &$3, sizeof(float*));
			$$->value = value;

	 	}
	 | IDENTIFIER '=' IDENTIFIER '+' IDENTIFIER
	 	{

	 	}
	 ;


print : PRINT IDENTIFIER
		{
			$$ = malloc(sizeof(*$$));
			$$->var_id = getId($2);
		}
	  ;

%%


void main()
{

	printf("#include \"variable_manager.h\"\n");
	printf("#include \"prose_functions.h\"\n");
	printf("float floatHolder;\n");
	printf("int intHolder;\n");
    printf("void main(void) { \n\n");
    // Start the Parsing (yacc
      yyparse();
    printf("}");
} 


int yywrap()
{
        return 1;
} 
