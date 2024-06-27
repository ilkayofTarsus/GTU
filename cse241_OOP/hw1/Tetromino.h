#ifndef _TETROMINO_H_
#define _TETROMINO_H_
#include <vector>


using std::vector;

enum class tetro_shapes{ i='I', o='O', t='T', j='J', l='L', s='S', z='Z'};

class Tetromino{

	public:

		Tetromino( tetro_shapes /*enum tetro_shapes*/);
		vector<vector<char>> get_vector() const;
		void set_symbol(char a);
		void print_s(vector<vector<char>> , int) const;
		bool canfit(vector<vector<char>>,const int&,vector<Tetromino>&,int) ;
		//vector<vector<char>> birlestir(vector<vector<char>>,vector<vector<char>>);
		vector<vector<char>> birlestir(vector<vector<char>>,int&);
		vector<vector<char>> pre_birlestir();
		void rotate_l() ;
		char get_symbol() const;
		void rotate_r();
		vector<vector<char>> best_fit(vector<Tetromino>, vector<vector<char>>, int&, int);
	private:

		void yedek_guncelle();
		bool asagi_kaydir();
		bool sola_kaydir();
		void bosluk_doldur( ); 
		char symbol;
		//static int tetro_number;
		vector <vector <char>> tetro_v;
		vector <vector <char>> b_tetro;
		vector <vector <char>> tetro_yedek;
};
#endif

