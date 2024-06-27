#ifndef _TETROMINO_H_
#define _TETROMINO_H_

enum class tetro_shapes{ i='I', o='O', t='T', j='J', l='L', s='S', z='Z'};

namespace Tetromino1{

class Tetromino{

	public:
		void print_tet();
		Tetromino( tetro_shapes);
		~Tetromino();
		char get_vectorc(int, int) const;
		void set_symbol(char a);
		void print_s(char** , int) const;
		char** birlestir(char**,int&);
		void rotate_l() ;
		char get_symbol() const;
		void rotate_r();
	private:

		void yedek_guncelle();
		bool asagi_kaydir();
		bool sola_kaydir();
		void bosluk_doldur( ); 
		char symbol;
		//static int tetro_number;
		char** tetro_v;
		char** tetro_yedek;
};


}						// end of namespace

#endif

