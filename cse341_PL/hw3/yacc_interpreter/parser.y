%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gpp.h"

#define OUT_FILE "output.txt"

extern FILE * yyin;     
extern FILE * yyout;    
extern int yyparse();   
extern char * yytext;   
extern int line_no;     
char expString[333];
int yylex();

int yyerror(char* str) { 
    printf("syntax_error\n");
    return 0; 
}
int exit_bool = 0;

%}

%union {
    Valuef valuef;
    int valueb;
    char* str;
}

%start START

%token  OP_PLUS
%token  OP_MINUS
%token  OP_DIV
%token  OP_MULT				
%token <str> KW_IF KW_AND KW_OR KW_NOT KW_EQUAL KW_LESS KW_NILL KW_LIST KW_APPEND KW_CONCAT KW_SET KW_DEF KW_FOR KW_EXIT KW_LOAD KW_DISPLAY KW_TRUE KW_FALSE OP_OP OP_CP OP_COMMA COMMENT  IDENTIFIER 

%token <valuef> VALUEF
%type  <valuef> FUNCTION
//%type <valuef> INPUT
%type <valuef> EXP

%%


START   : START EXP 						{printf(" Expression Result: %d/%d\n", $2.first, $2.second);}
	| START FUNCTION 					{;}
	| START OP_OP KW_EXIT OP_CP				{printf("exiting"); exit(1);}
	| EXP							{printf(" Expression Result: %d/%d\n", $1.first, $1.second);}
	| FUNCTION 						{;}
	| OP_OP KW_EXIT OP_CP					{printf("exiting..."); exit(1);}
	;

EXP     : OP_OP OP_PLUS EXP EXP OP_CP                   { /*strcat(expString,$1);strcat(expString,$2);strcat(expString,$3);strcat(expString,$4);strcat(expString,$5);*/$$ = addV($3, $4); }
        | OP_OP OP_MINUS EXP EXP OP_CP                  { $$ = subV($3, $4); }
        | OP_OP OP_MULT EXP EXP OP_CP                   { $$ = multV($3, $4); }
        | OP_OP OP_DIV EXP EXP OP_CP                    { $$ = divV($3, $4); }
       	| OP_OP IDENTIFIER EXP OP_CP 			{ $$ = $3; }
	| OP_OP IDENTIFIER EXP EXP OP_CP		{ $$ = $3; }
	| OP_OP IDENTIFIER EXP EXP EXP OP_CP		{ $$ = $3; }
        | VALUEF                                        { $$ = $1; }
        | IDENTIFIER					{ /*strcat(expString,$1);*/$$ = tempValuefCreator(1,1);}
		
        ;
        
FUNCTION: OP_OP KW_DEF IDENTIFIER EXP OP_CP  				{printf("function created 1");}
	| OP_OP KW_DEF IDENTIFIER IDENTIFIER EXP OP_CP	 		{printf("function created 2");}	
	| OP_OP KW_DEF IDENTIFIER IDENTIFIER IDENTIFIER EXP OP_CP	{printf("function created 3");}
        ;



%%

int main(int argc, char * argv[]) {
	FILE *input_file;

	if (argc == 2) {
		input_file = fopen(argv[1], "r");
		if (input_file == NULL) {
		    perror("Dosya açma hatası");
		    return 1;
		}
	} 
	else{
		input_file = stdin;
	}
	yyin = input_file;
	yyparse();
	if (input_file != stdin) {
		fclose(input_file);
	}
	return 0;
}

