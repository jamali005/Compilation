%{

#include "analys.h"
#define debug false
static int my_yylineno = 1;
%}
%%

[ \t]+
\n                      {my_yylineno++; set_token_attributes( my_yylineno );}
"package"		{if (debug) printf("package\n");return PACKAGE;}
"--"			{if (debug) printf("--\n");return COMMENTARY;}
"with"			{if (debug) printf("with\n");return WITH;}
"use"			{if (debug) printf("use\n");return USE;}
"procedure"		{if (debug) printf("procedure\n");return PROCEDURE;}
"is"			{if (debug) printf("is\n");return IS;}
"begin"			{if (debug) printf("begin\n");return BEG_IN;}
"end"			{if (debug) printf("end\n");return END;}
"integer"		{if (debug) printf("integer\n");return INTEGER;}
"string"		{if (debug) printf("string\n");return STRING;}
"float"			{if (debug) printf("float\n");return FLOAT;}
"character"		{if (debug) printf("character\n");return CHAR;}
"boolean"		{if (debug) printf("boolean\n");return BOOL;}
"natural"		{if (debug) printf("natural\n");return NATURAL;}
"positive"		{if (debug) printf("positive\n");return POSITIVE;}
"constant"		{if (debug) printf("const\n");return CONSTANT;}
"true"			{if (debug) printf("true \n");return TRUE;}
"false"			{if (debug) printf("false\n");return FALSE;}
":="			{if (debug) printf("aff\n");return AFFECTATION;}
":"			{if (debug) printf(":\n");return GTYPE;}
"="			{if (debug) printf("egal\n");return EGAL;}
";"			{if (debug) printf("pvirg\n");return PVIRG;}
"("			{if (debug) printf("popp\n");return POPEN;}
")"			{if (debug) printf("pclose\n");return PCLOSE;}
"for"			{if (debug) printf("for\n");return LOOPFOR;}
"in"			{if (debug) printf("innnn\n");return IN;}
".."			{if (debug) printf("..\n");return BETWEEN;}
"loop"			{if (debug) printf("loop\n");return LOOP;}
"Put_Line"		{if (debug) printf("put_line\n");return PUTLINE;}
"if"			{if (debug) printf("IF\n");return IF;}
"else"			{if (debug) printf("ELSE\n");return ELSE;}
"then" 			{if (debug) printf("THEN\n");return THEN;}
","			{if (debug) printf("virg\n");return VIRG;}
["]			{if (debug) printf("quot\n");return TIRETS;}
"+"			{if (debug) printf ("+"); return PLUS;}
"-"			{if (debug) printf ("-"); return MINUS;}
"*"			{if (debug) printf ("*"); return MULT;}
"/"			{if (debug) printf ("/"); return DIV;}
[0-9]+[.][0-9]+	{if (debug) printf("reel(%s)\n",yytext);
			set_number_attributes(atof(yytext));
			return DNUMBER;}
[0-9]+		{if (debug) printf("dnum(%s)\n",yytext);
			set_number_attributes((double)atoi(yytext));
			return INUMBER;}
[A-Za-z][A-Za-z0-9|_]*	{if (debug) printf ("IDF(%s)\n",yytext);
			set_idf_attributes(yytext, my_yylineno);
			return IDF;}
\'[a-z0-9A-Z]\'		{printf("CARA(%s) ",yytext); return CARA;}
.			{set_token_attributes(yylineno);return ERRL;}
%%
