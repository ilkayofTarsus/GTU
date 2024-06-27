#ifndef _TETRIS_H_
#define _TETRIS_H_
#include <vector>
#include<chrono>
#include <thread>

using std::vector;


    using namespace std;
    using namespace std::this_thread;     // sleep_for, sleep_until
    using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
    using std::chrono::system_clock;


class Tetris{

public:

	Tetris(int,int);
	
	char move(char);
	void set_index(int);
	void animate();
	
	vector <Tetromino> get_tetros()const{ return tetros;}
	int get_boy() const { return boy;}
	vector <vector<char>> get_board()const{ return board;}
	int get_en() const { return en;}
	int get_tetron()const {return tetro_n;}
	int get_index()const {return index;}	
	void print_board()const;							//print board

private:
	int kaydirma_s(vector<vector<char>>)const;					// asagıya ne kadar kaydırması gerektıgını bıldırır
	void kaydir_asagi();								// tetromınoyu kaydırır
	void fit();									// yatayda dogru konumuna koyar 
	int calc_haritax();
	void add_tetro(char);								//tetromınolar tetrısın classının ıcınde tetromıno vektorune eklenir
	void add_tetro_tomap();								// tetromınoları boardın ortasına ekler
	void rotate();
	vector <Tetromino> tetros;
	vector <vector <char>> board;
	vector<vector<char>> board_yedek;
	int boy;
	int en;
	int harita_x;
	int index;
	int tetro_n;
	void kaydir_sola();
	void kaydir_saga();


};



#endif
