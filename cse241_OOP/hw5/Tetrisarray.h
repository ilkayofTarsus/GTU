#include"abstract.h"
#include<chrono>
#include<thread>
#include <ctime>


using namespace std;
using std::this_thread::sleep_for;
using namespace abstract;	

namespace array1{

class TetrisArray1d : public AbstractTetris{

public:
	TetrisArray1d(int );
	~TetrisArray1d();
	//TetrisArray1d(const Tetris&);
	void operator +=(const Tetromino&); //
	//Tetris operator =(const Tetris&);
	char move(char);
	void set_index(int);
	void animate(Tetromino&)const; //
	bool sil();
	void draw()const;	//						//print board
	int kaydirma_s(const Tetromino&)const; //			// parametresi 2boyutlu char vektor		// asagıya ne kadar kaydırması gerektıgını bıldırır
	void kaydir_asagi(const Tetromino& ) const; //								// tetromınoyu kaydırır
	int calc_haritax();
	void add_tetro_tomap(const Tetromino&);								// tetromınoları boardın ortasına ekler
	void rotate();
	void kaydir_sola(const Tetromino&); //
	void kaydir_saga(const Tetromino&); //
	bool isLegal(char pre_shape);
	bool is_finished();	
	void writetofile(string);
	void readfromfile(string);

	char* get_board()const{ return board;}		//cıktısı 2 boyutlu char vektor

private:
	
	char* board;
	char* board_yedek;

};
}//end of namespace
