/**
* Tetromino class from previous homework
*<p>
*This class handles Tetromino issues
*</p>
*
* @author İlkay Bolat
* @since 21.01.2023
*/
public class Tetromino{
	private	char symbol;
	private	char[][] tetro_v;
	private	char[][] tetro_yedek;

	/**
	*<p> This method is responsible for printing tetrominos individually</p>
	*/
	public  void print_tet(){
		for(int a=0; a<4; a++){
		
			for(int b=0; b<4; b++){
			
			System.out.printf("%s", tetro_v[a][b]); //cout << tetro_v[a][b];
			
			
			}
		
		System.out.printf("\n"); //cout << endl;
		
		}
	
	
	}
	
	/**
	*<p> Constructor is responsible to create a 2d char array</p>
	*@param symbol says what kind of char Tetrominos is
	*/
	public  Tetromino( char symbol){

	tetro_v = new char[4][4];
	tetro_yedek = new char[4][4];
	
	set_symbol(symbol);
	
	
	switch(symbol){
		
			case ('I'):
			
				for(int i=0;i<4;i++){
				
					for(int j=0;j<4;j++){
					
						if(3==i){
							tetro_v[i][j]='I';
						}
						
						else
							tetro_v[i][j]=' ';
					}
				}
			break;
				
			case ('O'):
			
				for(int i=0;i<4;i++){
				
					for(int j=0;j<4;j++){
					
						if( ((2==i || 3==i) && (0==j || 1==j)) ){
							tetro_v[i][j]='O';
						}
						
						else
							tetro_v[i][j]=' ';
					}
				}
			break;
			
			case ('T'):
			
				for(int i=0;i<4;i++){
				
					for(int j=0;j<4;j++){
					
						if( (2==i && (0==j || 1==j || 2==j)) || (3==i && 1==j) ){
							tetro_v[i][j]='T';
						}
						
						else
							tetro_v[i][j]=' ';
					}
				}
			break;
				
			case ('J'):
			
				for(int i=0;i<4;i++){
				
					for(int j=0;j<4;j++){
					
						if( (1==j && (1==i || 2==i || 3==i)) || (3==i && 0==j) ){
							tetro_v[i][j]='J';
						}
						
						else
							tetro_v[i][j]=' ';
					}
				}
			
			break;
				
			case ('L'):
				
				for(int i=0;i<4;i++){
				
					for(int j=0;j<4;j++){
					
						if( (0==j && (1==i || 2==i || 3==i)) || (3==i && 1==j) ){
							tetro_v[i][j]='L';
						}
						
						else
							tetro_v[i][j]=' ';
					}
				}
			
			break;
			
			case ('S'):
			
				for(int i=0;i<4;i++){
			
					for(int j=0;j<4;j++){
					
						if( (2==i && (1==j || 2==j)) || (3==i && (0==j || 1==j)) ){
							tetro_v[i][j]='S';
						}
						
						else
							tetro_v[i][j]=' ';
					}
				}
			
			break;
			
			case ('Z'):
			
				for(int i=0;i<4;i++){
				
					for(int j=0;j<4;j++){
					
						if( (2==i && (0==j || 1==j)) || (3==i && (1==j || 2==j)) ){
							tetro_v[i][j]='Z';
						}
						
						else
							tetro_v[i][j]=' ';
					}
				}
			
			break;	
		
		}	
	

	}
	/**
	*<p> This method is responsible to say type of char </p>
	*@param a first dimension of array
	*@param b second dimension of array
	*@return the char in this location
	*/
	public	char get_vectorc(int a , int b){return tetro_v[a][b]; }//const func
	
	/**
	*<p> This method is responsible for changing symbol of tetrominos </p>
	*@param a new symbol
	*/
	public	void set_symbol(char a) { symbol = a; }
	
	/**
	*<p> This method is responsible for printing tetrominos individually</p>
	*@param v represents a Tetromino in 2d char array
	*@param inc responsible for loop
	*/
	public	void print_s(char[][] v , int inc){//const func

		for(int a=0 ;a<4 ;a++){
			for(int b =0 ;b<4+inc ;b++){
				System.out.printf("%s", v[a][b]); //cout <<v[a][b] ;
			}
				
			System.out.printf("\n"); //cout<< "\n";	
		
		}
	}
	/**
	*<p> This method is responsible for returning Tetrominos</p>
	*/
	public	void rotate_l() {
		for(int a=0; a< 4; a++){
			for(int b =0; b<4 ; b++){
				tetro_yedek[a][b] = tetro_v[a][b];			
			}
		}	

 		bosluk_doldur();
 				for(int a=0; a<4; a++) {
					for(int b=0; b<4; b++){
							tetro_v[b][a] = tetro_yedek[a][3-b];
					}
				}
 			asagi_kaydir();
 			sola_kaydir();
	}
	
	/**
	*<p> This method is responsible for getting symbol of tetromino</p>
	*@return getter functon
	*/
	public	char get_symbol(){ return symbol; }//const func


	/**
	*<p> This method is responsible for rotating tetromino</p>
	*/
	public	void rotate_r(){
		for(int a=0; a< 4; a++){
			for(int b =0; b<4 ; b++){
				tetro_yedek[a][b] = tetro_v[a][b];			
			}
		}
 		bosluk_doldur();
 				for(int a=0; a<4; a++) {
					for(int b=0; b<4; b++){
							tetro_v[b][a] = tetro_yedek[3-a][b];
					}
				}
 			asagi_kaydir();
 			sola_kaydir();
	
	}
	
	
//	private	void yedek_guncelle();
	
	/**
	*<p> This method is responsible for scrolling Tetrominos down</p>
	*@return boolean that says whether succesfully or not
	*/
	private	boolean asagi_kaydir(){
	
		boolean ret_d = true;
		
		do{
			for(int a=0; a<4; a++) {
				if(tetro_v[3][a] != ' ') ret_d = false;
			
			}

			if(ret_d){
				for(int b=3; b>=0; b--) {
						for(int a=0; a<4; a++){
								if(b>0) tetro_v[b][a] = tetro_v[b-1][a];
								else tetro_v[b][a] = ' ';
						}
				}
			}
			
		}while(ret_d);
	
		return ret_d;
	
	}
	/**
	*<p> This method is responsible for scrolling Tetrominos left</p>
	*@return boolean that says whether succesfully or not
	*/
	private	boolean sola_kaydir(){
	
		boolean ret_d = true;
		
		do{
		
			for(int a=0; a<4; a++) {
			
				if(tetro_v[a][0] != ' ') ret_d = false;
			
			
		}
			
			if(ret_d){
			
				for(int a=0; a<4; a++) {
						
						for(int b=0; b<4; b++){
							
								if(a<(3)) tetro_v[b][a] = tetro_v[b][a+1];
			
								else tetro_v[b][a] = ' ';
						}
					
				}
			}
			
		}while(ret_d);
	
		return ret_d;
	
	
	}
	
	/**
	*<p> This method is responsible for filling the empty locations with ' '</p>
	*/
	private	void bosluk_doldur(){
	
		for(int a=0;a<4;a++){
			
			for(int b=0; b<4; b++){
				
				tetro_v[a][b]= ' ';
			
			}
		
		
		}
	
	}


}
