#ifndef _TETRIS_
#define _TETRIS_
#include "Tetris.h"
#include <iostream>
#include<chrono>
#include <thread>
using namespace std;



namespace Tetris1{


Tetris::Tetris(int b,int e){							// constructor

	boy = b;
	en = e;
	harita_x=0;
	index=0;
	tetro_n=0;
	
	board = new char*[boy+2];

	for(int i = 0; i < boy+2; i++){
		
		board[i] = new char[en+2];
		
	
	}

	
		board_yedek = new char*[boy+2];

		for(int i = 0; i < boy+2; i++){
			
			board_yedek[i] = new char[en+2];
			
		
		}
		

	for(int i=0; i<b+2; i++){

		for(int j =0; j<e+2; j++){
		
			if(i==0) {
			
				board[i][j] = '&' ;
				
				
				}		
			
			else if(j==0 || j== b+1) board[i][j] ='&' ;
			
			else if(i == e+1) board[i][j] = '&';
			
			else board[i][j] = ' ';
		
		}
	
	
	
	}
	
}

Tetris::Tetris(const Tetris& other){					// copy constructor

	this->boy = other.boy;
	this->en = other.en;
	this->harita_x=0;
	this->index=0;
	this->tetro_n=0;
	
	board = new char*[boy+2];

	for(int i = 0; i < boy+2; i++){
		
		board[i] = new char[en+2];
		
	
	}
	
	for(int a=0; a<boy+2 ; a++){
	
		for(int b=0; a<en+2 ; b++){
	
		board[a][b] = other.get_board()[a][b];
	
		}
	
	}


}


Tetris::~Tetris(){						// destructor 
	
	
	if(board != nullptr){
		for(int a=0; a< boy+2; a++)
			if(board[a] != nullptr) delete [] board[a];

		delete [] board ;
	}
	
	if(board_yedek != nullptr){
		for(int a=0; a< boy+2; a++)
			if(board_yedek != nullptr) delete [] board_yedek[a];

		delete [] board_yedek;
	}
	

	/*
	for(int a=0; a< boy+2; a++){
			
		if(board != nullptr) delete [] board[a];

		if(board != nullptr) delete [] board_yedek[a];
	}
	
if(board != nullptr) delete [] board_yedek;
if(board != nullptr) delete [] board;
*/
}

void Tetris::operator +=(const Tetromino& other){

add_tetro_tomap(other);

//return *this;

}
Tetris Tetris::operator =(const Tetris& other){

	this->boy = other.boy;
	this->en = other.en;
	this->harita_x=other.harita_x;
	this->index=other.index;
	this->tetro_n=other.tetro_n;
	
	delete [] board;
	delete board;
	
	board = new char*[boy+2];

	for(int i = 0; i < boy+2; i++){
		
		board[i] = new char[en+2];
		
	
	}
	
	for(int a=0; a<boy+2 ; a++){
	
		for(int b=0; a<en+2 ; b++){
	
		board[a][b] = other.get_board()[a][b];
	
		}
	
	}

return *this;

}


void Tetris::set_index(int sayi){

	index += sayi;

}

void Tetris::print_board()const {


	for(int a=0; a<boy+2; a++){
	
		for(int b=0; b<en+2; b++){
		
		cout << board[a][b];
		
		
		}
	
	cout << endl;
	
	}


}

void Tetris::add_tetro_tomap(const Tetromino& tetrs){


for(int a=1; a< 5; a++){
		
		for(int b =(en/2); b<(en/2 + 4) ; b++){
		
			board[a][b] = ' '; 
		
		}
	}



	for(int a=1; a< 5; a++){
		
		for(int b = (en/2); b < (en/2 + 4) ; b++){
		
			board[a][b] =  tetrs.get_vectorc( a-1 , b-(en/2) ); 
		
		}
	}


}

void Tetris::kaydir_asagi(const Tetromino& obje)const{

	bool kontrol = true;
	char temp;
	
		for(int a=1; a < en+1; a++ ){
		
			for(int b=1; b < boy+1; b++){
				
				temp = 'x';		
					
				if(board[b][a] == obje.get_symbol()){
				
					for(int c=b+1; c<boy+1; c++){
						
						if(board[c][a] == ' '){
							
								temp = board[c][a];
								board[c][a] = board[b][a];		
								board[b][a] = temp;
								temp = ' ';
						
						}
					
					
					}	
					
				
				}
			
				
				if(temp == ' ') break;
			
			}
		
		
		}
	

}

void Tetris::kaydir_saga(const Tetromino& obje){

	bool kontrol = true;
	char temp;
		
		for(int a = 0; a<boy+2 ;a++){
		
			for(int b=0; b<en+2; b++){
			
			board_yedek[a][b] = board[a][b]; 
			
			
			}
		
		
		}
		
		

		for(int b=1; b < 5; b++){
		
			for(int a=1; a < en; a++ ){
				
				temp = 'x';		
					
				if(board_yedek[b][a] == obje.get_symbol()){ // burası ve asgısı
				
					for(int c=a; c<en+1; c++){
					
						if(board_yedek[b][c] == ' ' ){
							
							temp = board_yedek[b][c];
							board_yedek[b][c] = board_yedek[b][a];		
							board_yedek[b][a] = temp;
							temp = ' ';
						
						}
					
					
					}	
					
				
				}
			
				
				if(temp == ' ') break;
			
			}
		
		
		}
		
		for(int a = 0; a<boy+2 ;a++){
		
			for(int b=0; b<en+2; b++){
			
			board[a][b] = board_yedek[a][b]; 
			
			
			}
		
		
		}
	

}

void Tetris::kaydir_sola(const Tetromino& obje){

	bool kontrol = true;
	char temp;
		
		for(int a = 0; a<boy+2 ;a++){
		
			for(int b=0; b<en+2; b++){
			
			board_yedek[a][b] = board[a][b]; 
			
			
			}
		
		
		}
		
		for(int b=1; b < boy; b++){
		
			for(int a=en; a > 0 ; a-- ){
				
				temp = 'x';		
				
				if(board_yedek[b][a] == obje.get_symbol()){ // burası ve asagısı
				
					for(int c=a; c>0; c--){
						
						if(board_yedek[b][c] == ' ' ){
							
							temp = board_yedek[b][c];
							board_yedek[b][c] = board_yedek[b][a];		
							board_yedek[b][a] = temp;
							temp = ' ';
						
						}
					
					
					}	
					
				
				}
			
				
				if(temp == ' ') break;
			
			}
		
		
		}
		
		for(int a = 0; a<boy+2 ;a++){
		
			for(int b=0; b<en+2; b++){
			
			board[a][b] = board_yedek[a][b]; 
			
			
			}
		
		
		}
	

}

int Tetris::kaydirma_s(const Tetromino& obje)const{

int kaydirma=99, kaydirma_y =0, kaydirma_y1 =0,kaydirma_y2 =0;

		for(int b = 1 ; b < boy+1 ; b++){
		
			for(int a = 1; a < 5; a++){
				
				if(board[a][b] == obje.get_symbol()){ // burası ve asasgısı
					
					kaydirma_y=0;
					kaydirma_y1 =0;
					kaydirma_y2 =0;	
					for(int c = a; c < boy+1; c++){
					
						if(board[c][b] == ' '){
						
						kaydirma_y++;
						
						}
						

						if(board[c][b+1] == ' ') kaydirma_y1++;
						
						
						if(board[c][b+1] != '&'){
						 	
						 	if( board[c][b+2] == ' ') kaydirma_y2++;
						
						}
					}	
				if(kaydirma_y2 < kaydirma_y1) kaydirma_y1 = kaydirma_y2; 
				if(kaydirma_y1 < kaydirma_y) kaydirma_y = kaydirma_y1; 
				if((kaydirma_y != 0) && (kaydirma_y < kaydirma)) kaydirma = kaydirma_y;
				
				}
			
			
			}
		
		}

		
		return kaydirma;

}
void Tetris::animate( Tetromino& obje)const{
int kay = kaydirma_s(obje);
		
	 for(int a = 0; a < kay; a++){
		
		sleep_for(std::chrono::milliseconds(220));
		
	 	kaydir_asagi(obje);	

		cout << "\x1B[2J\x1B[H";

		print_board();

	}

}

bool Tetris::sil(){

	bool silme = true, ret = false;

	do{

		for(int a=1; a< en+1 ; a++){
		
			if(board[boy][a] == ' ') silme = false;
		
		
		}

		if(silme){
			
			ret = true;
			cout << "\x1B[2J\x1B[H";
			
			for(int a=boy; a >2; a--){
			
				for(int b=1; b<en+1; b++ ){
				
				board[a][b] = board[a-1][b];
				
				
				}
			
			
			}
		
		for(int b=1; b<en+1; b++ ) board[1][b] = ' ';
		
		}
	}while(silme);
return ret;

}

bool Tetris::isLegal(char pre_shape){


return (pre_shape == 'T' || pre_shape == 'I' || pre_shape == 'O' || pre_shape == 'Z'|| pre_shape == 'S'|| pre_shape == 'J'|| pre_shape == 'L' || pre_shape == 'Q');

}

bool Tetris::is_finished(){

bool finished = false;

	for(int a = 1; a < 5; a++ ){
	
		for(int b = 1; b < en + 1 ; b++){
		
					
		if( board[a][b] != ' ') finished = true;		
		
		
		}
	
	}

return finished;

}

}						// end of namespace

#endif
