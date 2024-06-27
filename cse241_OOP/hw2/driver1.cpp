#include<iostream>
#include "Tetromino.h"
#include "Tetromino.cpp"
#include "Tetris.cpp"
#include "Tetris.h"
#include<vector>



using namespace std;

int main(){

int tetro_n=0,sayac=0, dondu=0;
char pre_shape , pre_shape2;
bool ab;

vector <char> shapes;

cout << endl << endl << endl;

for(int a = 0; a < 100; a++) cout << "%";

cout << endl << endl << endl;

cout << endl << "Tetromino foksiyonlari kontrol ediliyor" << endl;

cout << endl << endl << endl;

for(int a = 0; a < 100; a++) cout << "%";


cout << endl << endl << endl;



Tetromino fazla_t(static_cast<tetro_shapes>('O'));				// ASIM HATASI OLMASIN DIYE FAZLADAN BIR OBJECT
cout << "HOW MANY TETROS" << endl;

tetro_n = 2;

vector<vector<char>> sonuc (4,vector<char>(tetro_n*4));

vector <Tetromino> tetrominos;							// TETROLARIN TUTULDUGU TETRO CINSLI VEKTOR

cout << "WHAT ARE THE TYPES" << endl;


		pre_shape = 'T';
		pre_shape2 = 'L';
		
		tetrominos.push_back(static_cast<tetro_shapes>(pre_shape));	// SECILEN KARAKTERLERE GORE ENUM YAPISINI ARA BASAMAK OLARAK KULLANARAK YENI OBJELER YAPILIYOR
		tetrominos.push_back(static_cast<tetro_shapes>(pre_shape2));	

cout << "YOUR TETROMINOS : " << endl;
		
for (int a=0; a< tetro_n; a++) {
	
	tetrominos[a].print_s(tetrominos[a].get_vector(),0);

	cout << endl;
}
tetrominos.push_back(fazla_t);							// FAZLALIK OBJE VEKTORE EKLENIYOR

cout << "HORIZONTALLY BEST-FIT TETROS" << endl; 

sonuc = tetrominos[0].best_fit(tetrominos,sonuc,sayac,tetro_n);			// CANFITI ICINDE BARINDIRAN BEST FIT FONKSIYONU... BEST FITI BULUP ONA GORE YAN YANA DIZER

tetrominos[0].print_s(sonuc,tetro_n*4-4);					// SONUC HARITASI BASTIRILIR

cout << endl << endl << endl;

for(int a = 0; a < 100; a++) cout << "%";

cout << endl << endl << endl;

cout << endl << "Tetromino foksiyonlari calisiyor" << endl;

cout << endl << endl << endl;

for(int a = 0; a < 100; a++) cout << "%";


cout << endl << "5 saniye bekleme suresi ..."<< endl;
cout << "Tetris fonksiyonlari deneniyor"<< endl;

sleep_for(std::chrono::milliseconds(5000));


cout << endl << endl << endl;

cout << endl << endl << endl;

for(int a = 0; a < 100; a++) cout << "%";

cout << endl << endl << endl;

cout << endl << "Tetris kontrol ediliyor" << endl;

cout << endl << endl << endl;

for(int a = 0; a < 100; a++) cout << "%";


cout << endl << endl << endl;

int row = 0, column = 0;

int kaydirma=0, kay=0;

char pre1_shape;

//Tetromino fazla_t(static_cast<tetro_shapes>('O'));

cout<< " give the size of Tetris board (first row then column)"<< endl;

Tetris board1(15,15);

//board1.get_tetros().push_back(fazla_t);

	
	cout << " Enter the tetromino types " << endl;

	pre1_shape = 'L';
	
	board1.move(pre1_shape);
	
	board1.animate();
	
	board1.set_index(1);

cout << endl << endl << endl;

cout << endl << endl << endl;

for(int a = 0; a < 100; a++) cout << "%";

cout << endl << endl << endl;

cout << endl << "Tetris foksiyonlari calisiyor" << endl;

cout << endl << endl << endl;

for(int a = 0; a < 100; a++) cout << "%";


cout << endl << endl << endl;


return 0;

}


