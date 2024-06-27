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
			
		cout << "Select type (v for vector, a for array, A for adapter)" << endl;
		cin >> type;
		
		if(type != 'a' && type !='v' && type !='A' ) throw;	
		
		srand(time(NULL));

		switch(type){


			case ('a'):{

				cout << endl << endl << endl << " Give the size of Tetris board (row )"<< endl;
				cin >> row;

				column = row;
				TetrisArray1d board1(row);
				board1.draw();

				do{
					
					cout << "give the tetromino type" << endl;

					do{

					cin >> pre_shape;
					if(!board1.isLegal(pre_shape)) cerr << "Give the legal tetromno type" << endl;
					}while(!board1.isLegal(pre_shape));
					
					if(pre_shape == 'Q') break;	

					Tetromino obje(static_cast <tetro_shapes> (pre_shape));
					board1 += obje;
					board1.draw();

					cout << "which direction do you want tetromino rotate (l or r)" << endl;
					cin >> donus;

					cout << "how many time do you want to rotate" << endl;
					cin >> donus_s;

					if(donus == 'l')
						for(int a = 0; a<donus_s; a++){
							obje.rotate_l();
							board1.set_numofmv(1);
							}
					if(donus == 'r') 
						for(int a = 0; a<donus_s; a++){
							obje.rotate_r();
							board1.set_numofmv(1);
							}
						
					board1 += obje;
					board1.draw();

					cout << "which side do you want tetromino to slide" << endl;
					cin >> donus ;

					cout << "how many times should tetromino slide" << endl
					     << "!! it must be " << row/2 -1 << " mostly" << endl;
					cin >> donus_s;

					switch(donus){
					
						case 'l':
						
						for(int a=0; a<donus_s; a++) {
						board1.kaydir_sola(obje);
						board1.set_numofmv(1);
						board1.set_lastmv('l');
						}
						break;
					
					
						case 'r':
						
						for(int a=0; a<donus_s; a++){
						board1.kaydir_saga(obje);
						board1.set_numofmv(1);
						board1.set_lastmv('r');
						}
						break;
					}

					board1.animate(obje);
					
					if(board1.sil()) board1.draw();	

				}while(!board1.is_finished());
				sleep_for(std::chrono::milliseconds(500));
			}break;


			case ('v'):{

				cout << endl << endl << endl << " Give the size of Tetris board (row )"<< endl;
				cin >> row;

				column = row;
				TetrisVector board2(column);
				board2.draw();

				do{
					
					cout << "give the tetromino type" << endl;

					do{

					cin >> pre_shape;
					if(!board2.isLegal(pre_shape)) cerr << "Give the legal tetromno type" << endl;
					}while(!board2.isLegal(pre_shape));
					
					if(pre_shape == 'Q') break;	
					Tetromino obje(static_cast <tetro_shapes> (pre_shape));
					board2 += obje;
					board2.draw();

					cout << "which direction do you want tetromino rotate (l or r)" << endl;
					cin >> donus;

					cout << "how many time do you want to rotate" << endl;
					cin >> donus_s;

					if(donus == 'l')
						for(int a = 0; a<donus_s; a++){
							obje.rotate_l();
							board2.set_numofmv(1);
							}

					if(donus == 'r') 
						for(int a = 0; a<donus_s; a++){
							obje.rotate_r();
							board2.set_numofmv(1);
							}
						
					board2 += obje;
					board2.draw();

					cout << "which side do you want tetromino to slide" << endl;
					cin >> donus ;

					cout << "how many times should tetromino slide" << endl
					     << "!! it must be " << row/2 -1 << " mostly" << endl;
					cin >> donus_s;

					switch(donus){
					
						case 'l':
						
						for(int a=0; a<donus_s; a++){
						 board2.kaydir_sola(obje);
						board2.set_numofmv(1);
						board2.set_lastmv('l');
						}
						break;
					
						case 'r':
						
						for(int a=0; a<donus_s; a++) {
						board2.kaydir_saga(obje);
						board2.set_numofmv(1);
						board2.set_lastmv('r');
						}
						break;
						
					}
					board2.animate(obje);

					if(board2.sil()) board2.draw();	
				}while(!board2.is_finished());
			}break;	
			
			case ('A'):{

				cout << endl << endl << endl << " Give the size of Tetris board (row )"<< endl;
				cin >> row;

				column = row;
				TetrisAdapter< vector <vector<char> > > board3(column);
				board3.draw();

				do{
					
					cout << "give the tetromino type" << endl;

					do{

					cin >> pre_shape;
					if(!board3.isLegal(pre_shape)) cerr << "Give the legal tetromno type" << endl;
					}while(!board3.isLegal(pre_shape));
					
					if(pre_shape == 'Q') break;	
					Tetromino obje(static_cast <tetro_shapes> (pre_shape));
					board3 += obje;
					board3.draw();

					cout << "which direction do you want tetromino rotate (l or r)" << endl;
					cin >> donus;

					cout << "how many time do you want to rotate" << endl;
					cin >> donus_s;

					if(donus == 'l')
						for(int a = 0; a<donus_s; a++){
							obje.rotate_l();
							board3.set_numofmv(1);
							}

					if(donus == 'r') 
						for(int a = 0; a<donus_s; a++){
							obje.rotate_r();
							board3.set_numofmv(1);
							}
						
					board3 += obje;
					board3.draw();

					cout << "which side do you want tetromino to slide" << endl;
					cin >> donus ;

					cout << "how many times should tetromino slide" << endl
					     << "!! it must be " << row/2 -1 << " mostly" << endl;
					cin >> donus_s;

					switch(donus){
					
						case 'l':
						
						for(int a=0; a<donus_s; a++){
						 board3.kaydir_sola(obje);
						board3.set_numofmv(1);
						board3.set_lastmv('l');
						}
						break;
					
						case 'r':
						
						for(int a=0; a<donus_s; a++){
						 board3.kaydir_saga(obje);
						board3.set_numofmv(1);
						board3.set_lastmv('r');
						}
						break;
					}
					board3.animate(obje);

					if(board3.sil()) board3.draw();	
				}while(!board3.is_finished());
			}break;	


		}	
} 
catch(...){
	cerr <<"Exception occured" << endl;
}
	return 0;
}

