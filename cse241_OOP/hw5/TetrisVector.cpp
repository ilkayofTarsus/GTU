#include "TetrisVector.h"
	
namespace vector1{

TetrisVector::TetrisVector(int length) : AbstractTetris(length){
	
	vector <vector <char>> board_y(boy+2,vector<char>(en+2));

	for(int i=0; i<length+2; i++){

		for(int j =0; j<length+2; j++){
		
			if(i==0) {
			
				board_y[i][j] = '&' ;
				}		
			
			else if(j==0 || j== length+1) board_y[i][j] ='&' ;
			
			else if(i == length+1) board_y[i][j] = '&';
			
			else board_y[i][j] = ' ';
		}
	}
board = board_y;
board_yedek = board;
}

void TetrisVector::writetofile(string file_name){
	
		fstream file;
		file.open(file_name);
		for(int a=0; a<boy+2; a++){
		
			for(int b=0; b<en+2; b++){
			
			file << board[a][b];
			
			
			}
		
		file << endl;
		
		}
		file.close();
	}

void TetrisVector::readfromfile(string file_name){
		
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


void TetrisVector::operator +=(const Tetromino& other){

for(int a=1; a< 5; a++){
		
		for(int b =(en/2); b<(en/2 + 4) ; b++){
		
			board[a][b] = ' '; 
		
		}
	}



	for(int a=1; a< 5; a++){
		
		for(int b = (en/2); b < (en/2 + 4) ; b++){
		
			board[a][b] =  other.get_vectorc( a-1 , b-(en/2) ); 
		
		}
	}

 }


/*
vector<vector<char>> temp;

	for(int a=1; a< 5; a++){
		
		for(int b =(en/2); b<(en/2 + 4) ; b++){
		
			temp =other.get_vector();
			board[a][b] = temp[a-1][b-(en/2)];  
		}
	}
//return *this;

}
*/
void TetrisVector::draw()const {


	for(int a=0; a<boy+2; a++){
	
		for(int b=0; b<en+2; b++){
		
		cout << board[a][b];
		
		
		}
	
	cout << endl;
	
	}


}

void TetrisVector::kaydir_asagi(const Tetromino& obje){

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

void TetrisVector::kaydir_saga(const Tetromino& obje){

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

void TetrisVector::kaydir_sola(const Tetromino& obje){

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

int TetrisVector::kaydirma_s(const Tetromino& obje)const{

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
void TetrisVector::animate( Tetromino& obje){
int kay = kaydirma_s(obje);
		
	 for(int a = 0; a < kay; a++){
		
		sleep_for(std::chrono::milliseconds(220));
		
	 	kaydir_asagi(obje);	

		cout << "\x1B[2J\x1B[H";

		draw();

	}

}

bool TetrisVector::sil(){

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

bool TetrisVector::isLegal(char pre_shape){


return (pre_shape == 'T' || pre_shape == 'I' || pre_shape == 'O' || pre_shape == 'Z'|| pre_shape == 'S'|| pre_shape == 'J'|| pre_shape == 'L' || pre_shape == 'Q');

}

bool TetrisVector::is_finished(){

bool finished = false;

	for(int a = 1; a < 5; a++ ){
	
		for(int b = 1; b < en + 1 ; b++){
		
					
		if( board[a][b] != ' ') finished = true;		
		}
	}
return finished;

}
} // end of namespace
