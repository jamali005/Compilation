%{

#include "analys.h"
%}
%%

[ \t\n]+
"package"		{return PACKAGE;}
"--"			{return COMMENTARY;}
"with"			{return WITH;}
"use"			{return USE;}
"procedure"		{return PROCEDURE;}
"is"			{return IS;}
"begin"			{return BEG_IN;}
"end"			{return END;}
"integer"		{return INTEGER;}
"string"		{return STRING;}
"float"			{return FLOAT;}
"character"		{return CHAR;}
"boolean"		{return BOOL;}
"natural"		{return NATURAL;}
"positive"		{return POSITIVE;}
"constant"		{printf("const");return CONSTANT;}
"true"			{return TRUE;}
"false"			{return FALSE;}
"="				{return EGAL;}
":="			{printf("aff");return AFFECTATION;}
":"			{return GTYPE;}
";"			{printf("pvirg");return PVIRG;}
"("			{printf("popp");return POPEN;}
")"			{printf("pclose");return PCLOSE;}
","			{return VIRG;}
"if"			{printf("IF\t");return IF;}
"else"			{printf("ELSE\n");return ELSE;}
"then"			{printf("THEN\n");return THEN;}
[-+]?[0-9]*+\.[0-9]*	{return DNUMBER;}

[-+]?[0-9]+		{printf("dnum");return INUMBER;}
[A-Za-z][A-Za-z0-9|_]*	{printf("IDF\t");return IDF;}
.			{return ERRL;}
%%
