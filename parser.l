%{
	#include "ast.h"
    #include "y.tab.h"
    #include <string.h>
    #include <stdlib.h>

%}

alpha [A-Za-z]
digit [0-9]

%%

[\t \n] 			

mostrar           	return PRINT;

vale				return VALE;
mientras\ que		return WHILE;
entonces			return DO;
listo.				return END;

y\ ademas			return AND;
o\ bien				return OR;

no					return NOT;

no\ es 				return NEQ;
es 					return EQ;

\"					return SEP;

{digit}+   			{
						yylval.intval = atoi(yytext);
						return NUM;
					}	

{digit}+\.{digit}+  { 	yylval.floatval = atof(yytext);
						return FLOAT; 
					}

{alpha}({alpha}|{digit})* { yylval.strval = malloc(strlen(yytext)+1);
							strcpy(yylval.strval, yytext);
							return IDENTIFIER;
						}

\'.+\'			{
					char * str = malloc(strlen(yytext) - 1);
					strncpy(str, yytext + 1, strlen(yytext) - 2);
					yylval.strval = str;
					return STR; 
				}

.               {return yytext[0];}

%%