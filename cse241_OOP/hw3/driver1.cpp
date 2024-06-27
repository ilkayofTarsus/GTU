#include<iostream>
#include "Tetromino.h"
#include "Tetris.h"

using namespace std;
using namespace Tetromino1;
using namespace Tetris1;

int main(){



srand(time(NULL));

int row = 0, column = 0,sayac=0;
int tetro_n=0, kaydirma=0, kay=0, donus_s=0;
char pre_shape , donus;
bool kontrol = true;

cout << endl << endl << endl << " Give the size of Tetris board (row )"<< endl;
cin >> row;

column = row;
Tetris board1(row,column);
board1.print_board();

do{
	
	cout << "give the tetromino type" << endl;

	do{
	cin >> pre_shape;
	
	if(pre_shape == 'R'){
	
		do{
			pre_shape = 'A' + rand()%26;
			
			if(pre_shape == 'I' || pre_shape == 'J' || pre_shape == 'Z' || pre_shape == 'S'|| pre_shape == 'L'|| pre_shape == 'T'|| pre_shape == 'O'){
				kontrol = false;
				break;
			
			} 
		}while(kontrol);
	
	
	}

	if(!board1.isLegal(pre_shape)) cerr << "Give the legal tetromno type" << endl;
	
	}while(!board1.isLegal(pre_shape));
	
	if(pre_shape == 'Q') break;	
	
	Tetromino obje(static_cast <tetro_shapes> (pre_shape));
	
	board1 += obje;
	board1.print_board();


	cout << "which direction do you want tetromino rotate (l or r)" << endl;
	cin >> donus;

	cout << "how many time do you want to rotate" << endl;
	cin >> donus_s;

	if(donus == 'l')
		for(int a = 0; a<donus_s; a++)
			obje.rotate_l();

	if(donus == 'r') 
		for(int a = 0; a<donus_s; a++)
			obje.rotate_r();
		
		
	board1 += obje;
	board1.print_board();

	cout << "which side do you want tetromino to slide" << endl;
	cin >> donus ;

	cout << "how many times should tetromino slide" << endl
	     << "!! it must be " << row/2 -1 << " mostly" << endl;
	cin >> donus_s;

	switch(donus){
	
		case 'l':
		
		for(int a=0; a<donus_s; a++) board1.kaydir_sola(obje);
		
		
		break;
	
	
		case 'r':
		
		for(int a=0; a<donus_s; a++) board1.kaydir_saga(obje);
		
		break;
	
	}

	board1.animate(obje);
	
	
	if(board1.sil()) board1.print_board();	
	

}while(!board1.is_finished());

sleep_for(std::chrono::milliseconds(500));


return 0;
}
