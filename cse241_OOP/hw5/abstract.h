#ifndef _ABSTRACT_H_
#define _ABSTRACT_H_


#include <iostream>
#include"Tetrominoa.h"
#include<fstream>
#include<vector>
#include<chrono>
#include<thread>
#include <ctime>
#include <cstdlib>

using std::this_thread::sleep_for;
using namespace std;


namespace abstract{
class AbstractTetris{

public:
	AbstractTetris(int length) : lastmv('x'), numofmv(0), harita_x(0), index(0)
	{
		boy = length;
		en = length;
	};
	virtual ~AbstractTetris(){};
	virtual void draw()const = 0 ;
	virtual void operator+=(const Tetromino&) = 0;
	virtual void kaydir_sola(const Tetromino&) = 0;
	virtual void kaydir_saga(const Tetromino&) = 0;
	virtual int kaydirma_s(const Tetromino&)const = 0;			// parametresi 2boyutlu char vektor		// asagıya ne kadar kaydırması gerektıgını bıldırır
	virtual void readfromfile(string) = 0;
	virtual void writetofile(string) = 0;
	char lastmove() { return lastmv;};
	int numberofmoves(){return numofmv;} ;
	int get_en() const { return en;}
	int get_tetron()const {return tetro_n;}
	int get_index()const {return index;}
	int get_numofmv()const{return numofmv;}
	void set_index(int sayi){ index += sayi;}
	void set_numofmv(int sayi){ numofmv += sayi;}
	void set_lastmv(char las){lastmv = las ;}

protected:
	char lastmv;
	int numofmv;
	int boy;
	int en;
	int harita_x;
	int index;
	int tetro_n;
	

};	

} //end of namespace
#endif


