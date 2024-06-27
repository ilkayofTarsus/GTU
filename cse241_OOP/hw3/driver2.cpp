#include<iostream>
#include "Tetromino.h"
#include "Tetris.h"
using namespace std;
using namespace Tetromino1;
using namespace Tetris1;


int main()
{

srand(time(NULL));

sleep_for(std::chrono::milliseconds(700));


int row = 0, column = 0,sayac=0;
int tetro_n=0, kaydirma=0, kay=0, donus_s=0;
char pre_shape , donus;

cout << endl << endl << endl << " size of Tetris board is 20X20"<< endl;
row = 20;

column = row;
Tetris board1(row,column);
board1.print_board();


	cout << "First tetromino is L" << endl;
	pre_shape = 'L';
	
	cout << " It is added with operator +=..." << endl;
	
	sleep_for(std::chrono::milliseconds(400));
	
	Tetromino obje(static_cast <tetro_shapes> (pre_shape));
	board1 += obje;
	board1.print_board();

	donus = 'l';
	donus_s = 2;

	if(donus == 'l')
		for(int a = 0; a<donus_s; a++)
			obje.rotate_l();

	if(donus == 'r') 
		for(int a = 0; a<donus_s; a++)
			obje.rotate_r();
	

	board1 += obje;
	board1.print_board();
	
	cout << "The turn direction is left and it turned two times... "<< endl;

	sleep_for(std::chrono::milliseconds(500));

	donus = 'l' ;
	donus_s = 9;
	cout << "it will go to left side 9 times" << endl;
	sleep_for(std::chrono::milliseconds(500));


	switch(donus){
	
		case 'l':
		
		for(int a=0; a<donus_s; a++) board1.kaydir_sola(obje);
		
		
		break;
	
	
		case 'r':
		
		for(int a=0; a<donus_s; a++) board1.kaydir_saga(obje);
		
		break;
	
	}
	
	sleep_for(std::chrono::milliseconds(500));

	board1.animate(obje);
	
	if(board1.sil()) board1.print_board();	
	
	cout << "Additional test.." << endl;
	pre_shape = 'T';
	
	Tetromino obje1(static_cast <tetro_shapes> (pre_shape));
	board1 += obje1;
	board1.print_board();

	donus = 'l';
	donus_s = 2;

	if(donus == 'l')
		for(int a = 0; a<donus_s; a++)
			obje1.rotate_l();

	if(donus == 'r') 
		for(int a = 0; a<donus_s; a++)
			obje1.rotate_r();
	

	board1 += obje1;
	board1.print_board();

	sleep_for(std::chrono::milliseconds(250));

	donus = 'r' ;
	donus_s = 7;
	sleep_for(std::chrono::milliseconds(250));


	switch(donus){
	
		case 'l':
		
		for(int a=0; a<donus_s; a++) board1.kaydir_sola(obje1);
		
		
		break;
	
	
		case 'r':
		
		for(int a=0; a<donus_s; a++) board1.kaydir_saga(obje1);
		
		break;
	
	}
	
	sleep_for(std::chrono::milliseconds(250));

	board1.animate(obje1);
	

	

return 0;
}
