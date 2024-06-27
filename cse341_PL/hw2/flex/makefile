all: flex gcc run 

flex:

	@flex -o gpp_lexer.c gpp_lexer.l
	
gcc: 

	@gcc gpp_lexer.c -o ./lexer -lfl

run:
	@./lexer
	

