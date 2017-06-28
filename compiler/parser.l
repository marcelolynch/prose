%{
	#include "include/ast.h"
    #include "y.tab.h"
    #include <string.h>
    #include <stdlib.h>

%}

alpha [A-Za-z]
digit [0-9]

%%

[\t \n]
mostrar           		return PRINT;

anexar(le)?				return ANEXAR;
a						return A;
mayusculas?				return MAYUSCULA;
minusculas?				return MINUSCULA;
decrementar 			return DECREMENTAR;
incrementar 			return INCREMENTAR;
pasar					return PASAR;


que						return QUE;
valga\ 					return VALGA;
sea\ 					return VALGA;

mientras\ que			return WHILE;
mientras\ que\ no 		return UNTIL;
hasta\ que\ (pase)? 	return UNTIL;


suponga\ que			return IF;
si\ pasa(\ que)?		return IF;

en\ cambio\ si  		return ELSEIF;

si\ no:?				return ELSE;
de\ otro\ modo:?		return ELSE;
en\ otro\ caso:?		return ELSE;


entonces:?  			return DO;
hacer:?					return DO;

listo.?					return END;
y\ repetir.?			return WEND;

y\ ademas				return AND;
o\ bien					return OR;

no						return NOT;

no\ es 					return NEQ;
es 						return EQ;
vale 					return EQ;

es\ menor\ (a|que)		return LT;
es\ menor\ que\ o\ es 	return LE;

es\ mayor\ (a|que)		return GT;
es\ mayor\ que\ o\ es 	return GE;

\"						return SEP;

verdadero				return TRUE;
verdad 					return TRUE;

falso					return FALSE;
mentira					return FALSE;

[\(\)]				{return *yytext;}

{digit}+   			{
						yylval.intval = atoi(yytext);
						return NUM;
					}

{digit}+\.{digit}+  { 	yylval.floatval = atof(yytext);
						return FLOAT;
						}

{alpha}({alpha}|{digit})*  { 
							yylval.strval = malloc(strlen(yytext)+1);
							strcpy(yylval.strval, yytext);
							return IDENTIFIER;
							}

\'[^\'.]+\'			{
					char * str = malloc(strlen(yytext) - 1);
					strncpy(str, yytext + 1, strlen(yytext) - 2);
					yylval.strval = str;
					return STR;
					}

.               {return yytext[0];}

%%