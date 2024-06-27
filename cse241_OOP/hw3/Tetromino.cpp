#ifndef _TETROMINO_
#define _TETROMINO_
#include "Tetromino.h"
#include <iostream>
using namespace std;

namespace Tetromino1{

	Tetromino::Tetromino(tetro_shapes symbol){
	
	tetro_v = new char*[4];

	for(int a = 0; a< 4; a++) {

		tetro_v[a] = new char[4];
	
	tetro_yedek = new char*[4];

		for(int a = 0; a< 4; a++) {

			tetro_yedek[a] = new char[4];

		}


	}
	
	set_symbol(static_cast<char> (symbol));
	
	
	switch(symbol){
		
			case tetro_shapes::i:
			
				for(int i=0;i<4;i++){
				
					for(int j=0;j<4;j++){
					
						if(3==i){
							tetro_v[i][j]='I';
						}
						
						else
							tetro_v[i][j]=' ';
					}
				}
			break;
				
			case tetro_shapes::o:
			
				for(int i=0;i<4;i++){
				
					for(int j=0;j<4;j++){
					
						if( ((2==i || 3==i) && (0==j || 1==j)) ){
							tetro_v[i][j]='O';
						}
						
						else
							tetro_v[i][j]=' ';
					}
				}
			break;
			
			case tetro_shapes::t:
			
				for(int i=0;i<4;i++){
				
					for(int j=0;j<4;j++){
					
						if( (2==i && (0==j || 1==j || 2==j)) || (3==i && 1==j) ){
							tetro_v[i][j]='T';
						}
						
						else
							tetro_v[i][j]=' ';
					}
				}
			break;
				
			case tetro_shapes::j:
			
				for(int i=0;i<4;i++){
				
					for(int j=0;j<4;j++){
					
						if( (1==j && (1==i || 2==i || 3==i)) || (3==i && 0==j) ){
							tetro_v[i][j]='J';
						}
						
						else
							tetro_v[i][j]=' ';
					}
				}
			
			break;
				
			case tetro_shapes::l:
				
				for(int i=0;i<4;i++){
				
					for(int j=0;j<4;j++){
					
						if( (0==j && (1==i || 2==i || 3==i)) || (3==i && 1==j) ){
							tetro_v[i][j]='L';
						}
						
						else
							tetro_v[i][j]=' ';
					}
				}
			
			break;
			
			case tetro_shapes::s:
			
				for(int i=0;i<4;i++){
			
					for(int j=0;j<4;j++){
					
						if( (2==i && (1==j || 2==j)) || (3==i && (0==j || 1==j)) ){
							tetro_v[i][j]='S';
						}
						
						else
							tetro_v[i][j]=' ';
					}
				}
			
			break;
			
			case tetro_shapes::z:
			
				for(int i=0;i<4;i++){
				
					for(int j=0;j<4;j++){
					
						if( (2==i && (0==j || 1==j)) || (3==i && (1==j || 2==j)) ){
							tetro_v[i][j]='Z';
						}
						
						else
							tetro_v[i][j]=' ';
					}
				}
			
			break;	
		
		}	
	
	}
	
	Tetromino::~Tetromino(){
	
	if(tetro_v != nullptr){
		for(int a=0; a< 4; a++)
			if(tetro_v[a] != nullptr) delete [] tetro_v[a];

		delete [] tetro_v ;
		tetro_v == nullptr;
	}
	
	if(tetro_yedek != nullptr){
		for(int a=0; a< 4; a++)
			if(tetro_yedek != nullptr) delete [] tetro_yedek[a];

		delete [] tetro_yedek;
		tetro_yedek = nullptr;
	}
	
	}
	
	
	void Tetromino::print_s(char** v,int inc)const{
	
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
	
		
	
		
		for(int a=0; a< 4; a++){

			for(int b =0; b<4 ; b++){

				
				tetro_yedek[a][b] = tetro_v[a][b];			
			
			}
		}
	
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
	
		
		for(int a=0; a< 4; a++){

			for(int b =0; b<4 ; b++){

				
				tetro_yedek[a][b] = tetro_v[a][b];			
			
			}
		}	

 		bosluk_doldur();
 			
 			
 				for(int a=0; a<4; a++) {
						
					for(int b=0; b<4; b++){
							
							tetro_v[b][a] = tetro_yedek[a][3-b];
					}
				}
 			asagi_kaydir();
 			sola_kaydir();
	
	}
	
	void Tetromino::print_tet(){
	
		for(int a=0; a<4; a++){
		
			for(int b=0; b<4; b++){
			
			cout << tetro_v[a][b];
			
			
			}
		
		cout << endl;
		
		}
	
	
	
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
				
				if(tetro_v[3][a] != ' ') ret_d = false;
			
			
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
			
				if(tetro_v[a][0] != ' ') ret_d = false;
			
			
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
		
	char Tetromino::get_vectorc(int a, int b) const{
	
	return tetro_v[a][b];	
	
	}
	
}						// end of namespace	

#endif
