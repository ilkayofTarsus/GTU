%{
	#include "gpp.h"
	#include "parser.tab.h"
	int line_no = 1;
%}


%%
	
"if"    	{ yylval.str = strdup(yytext); return KW_IF; }			
"and"    	{ yylval.str = strdup(yytext); return KW_AND; }
"or"    	{ yylval.str = strdup(yytext); return KW_OR; }
"not"   	{ yylval.str = strdup(yytext); return KW_NOT; }
"equal"    	{ yylval.str = strdup(yytext); return KW_EQUAL; }
"less"    	{ yylval.str = strdup(yytext); return KW_LESS; }
"nill"    	{ yylval.str = strdup(yytext); return KW_NILL; }
"list"    	{ yylval.str = strdup(yytext); return KW_LIST; }
"append"    	{ yylval.str = strdup(yytext); return KW_APPEND; }
"concat"   	{ yylval.str = strdup(yytext); return KW_CONCAT; }
"set"    	{ yylval.str = strdup(yytext); return KW_SET; }
"def"    	{ yylval.str = strdup(yytext); return KW_DEF; }
"for"    	{  yylval.str = strdup(yytext); return KW_FOR; }
"exit"    	{ yylval.str = strdup(yytext); return KW_EXIT; }
"load"		{ yylval.str = strdup(yytext); return KW_LOAD; }
"display"	{ yylval.str = strdup(yytext); return KW_DISPLAY; }
"true"		{ yylval.str = strdup(yytext); return KW_TRUE; }
"false"    	{ yylval.str = strdup(yytext); return KW_FALSE; }

[+]    {  yylval.str = strdup(yytext); return OP_PLUS; }
[-]    { yylval.str = strdup(yytext); return OP_MINUS; }
[/]    { yylval.str = strdup(yytext); return OP_DIV; }
[*]    { yylval.str = strdup(yytext); return OP_MULT; }
[(]    { yylval.str = strdup(yytext); return OP_OP; }
[)]    { yylval.str = strdup(yytext); return OP_CP; }
[,]    { yylval.str = strdup(yytext);return OP_COMMA; }
[a-zA-Z][a-zA-Z0-9]* { yylval.str = strdup(yytext); return IDENTIFIER; }
[-]?([1-9][0-9]*|0)b([1-9][0-9]*|0)     { yylval.valuef = valuefConverter(yytext); return VALUEF; }
. 		;

%%

int yywrap() {
    return 1;
}
