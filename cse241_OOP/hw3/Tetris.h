#ifndef _TETRIS_H_
#define _TETRIS_H_
#include<chrono>
#include <thread>
#include "Tetromino.h"


    using namespace std;
    using namespace std::this_thread;     // sleep_for, sleep_until
    using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
    using std::chrono::system_clock;

using namespace Tetromino1;


namespace Tetris1{

class Tetris{

public:

	Tetris(int,int);
	~Tetris();
	Tetris(const Tetris&);
	void operator +=(const Tetromino&);
	Tetris operator =(const Tetris&);
	char move(char);
	void set_index(int);
	void animate(Tetromino&)const;
	bool sil();
	int get_boy() const { return boy;}
	char** get_board()const{ return board;}		//cıktısı 2 boyutlu char vektor
	int get_en() const { return en;}
	int get_tetron()const {return tetro_n;}
	int get_index()const {return index;}	
	void print_board()const;							//print board
	int kaydirma_s(const Tetromino&)const;			// parametresi 2boyutlu char vektor		// asagıya ne kadar kaydırması gerektıgını bıldırır
	void kaydir_asagi(const Tetromino& ) const;								// tetromınoyu kaydırır
	void fit();									// yatayda dogru konumuna koyar 
	int calc_haritax();
	void add_tetro(char);								//tetromınolar tetrısın classının ıcınde tetromıno vektorune eklenir
	void add_tetro_tomap(const Tetromino&);								// tetromınoları boardın ortasına ekler
	void rotate();
	void kaydir_sola(const Tetromino&);
	void kaydir_saga(const Tetromino&);
	bool isLegal(char pre_shape);
	bool is_finished();

private:
	
	char** board;
	char** board_yedek;
	int boy;
	int en;
	int harita_x;
	int index;
	int tetro_n;

};


}						// end of namespace
#endif
