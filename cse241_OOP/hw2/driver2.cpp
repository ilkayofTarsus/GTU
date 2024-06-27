#include<iostream>
#include "Tetromino.h"
#include "Tetromino.cpp"
#include "Tetris.cpp"
#include "Tetris.h"
#include<vector>

int main(){

srand(time(NULL));

int row = 0, column = 0,sayac=0;

int tetro_n=0, kaydirma=0, kay=0;

char pre_shape;

cout << endl << endl << endl << " Give the size of Tetris board (row )"<< endl;

cin >> row;

column = row;

Tetris board1(row,column);

board1.print_board();

do{
	
	
	cout << " Enter the tetromino types " << endl;

	cin >> pre_shape;
	
	board1.move(pre_shape);								// tetrominoyu tahtaya ekler ve gerekl kaydırmaları yapar
	
	board1.animate();								// move fonskıyonu sayesınde aldıgı düzgün tetroları asagı kaydırır
	
	board1.set_index(1);								//bir sonraki tetroya erısmek ıcın ındex arttırılır
	
}while(pre_shape != 'Q');

return 0;
}
