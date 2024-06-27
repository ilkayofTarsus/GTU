all: compile run cat

compile: dr1.cpp test.cpp Tetrisarray.cpp TetrisVector.cpp Tetrominoa.cpp 

	@g++-11 dr1.cpp Tetrisarray.cpp TetrisVector.cpp Tetrominoa.cpp -o main.out
	@g++-11 test.cpp Tetrisarray.cpp TetrisVector.cpp Tetrominoa.cpp -o test.out
	
run:

	@./main.out
	@./test.out
	
cat:

	@cat text.txt
