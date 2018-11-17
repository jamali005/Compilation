%{
#include<stdio.h>
%}
%%
[ \t\n]+ printf("sep(%s) ",yytext);
"--"[^\n]*  
procedure printf("proc(%s) ",yytext);
is printf("is(%s) ",yytext);
begin printf(" BEG_IN(%s) ",yytext);
end printf(" END(%s) ",yytext);
Put_Line printf(" putline(%s) ",yytext);
New_Line printf("New_Line'%s) ",yytext);
Put printf("put ");
package printf("package ");
record printf("record ");
out printf("out");
in printf("in");
with printf("with(%s) ",yytext);
use printf("use(%s) ",yytext);
"\""  printf("qout(%s)\n",yytext);
type printf("type");
Character printf("char ");
Integer printf("integer ");
String printf("chaine ");
Boolean printf("boolean ");
Float printf("float ");
Natural printf(" natural ");
Positive printf(" positive ");
subtype printf(" subtype ");
new printf(" new ");
range printf(" range ");
" .. " printf(" to ");
not printf(" not ");
and printf(" and ");
then printf(" then ");
or printf(" or ");
else printf(" else ");
if printf(" if ");
elsif printf(" elsif ");
case printf(" case ");
when printf(" when ");
others printf(" others ");
xor printf(" xor ");
[-+]?[0-9]+ printf("INUMBER(%s) ",yytext);
[-+]?[0-9]+\.?[0-9]* printf("DNUMBER(%s) ",yytext);
"/=" printf(" DIFF ");
":=" printf("aff ");
"=" printf(" EQ ");
"<" printf(" INF ");
">" printf(" SUP ");
, printf("VIRG ");
"+" printf("PLUS ");
"-" printf("MINUS ");
"**" printf(" exp ");
"*" printf("MULT ");
"/"  printf("DIV ");
mod printf(" mod ");
rem printf(" DIVE ");
abs printf(" abs ");
digits printf(" digits ");
delta printf(" delta ");
":" printf(" dbpoint");
declare printf(" declare ");
exception printf(" exception ");
loop printf(" loop ");
exit printf(" exit ");
while printf(" while ");
for printf( " for ");
";" printf(" PVIRG ");
"(" printf(" POPEN ");
")" printf(" PCLOSE ");
[_a-zA-Z][_a-zA-Z0-9]*  printf(" IDF(%s) ",yytext);
.	printf("ERR_LEX( %s )\n", yytext);
%%