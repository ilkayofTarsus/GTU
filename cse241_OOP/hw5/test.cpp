#include"TetrisVector.h"
#include"Tetrisarray.h"
#include"Adapter.cpp"


using namespace array1;
using namespace vector1;
using namespace adapter;

int main(){

char type;

int row = 0, column = 0,sayac=0;
int tetro_n=0, kaydirma=0, kay=0, donus_s=0;
char pre_shape , donus;

try{
		srand(time(NULL));		
					
		cout << "type array selected... " << endl;
		sleep_for(std::chrono::milliseconds(1500));


				TetrisArray1d board1(20);
				board1.draw();

					Tetromino obje(static_cast <tetro_shapes> ('T'));
					board1 += obje;
					board1.draw();

					for(int a = 0; a<2; a++){
						obje.rotate_l();
						board1.set_numofmv(1);
					}
						
					board1 += obje;
					board1.draw();

						
						for(int a=0; a<7; a++) {
						board1.kaydir_sola(obje);
						board1.set_numofmv(1);
						board1.set_lastmv('l');
						}
					

					board1.animate(obje);
					
					if(board1.sil()) board1.draw();	


			cout << "type vector selected... " << endl;
			sleep_for(std::chrono::milliseconds(1500));

				TetrisVector board2(20);
				board2.draw();

					Tetromino obje2(static_cast <tetro_shapes> ('S'));
					board2 += obje2;
					board2.draw();

					for(int a = 0; a<2; a++){
						obje2.rotate_l();
						board2.set_numofmv(1);
					}
						
					board2 += obje2;
					board2.draw();

						
						for(int a=0; a<7; a++) {
						board2.kaydir_saga(obje2);
						board2.set_numofmv(1);
						board2.set_lastmv('l');
						}
					

					board2.animate(obje2);
					
				
				cout << "type adapter selected " << endl;
				sleep_for(std::chrono::milliseconds(1500));

				TetrisAdapter< vector <vector<char> > > board3(20);
				board3.draw();

					Tetromino obje3(static_cast <tetro_shapes> ('L'));
					board3 += obje3;
					board3.draw();

					for(int a = 0; a<2; a++){
						obje3.rotate_l();
						board3.set_numofmv(1);
					}	
					board3 += obje3;
					board3.draw();

						for(int a=0; a<5; a++) {
						board3.kaydir_saga(obje3);
						board3.set_numofmv(1);
						board3.set_lastmv('l');
						}
					

					board3.animate(obje3);
					
					cout << endl << endl << "Board is writed to file " << endl;
					sleep_for(std::chrono::milliseconds(1500));

					board3.writetofile("text.txt");

} 

catch(...){
	cerr <<"Exception occured" << endl;
}
	return 0;
	
}
