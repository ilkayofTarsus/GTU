#include"Tetrisarray.h"

namespace array1{

TetrisArray1d::TetrisArray1d(int length) : AbstractTetris(length){							// constructor	
	
	board =  (char*) malloc ((boy+2)*(en+2));
	board_yedek = (char*) malloc ((boy+2)*(en+2)); 

	for(int i=0; i<boy+2; i++){

		for(int j =0; j<en+2; j++){
		
			if(i ==0 || i == boy+1 || j ==0 || j == en+1) board[i*(en+2)+j] = '&' ;
			
			else board[i*(en+2)+j] = ' ';
		}
	}
}


TetrisArray1d::~TetrisArray1d(){						// destructor 
	
		delete [] board ;

}


void TetrisArray1d::readfromfile(string file_name){
		
		fstream file;
		file.open(file_name);
		char r;
		int sayac = 0;		
		while(!file.eof()){
			
			if(sayac == en+2){
			sayac=0;
			cout << endl;
			}	
			file >> r;			
			cout << r;	
			sayac++;
		}
		file.close();
}




void TetrisArray1d::writetofile(string file_name){
	
		fstream file;
		file.open(file_name);
		for(int a=0; a<boy+2; a++){
		
			for(int b=0; b<en+2; b++){
			
			file << board[a*(en+2)+b];
			
			
			}
		
		file << endl;
		
		}
		file.close();
	}




void TetrisArray1d::operator +=(const Tetromino& other){

for(int a=1; a< 5; a++){
		
		for(int b =(en/2); b<(en/2 + 4) ; b++){
		
			board[a*(en+2)+b] = ' '; 
		
		}
	}



	for(int a=1; a< 5; a++){
		
		for(int b = (en/2); b < (en/2 + 4) ; b++){
		
			board[a*(en+2)+b] =  other.get_vectorc( a-1 , b-(en/2) ); 
		
		}
	}


}

void TetrisArray1d::set_index(int sayi){

	index += sayi;

}

void TetrisArray1d::draw()const {


	for(int a=0; a<boy+2; a++){
	
		for(int b=0; b<en+2; b++){
		
		cout << board[a*(en+2)+b];
		
		
		}
	
	cout << endl;
	
	}


}

void TetrisArray1d::add_tetro_tomap(const Tetromino& tetrs){


for(int a=1; a< 5; a++){
		
		for(int b =(en/2); b<(en/2 + 4) ; b++){
		
			board[a*(en+2)+b] = ' '; 
		
		}
	}



	for(int a=1; a< 5; a++){
		
		for(int b = (en/2); b < (en/2 + 4) ; b++){
		
			board[a*(en+2)+b] =  tetrs.get_vectorc( a-1 , b-(en/2) ); 
		
		}
	}


}

void TetrisArray1d::kaydir_asagi(const Tetromino& obje)const{

	bool kontrol = true;
	char temp;
	
		for(int a=1; a < en+1; a++ ){
		
			for(int b=1; b < boy+1; b++){
				
				temp = 'x';		
					
				if(board[b*(en+2)+a] == obje.get_symbol()){
				
					for(int c=b+1; c<boy+1; c++){
						
						if(board[c*(en+2)+a] == ' '){
							
								temp = board[c*(en+2)+a];
								board[c*(en+2)+a] = board[b*(en+2)+a];		
								board[b*(en+2)+a] = temp;
								temp = ' ';
						}
					}	
				}
				if(temp == ' ') break;
			}
		}
}

void TetrisArray1d::kaydir_saga(const Tetromino& obje){

	bool kontrol = true;
	char temp;
		
		for(int a = 0; a<boy+2 ;a++){
		
			for(int b=0; b<en+2; b++){
			
			board_yedek[a*(en+2)+b] = board[a*(en+2)+b]; 
			}
		}
		for(int b=1; b < 5; b++){
		
			for(int a=1; a < en; a++ ){
				
				temp = 'x';		
					
				if(board_yedek[b*(en+2)+a] == obje.get_symbol()){ // burası ve asgısı
				
					for(int c=a; c<en+1; c++){
					
						if(board_yedek[b*(en+2)+c] == ' ' ){
							
							temp = board_yedek[b*(en+2)+c];
							board_yedek[b*(en+2)+c] = board_yedek[b*(en+2)+a];		
							board_yedek[b*(en+2)+a] = temp;
							temp = ' ';
						}
					}	
				}
				if(temp == ' ') break;
			}
		}
		for(int a = 0; a<boy+2 ;a++){
		
			for(int b=0; b<en+2; b++){
			
			board[a*(en+2)+b] = board_yedek[a*(en+2)+b]; 
			}
		}
}

void TetrisArray1d::kaydir_sola(const Tetromino& obje){

	bool kontrol = true;
	char temp;
		
		for(int a = 0; a<boy+2 ;a++){
		
			for(int b=0; b<en+2; b++){
			
			board_yedek[a*(en+2)+b] = board[a*(en+2)+b]; 
			
			
			}
		
		
		}
		
		for(int b=1; b < boy; b++){
		
			for(int a=en; a > 0 ; a-- ){
				
				temp = 'x';		
				
				if(board_yedek[b*(en+2)+a] == obje.get_symbol()){ // burası ve asagısı
				
					for(int c=a; c>0; c--){
						
						if(board_yedek[b*(en+2)+c] == ' ' ){
							
							temp = board_yedek[b*(en+2)+c];
							board_yedek[b*(en+2)+c] = board_yedek[b*(en+2)+a];		
							board_yedek[b*(en+2)+a] = temp;
							temp = ' ';
						}
					}	
				}
				if(temp == ' ') break;
			}
		}
		for(int a = 0; a<boy+2 ;a++){
		
			for(int b=0; b<en+2; b++){
			
			board[a*(en+2)+b] = board_yedek[a*(en+2)+b]; 
			}
		}
}

int TetrisArray1d::kaydirma_s(const Tetromino& obje)const{

int kaydirma=99, kaydirma_y =0, kaydirma_y1 =0,kaydirma_y2 =0;

		for(int b = 1 ; b < boy+1 ; b++){
		
			for(int a = 1; a < 5; a++){
				
				if(board[a*(en+2)+b] == obje.get_symbol()){ // burası ve asasgısı
					
					kaydirma_y=0;
					kaydirma_y1 =0;
					kaydirma_y2 =0;	
					for(int c = a; c < boy+1; c++){
					
						if(board[c*(en+2)+b] == ' '){
						
						kaydirma_y++;
						
						}
						

						if(board[c*(en+2)+(b+1)] == ' ') kaydirma_y1++;
						
						
						if(board[c*(en+2)+b+1] != '&'){
						 	
						 	if( board[c*(en+2)+b+2] == ' ') kaydirma_y2++;
						
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
void TetrisArray1d::animate( Tetromino& obje)const{
int kay = kaydirma_s(obje);
		
	 for(int a = 0; a < kay; a++){
		
		sleep_for(std::chrono::milliseconds(220));
		
	 	kaydir_asagi(obje);	

		cout << "\x1B[2J\x1B[H";

		draw();

	}

}

bool TetrisArray1d::sil(){

	bool silme = true, ret = false;

	do{

		for(int a=1; a< en+1 ; a++){
		
			if(board[boy*(en+2)+a] == ' ') silme = false;
		
		
		}

		if(silme){
			
			ret = true;
			cout << "\x1B[2J\x1B[H";
			
			for(int a=boy; a >2; a--){
			
				for(int b=1; b<en+1; b++ ){
				
				board[a*(en+2)+b] = board[(a-1)*(en+2)+b];
				
				
				}
			
			
			}
		
		for(int b=1; b<en+1; b++ ) board[1*(en+2)+b] = ' ';
		
		}
	}while(silme);
return ret;

}

bool TetrisArray1d::isLegal(char pre_shape){


return (pre_shape == 'T' || pre_shape == 'I' || pre_shape == 'O' || pre_shape == 'Z'|| pre_shape == 'S'|| pre_shape == 'J'|| pre_shape == 'L' || pre_shape == 'Q');

}

bool TetrisArray1d::is_finished(){

bool finished = false;

	for(int a = 1; a < 5; a++ ){
	
		for(int b = 1; b < en + 1 ; b++){
		
					
		if( board[a*(en+2)+b] != ' ') finished = true;		
		
		
		}
	
	}

return finished;

}
} //end of namespace
