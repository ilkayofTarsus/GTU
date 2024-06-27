#include<iostream>
#include<vector>
#include "Tetromino.h" 
#include "Tetromino.cpp"
using namespace std;

	
	
	
int main(){

int tetro_n=0,sayac=0, dondu=0;
char pre_shape;
bool ab;

vector <char> shapes;

Tetromino fazla_t(static_cast<tetro_shapes>('O'));				// ASIM HATASI OLMASIN DIYE FAZLADAN BIR OBJECT

cout << "HOW MANY TETROS" << endl;
cin >> tetro_n;

vector<vector<char>> sonuc (4,vector<char>(tetro_n*4));

vector <Tetromino> tetrominos;							// TETROLARIN TUTULDUGU TETRO CINSLI VEKTOR

cout << "WHAT ARE THE TYPES" << endl;

	for (int a=0; a< tetro_n; a++){

		cin >> pre_shape;		
		tetrominos.push_back(static_cast<tetro_shapes>(pre_shape));	// SECILEN KARAKTERLERE GORE ENUM YAPISINI ARA BASAMAK OLARAK KULLANARAK YENI OBJELER YAPILIYOR

	}

cout << "YOUR TETROMINOS : " << endl;
		
for (int a=0; a< tetro_n; a++) {
	
	tetrominos[a].print_s(tetrominos[a].get_vector(),0);

	cout << endl;
}
tetrominos.push_back(fazla_t);							// FAZLALIK OBJE VEKTORE EKLENIYOR

cout << "HORIZONTALLY BEST-FIT TETROS" << endl; 

sonuc = tetrominos[0].best_fit(tetrominos,sonuc,sayac,tetro_n);			// CANFITI ICINDE BARINDIRAN BEST FIT FONKSIYONU... BEST FITI BULUP ONA GORE YAN YANA DIZER

tetrominos[0].print_s(sonuc,tetro_n*4-4);					// SONUC HARITASI BASTIRILIR
return 0 ;
}
