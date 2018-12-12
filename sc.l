%{
#include <math.h>

#include "analys.h"
%}
%option noyywrap
IDF	[A-Za-z][A-Za-z0-9|_]*
INST	 [;]
%%




{INST}			{return INST;}

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
"true"			{return TRUE;}
"false"			{return FALSE;}
"for"			{return LOOPFOR;}
"in"			{return IN;}
".."			{return BETWEEN;}
"loop"			{return LOOP;}
"Put_Line"		{return PUTLINE;}
":"			{return GTYPE;}
":="			{return AFFECTATION;}
"("			{return POPEN;}
")"			{return PCLOSED;}

[-+]?[0-9]*+\.[0-9]*	{return DNUMBER;}

[-+]?[0-9]+		{return INUMBER;}
{IDF}			{return IDF;}


%%