#ifndef _TETRIS_
#define _TETRIS_
#include "Tetris.h"
#include <vector>
#include <iostream>
#include<chrono>
#include <thread>
using namespace std;


Tetris::Tetris(int b,int e){							// constructor

	this->boy = b;
	this->en = e;
	this->harita_x=0;
	this->index=0;
	this->tetro_n=0;
	
	vector <vector <char>> board_y(boy+2,vector<char>(en+2));

	for(int i=0; i<b+2; i++){

		for(int j =0; j<e+2; j++){
		
			if(i==0) {
			
				board_y[i][j] = '&' ;
				
				
				}		
			
			else if(j==0 || j== b+1) board_y[i][j] ='&' ;
			
			else if(i == e+1) board_y[i][j] = '&';
			
			else board_y[i][j] = ' ';
		
		}
	
	
	
	}
	
	
board = board_y;
board_y.clear();
}

void Tetris::set_index(int sayi){

	index += sayi;

}


void Tetris::add_tetro(char pre_shape){								
	
	char a;
	bool kontrol = true;
	if(pre_shape == 'R'){
	
	do{

		
		a = 'A' + rand()%26;
		
		if(a == 'I' || a == 'J' || a == 'Z' || a == 'S'|| a == 'L'|| a == 'T'|| a == 'O'){
		
			pre_shape = a;
		
			kontrol = false;
		
		} 
	
	}while(kontrol);
	
	
	}
			
	if(pre_shape != 'Q') tetros.push_back(static_cast<tetro_shapes>(pre_shape));

	tetro_n++;

}

void Tetris::print_board()const {


	for(int a=0; a<boy+2; a++){
	
		for(int b=0; b<en+2; b++){
		
		cout << board[a][b];
		
		
		}
	
	cout << endl;
	
	}


}

void Tetris::add_tetro_tomap(){

vector<vector<char>> temp;

for(int c = 0; c<tetro_n; c++){

	for(int a=1; a< 5; a++){
		
		for(int b =(en/2); b<(en/2 + 4) ; b++){
		
			temp =tetros[c].get_vector();
		
			board[a][b] = temp[a-1][b-(en/2)];  

			
		
		}
	}

}

temp.clear();

}

