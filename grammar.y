
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

%start entry

%%


entry : program {
		$$ = malloc(sizeof(*$$));
			
		$$->body = $1;
		produce($$);
	}


program : asig
		   {
		   	$$ = malloc(sizeof(*$$));
			$$->type = ASSIGNMENT;
			$$->expressionNode = $1;
			$$->next = NULL;		
			}
		| asig program

			{
			$$ = malloc(sizeof(*$$));
		
			$$->type = ASSIGNMENT;
			$$->expressionNode = $1;
			$$->next = $2;		
			}

		| print program
			{
			$$ = malloc(sizeof(*$$));
			
			$$->type = PRINT_CALL;
			$$->expressionNode = $1;
			$$->next = $2;		
			}

		| print {
			$$ = malloc(sizeof(*$$));
			
			$$->type = PRINT_CALL;
			$$->expressionNode = $1;
			$$->next = NULL;		
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
			
			$$->value = &str;
		}

	 | IDENTIFIER '=' NUM
	 	{	
	 		$$ = malloc(sizeof(*$$));
			
			$$->var_id = getId($1);
			$$->type = INT_T;

			int * value = malloc(sizeof(int));

			memcpy(value, &$3, 4);
			$$->value = value;
	 	}

	 | IDENTIFIER '=' FLOAT
	 	{
	 		$$ = malloc(sizeof(*$$));
			
			$$->var_id = getId($1);
			$$->type = FLOAT_T;
			$$->value = &$3;
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
