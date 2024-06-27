#ifndef _TETRISVECTOR_H
#define _TETRISVECTOR_H

#include"abstract.h" 
using namespace abstract;

namespace vector1{

class TetrisVector : public AbstractTetris{

public:
	
	
//	Tetris operator =(const Tetris&);
	char move(char);
	void animate(Tetromino&);
	bool sil();
	int get_boy() const { return boy;}
	vector<vector<char>> get_board()const{ return board;}		//cıktısı 2 boyutlu char vektor
	int kaydirma_s(const Tetromino&)const;			// parametresi 2boyutlu char vektor		// asagıya ne kadar kaydırması gerektıgını bıldırır
	void kaydir_asagi(const Tetromino& ) ;								// tetromınoyu kaydırır
	int calc_haritax();
	//void rotate();
	void kaydir_sola(const Tetromino&);
	void kaydir_saga(const Tetromino&);
	bool isLegal(char pre_shape);
	bool is_finished();
	void writetofile(string);
	void readfromfile(string);
	//void print_board()const;
	
	
	
	TetrisVector(int length);
	virtual~TetrisVector(){};
	void draw()const override;
	void operator+=(const Tetromino&)override;
private:
	vector <Tetromino> tetros;
	vector <vector <char>> board;
	vector<vector<char>> board_yedek;

};
}//end of namespace

#endif
