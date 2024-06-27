#ifndef _TETROMINO_
#define _TETROMINO_
#include "Tetromino.h"
#include <vector>
#include <iostream>
using namespace std;
	Tetromino::Tetromino(tetro_shapes symbol){
	
		switch(symbol){
		
			case tetro_shapes::i:
			
			set_symbol('I');
			tetro_v = {{'I',' ',' ',' '}, {'I',' ',' ',' '}, {'I',' ',' ',' '}, {'I',' ',' ',' '} };
			
			break;
			
			case tetro_shapes::o:
			
			set_symbol('O');
			tetro_v = {{' ',' ',' ',' '}, {' ',' ',' ',' '}, {'O','O',' ',' '}, {'O','O',' ',' '} };
						
			break;
			
			case tetro_shapes::t:
			
			set_symbol('T');
			tetro_v = {{' ',' ',' ',' '}, {'T',' ',' ',' '}, {'T','T',' ',' '}, {'T',' ',' ',' '} };
			
			break;
			
			case tetro_shapes::j:
			
			set_symbol('J');
			tetro_v = {{' ',' ',' ',' '}, {' ','J',' ',' '}, {' ','J',' ',' '}, {'J','J',' ',' '} };
			
			break;
			
			case tetro_shapes::l:
			
			set_symbol('L');
			tetro_v = {{' ',' ',' ',' '}, {'L',' ',' ',' '}, {'L',' ',' ',' '}, {'L','L',' ',' '} };
			
			break;
			
			case tetro_shapes::s:
			
			set_symbol('S');
			tetro_v = {{' ',' ',' ',' '}, {' ',' ',' ',' '}, {' ','S','S',' '}, {'S','S',' ',' '} };
			
			break;
			
			case tetro_shapes::z:
			
			set_symbol('Z');
			tetro_v = {{' ',' ',' ',' '}, {' ',' ',' ',' '}, {'Z','Z',' ',' '}, {' ','Z','Z',' '} };
			
			break;
		
		
		}	
	
	}
	void Tetromino::print_s(vector<vector<char>> v,int inc)const{
	
		for(int a=0 ;a<4 ;a++){
			
					
			for(int b =0 ;b<4+inc ;b++){
	
			
				cout <<v[a][b] ;
			
			}
				
			cout<< "\n";	
		
		}
	
	
	
	}
	char Tetromino::get_symbol() const{ return symbol; }
	void Tetromino::set_symbol(char a){
		
		symbol = a;
	
	}
	void Tetromino::rotate_r(){
	
		tetro_yedek = tetro_v;
 		bosluk_doldur();
 			
 				for(int a=0; a<4; a++) {
						
					for(int b=0; b<4; b++){
								
							tetro_v[b][a] = tetro_yedek[3-a][b];
					}
				}
 			asagi_kaydir();
 			sola_kaydir();
 			
	}
	void Tetromino::rotate_l(){
	
		tetro_yedek = tetro_v;
 		bosluk_doldur();
 			
 			
 				for(int a=0; a<4; a++) {
						
					for(int b=0; b<4; b++){
							
							tetro_v[b][a] = tetro_yedek[a][3-b];
					}
				}
 			asagi_kaydir();
 			sola_kaydir();
	
	}
	
	void Tetromino::bosluk_doldur(){
	
		for(int a=0;a<4;a++){
			
			for(int b=0; b<4; b++){
				
				tetro_v[a][b]= ' ';
			
			}
		
		
		}
	
	
	
	}
	bool Tetromino::asagi_kaydir(){
		
		bool ret_d = true;
		
		do{
		
			
			for(int a=0; a<4; a++) {
				
				if(tetro_v[3][a] == symbol) ret_d = false;
			
			
			}

			if(ret_d){
			
				for(int b=3; b>=0; b--) {
						
						for(int a=0; a<4; a++){
							
								if(b>0) tetro_v[b][a] = tetro_v[b-1][a];
			
								else tetro_v[b][a] = ' ';
						}
					
				}
			}
			
		}while(ret_d);
	
		return ret_d;
	
	}
	bool Tetromino::sola_kaydir(){
	
		bool ret_d = true;
		
		do{
		
			for(int a=0; a<4; a++) {
			
				if(tetro_v[a][0] == symbol) ret_d = false;
			
			
		}
			
			if(ret_d){
			
				for(int a=0; a<4; a++) {
						
						for(int b=0; b<4; b++){
							
								if(a<(3)) tetro_v[b][a] = tetro_v[b][a+1];
			
								else tetro_v[b][a] = ' ';
						}
					
				}
			}
			
		}while(ret_d);
	
		return ret_d;
	
	}
	
	void yedek_guncelle(){
	
	
	
	
	
	
	
	}
	

	
	vector<vector<char>> Tetromino::birlestir(vector<vector<char>> y_tetro,int& sayac){
	
	int kontrol =0,sayac1=0, kontrol2=0;
	
	for(int a=0; a<4; a++){
		
		kontrol = 0;
		
		for(int c=0; c<4; c++)	{
			
				if(tetro_v[c][a] == symbol){
				
					kontrol = 1;
				
					break;
				
				}
			}
	
		
		if(kontrol) {
			
			for(int b=0; b<4; b++){
				

				y_tetro[b][a+sayac] = tetro_v[b][a];
				
				
			}
		sayac1++;
		}
			
	}
	
	
	for(int a=3 ;a>=2 ;a--){

		for(int b=0;b<y_tetro[0].size();b++){
	
			if(a != 2 && y_tetro[a][b] == ' ' && y_tetro[a-1][b+1] == ' '){
			
				for(int c=0; c<4; c++){
			
					for(int d = b; d< y_tetro[0].size()-1; d++){
								
						if(y_tetro[c][d] == ' ')
						{
						 y_tetro[c][d]=y_tetro[c][d+1];
						y_tetro[c][d+1] = ' ';
						}
					
					}
				}
				sayac--;
			}		
			
			if(a == 2 && y_tetro[a][b] == ' ' && y_tetro[a+1][b+1] == ' '){

				for(int c=0; c<4; c++){
			
					for(int d = b; d<y_tetro[0].size()-1; d++){
						
						
								
						if(y_tetro[c][d] == ' ')
						{
						
						
						y_tetro[c][d]=y_tetro[c][d+1];
						y_tetro[c][d+1] = ' ';
						}
					}
				}
				sayac--;
			
			
			}
		
		}
	
	}
	
	
	sayac+=sayac1;
	
	return y_tetro;
	
	}
	
	vector<vector<char>> Tetromino::get_vector() const{
	
	return tetro_v;	
	
	}
	
	bool Tetromino::canfit(vector<vector<char>> sonuc,const int& sayac,vector<Tetromino>& tetro, int index){
	
	vector<vector<char>> deneme;
	int sayac1=sayac;
	
	deneme = sonuc;
	
	deneme = tetro[index].birlestir(deneme,sayac1);
	
		for (int b=1; b<sonuc[0].size(); b++){
		
		if(deneme[3][b-1+sayac-2] != ' ' && deneme[3][b+sayac-2] == ' ' && deneme[3][b+2+sayac-2] == tetro[index].get_symbol()) return false;			
		
		}
	
	return true;
	
	}
	
	vector<vector<char>> Tetromino::best_fit(vector<Tetromino> tetrominos, vector<vector<char>> sonuc, int& sayac, int tetro_n){
		
		bool ab;
		int dondu=0;
		
		sonuc = tetrominos[0].birlestir(sonuc,sayac);

		for(int a=1; a<tetro_n; a++){
	
			dondu = 0;
			 
			 do{
			 
				 ab = tetrominos[a].canfit(sonuc,sayac,tetrominos,a);
				
				 if(ab || dondu == 4) sonuc = tetrominos[a].birlestir(sonuc,sayac); // sayaca bak
		
				 else {
				
				 	tetrominos[a].rotate_l();
				
				 	dondu++;
				 }
			 
			 }while(!ab && dondu != 4);

			
}
	
	return sonuc;
	
	}

#endif
