
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
}


%token <strval> IDENTIFIER;
%token <strval> STR;
%token <intval> NUM;
%token <floatval> FLOAT;
%token PRINT;


%start program

%%


program : asig
		   {

			
			}
		| asig program

			{

			}

		| print program
			{

			}

		| print {

		}
		;


asig : IDENTIFIER '=' STR 
		{
			printf("assign(%d, \"%s\", STR_T);\n", getId($1), $3);
			free($3);
		}
	 | IDENTIFIER '=' NUM
	 	{	
	 		printf("intHolder = %d;\n", $3);
			printf("assign(%d, &intHolder, INT_T);\n", getId($1));
	 	}
	 | IDENTIFIER '=' FLOAT
	 	{

	 		printf("floatHolder = %f;\n", $3);
			printf("assign(%d, &floatHolder, FLOAT_T);\n", getId($1));
	 	}
	 | IDENTIFIER '=' IDENTIFIER '+' IDENTIFIER
	 	{

	 	}
	 ;


print : PRINT IDENTIFIER
		{
			printf("print_var(%d);\n", getId($2));	
			free($2);		
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
