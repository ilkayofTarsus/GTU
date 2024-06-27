all: compile run clean

compile:  driver1.cpp Tetromino.h Tetris.h Tetris.cpp Tetromino.cpp
	@echo "-------------------------------------------"
	@echo "Compiling.."
	@g++ driver1.cpp Tetris.cpp Tetromino.cpp -o main.out
	@g++ driver2.cpp Tetris.cpp Tetromino.cpp -o test.out
run:
	@echo "-------------------------------------------"
	@echo "Running the tests.."
	./test.out
	@echo "============================================================="
	./main.out
	@echo "============================================================="
	@echo "Completed tests.."
	
clean:
	rm test.out
	rm main.out
