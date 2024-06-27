%{
#include <stdio.h>
#include <stdlib.h>
%}

	
IF 	"if"		
AND	"and"
OR	"or"
NOT	"not"
EQUAL	"equal"
LESS	"less"
NILL	"nill"
LIST	"list"
APPEND	"append"
CONCAT	"concat"
SET	"set"
DEF	"def"
FOR	"for"
EXIT	"exit"
LOAD	"load"
DISPLAY	"display"
TRUE	"true"
PLUS	"+"
MINUS	"-"
DIV	"/"
MULT	"*"
OP	"("
CP	")"
COMMA	","
IDENTIFIER [a-zA-Z][a-zA-Z0-9]+
FALSE	"false"


%%
					
{IF}    { printf("KW_IF\n"); }			
{AND}    { printf("KW_AND\n"); }
{OR}    { printf("KW_OR\n"); }
{NOT}    { printf("KW_NOT\n"); }
{EQUAL}    { printf("KW_EQUAL\n"); }
{LESS}    { printf("KW_LESS\n"); }
{NILL}    { printf("KW_NILL\n"); }
{LIST}    { printf("KW_LIST\n"); }
{APPEND}    { printf("KW_APPEND\n"); }
{CONCAT}    { printf("KW_CONCAT\n"); }
{SET}    { printf("KW_SET\n"); }
{DEF}    { printf("KW_DEF\n"); }
{FOR}    { printf("KW_FOR\n"); }
{EXIT}    { printf("KW_EXIT\n"); }
{LOAD}    { printf("KW_LOAD\n"); }
{DISPLAY}    { printf("KW_DISPLAY\n"); }
{TRUE}    { printf("KW_TRUE\n"); }
{FALSE}    { printf("KW_FALSE\n"); }
"+"    { printf("OP_PLUS\n"); }
"-"    { printf("OP_MINUS\n"); }
"/"    { printf("OP_DIV\n"); }
"*"    { printf("OP_MULT\n"); }
"("    { printf("OP_OP\n"); }
")"    { printf("OP_CP\n"); }
","    { printf("OP_COMMA\n"); }
";;".*    { printf("COMMENT\n"); }
[0-9]+  { printf("INTEGER\n"); } 
{IDENTIFIER} { printf("IDENTIFIER\n"); }
[0-9]+[b][0-9]+ { printf("VALUEF\n"); } 
{IDENTIFIER}^[+*-/]{IDENTIFIER} { printf("Syntax Error: %s\n",yytext); exit(1); }
[0-9]{IDENTIFIER} { printf("Syntax Error: %s\n",yytext); exit(1); }
" "     { printf("");  } 	
\n      { printf("");  } 
\\n     { printf("");  } 
\t      { printf("");  } 
.       { printf("Syntax Error: %s \n",yytext); exit(1);}

%%

int main() {
	    int number = yylex();
	    return 0;
}