void Tetris::kaydir_asagi(){

	bool kontrol = true;
	char temp;

		for(int a=1; a < en+1; a++ ){
		
			for(int b=1; b < boy+1; b++){
				
				temp = 'x';		
					
				if(board[b][a] == tetros[index].get_symbol()){
				
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

void Tetris::kaydir_saga(){

	bool kontrol = true;
	char temp;


		for(int b=1; b < 5; b++){
		
			for(int a=1; a < en; a++ ){
				
				temp = 'x';		
					
				if(board_yedek[b][a] == tetros[index].get_symbol()){ // burası ve asgısı
				
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
	

}

void Tetris::kaydir_sola(){

	bool kontrol = true;
	char temp;

		for(int b=1; b < boy; b++){
		
			for(int a=en; a > 0 ; a-- ){
				
				temp = 'x';		
				
				
				if(board_yedek[b][a] == tetros[index].get_symbol()){ // burası ve asagısı
				
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
	

}

int Tetris::kaydirma_s(vector<vector<char>> vekt)const{

int kaydirma=99, kaydirma_y =0, kaydirma_y1 =0;

		for(int b = 1 ; b < boy+2 ; b++){
		
			for(int a = 1; a < en+2; a++){
				
				if(vekt[a][b] == tetros[index].get_symbol()){ // burası ve asasgısı
					
					kaydirma_y=0;
					kaydirma_y1 =0;	
					for(int c = a; c < boy+1; c++){
					
						if(vekt[c][b] == ' '){
						
						kaydirma_y++;
						
						}
						
						if(vekt[c][b+1] == ' ') kaydirma_y1++;
					}	
				
				if(kaydirma_y1 < kaydirma_y) kaydirma_y = kaydirma_y1; 
				if((kaydirma_y != 0) && (kaydirma_y < kaydirma)) kaydirma = kaydirma_y;
				
				}
			
			
			}
		
		}

		
		return kaydirma;

}

void Tetris::fit(){

	int sola_b=0;
	int saga_b=0;
	int kay , dondu = 0;
	bool amp_kontrol= false;
	calc_haritax();
	int d_kontrol = 0;
	
	
	if(harita_x < en/2){
		
		do{	
			d_kontrol++;
			board_yedek = board;

			if(harita_x == 0) sola_b= en/2 - harita_x - 1;	
			
			if(harita_x != 0) sola_b= en/2 - harita_x ;

			for(int a=0 ; a < sola_b; a++ ) kaydir_sola();
		
			kay = kaydirma_s(board_yedek);
		
			for(int a = 1; a < 5; a++){
			
				for(int b = 1; b < en; b++){
				
				
					if(board_yedek[a][b] == tetros[index].get_symbol()){
						
							if(board_yedek[a+kay+1][b+1] == '&'){
		
								amp_kontrol = true;				
							
							break;
							}
					
					}		
						
				if(amp_kontrol) break;						
				
				}		
					
				if(amp_kontrol) break;
			}
			
			if(amp_kontrol == false && dondu != 4 ){
			
				tetros[index].rotate_l();
				
				add_tetro_tomap();
				
				dondu++;
				
			}
			
		}while(!amp_kontrol && d_kontrol!=5);
	
		if(d_kontrol == 5) {
		
		
		
		kaydir_saga();
		
		}
	
	
		board = board_yedek;	
	}
		

	else if(harita_x >= en/2 && harita_x < en){
	
		
		do{	
			d_kontrol++;
			
			board_yedek = board;

			saga_b= harita_x - en/2 ;

			for(int a=0 ; a < saga_b; a++ ) kaydir_saga();
		
			kay = kaydirma_s(board_yedek);

			for(int a = 1; a < 5; a++){
			
				for(int b = 1; b < en; b++){
				
				
					if(board_yedek[a][b] == tetros[index].get_symbol()){
						
							if(board_yedek[a+kay+1][b+1] == '&' && board_yedek[a+kay+1][b+1] != ' '){
		
								amp_kontrol = true;				
							
							break;
							}
					
					}		
						
				if(amp_kontrol) break;						
				
				}		
					
				if(amp_kontrol) break;
			}
			
			if(amp_kontrol == false && dondu != 4 ){
			
				tetros[index].rotate_l();
				
				add_tetro_tomap();
				
				dondu++;
				
			}
			
		}while(!amp_kontrol && d_kontrol!=5);
	
		if(d_kontrol == 5) {
		
		
		
		kaydir_saga();
		
		}
	
	
		board = board_yedek;
		
	}
	
	
	else{
	
	cout << " sınır asıldı " << endl;
	
	
	}

}

int Tetris::calc_haritax(){

	int x=0, x2=0 ;
	
	for(int b =0; b<en; b++){
		
		if(board[boy][en-b] != ' ') {
		
		x = en-b;
		
		break;		
		 
		}
	}
	
	for(int b=0; b<en; b++){	 
		if(board[boy-1][en-b] != ' ') {
		
		x2 = en-b;
		
		break;		
		 
		}

	}
	
	if(x2>x) x=x2;

	harita_x =  x;
	
	return harita_x;

}

void Tetris::animate(){

int kay = kaydirma_s(board);
	
	 for(int a = 0; a < kay; a++){
		
		sleep_for(std::chrono::milliseconds(220));
		
	 	kaydir_asagi();	

		cout << "\x1B[2J\x1B[H";

		print_board();

	}

}

char Tetris::move(char pre_shape){
	
	if (pre_shape == 'Q') exit(0);

	add_tetro(pre_shape);
	
	add_tetro_tomap();

	cout << "\x1B[2J\x1B[H";
	
	print_board();
	
	fit();
	
	return pre_shape;

}

#endif
