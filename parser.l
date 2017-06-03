%{
    #include "y.tab.h"
    #include <string.h>
    #include <stdlib.h>

%}

alpha [A-Za-z]
digit [0-9]

%%

[\t \n] 
print           	return PRINT;

{digit}+   			{
						yylval.intval = atoi(yytext);
						return NUM;
					}	

{digit}+\.{digit}+  { 	yylval.floatval = atof(yytext);
						return FLOAT; }


{alpha}({alpha}|{digit})* { yylval.strval = malloc(strlen(yytext)+1);
							strcpy(yylval.strval, yytext);
							return IDENTIFIER;
						}

\".+\"			{
					char * str = malloc(strlen(yytext) - 1);
					strncpy(str, yytext + 1, strlen(yytext) - 2);
					yylval.strval = str;
					return STR; 
				}

.               {return yytext[0];}

%%