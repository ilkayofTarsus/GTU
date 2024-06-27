import java.lang.Thread;
import java.io.*;

/**
* Tetris class from previous homework
*<p>
*This class handles Tetris board issues
*</p>
*
* @author İlkay Bolat
* @since 21.01.2023
*/
public class Tetris{

	private char[][] board;
	private char[][] board_yedek;
	private int boy;
	private int en;
	private int harita_x;
	private int index;
	private int tetro_n;


	/**
	*<p>	
	*Constructor creates a Tetris board
	*</p>
	*
	* @param b represent row
	* @param e represent column
	*/
	public Tetris(int b,int e){
	
	boy = b;
	en = e;
	harita_x=0;
	index=0;
	tetro_n=0;
	
	board = new char[boy+2][boy+2];
	board_yedek = new char[boy+2][boy+2];
/*
	for(int i = 0; i < boy+2; i++){
		
		board[i] = new char[en+2];
		
	
	}

	
		board_yedek = new char*[boy+2];

		for(int i = 0; i < boy+2; i++){
			
			board_yedek[i] = new char[en+2];
			
		
		}
*/		

	for(int i=0; i<b+2; i++){

		for(int j =0; j<e+2; j++){
		
			if(i==0) {
			
				board[i][j] = '&' ;
				
				
				}		
			
			else if(j==0 || j== b+1) board[i][j] ='&' ;
			
			else if(i == e+1) board[i][j] = '&';
			
			else board[i][j] = ' ';
		
		}
	
	
	
	}
	
	}
	/**
	*<p>	
	*This class handles Tetromino issues
	*</p>
	*
	* @param sayi it is added on index
	*/
	public void set_index(int sayi) { index += sayi;}
	
	/**
	*<p>	
	*This method is responsible for animating tetrominos in tetris board
	*</p>
	*
	* @param obje it is a Tetromino that will be animated
	*/
	public void animate(Tetromino obje ){ //const func
	
	
	int kay = kaydirma_s(obje);
		
	 for(int a = 0; a < kay; a++){
		
		//Thread.sleep(220);
	try {
	    Thread.sleep(220);
	} 
	catch(InterruptedException e){
	
			
	
	}
		
		
	 	kaydir_asagi(obje);	

		System.out.printf("\033[H\033[2J");//cout << "\x1B[2J\x1B[H";

		print_board();

	}
	
	}
	/**
	*<p>	
	*This method eraseses tetrominos on board
	*</p>
	*
	*@return a boolean 
	*/
	public boolean sil(){
	
		boolean silme = true, ret = false;
		do{
			for(int a=1; a< en+1 ; a++){
				if(board[boy][a] == ' ') silme = false;
			}
			if(silme){
				ret = true;
				System.out.printf("\033[H\033[2J");
				for(int a=boy; a >2; a--){
					for(int b=1; b<en+1; b++ ){
						board[a][b] = board[a-1][b];
					}
				}
			for(int b=1; b<en+1; b++ ) board[1][b] = ' ';
			}
		}while(silme);
		
	return ret;
	
	
	}
	/**
	*<p>	
	*getter for row 
	*</p>
	*
	*@return give a int that represents row
	*/
	public int get_boy()  { return boy;} //const func
	/**
	*<p>	
	*getter for board
	*</p>
	*
	*@return give a 2 dimension char array that is tetris board
	*/
	public char[][] get_board(){ return board;}	//const func //cıktısı 2 boyutlu char vektor
	/**
	*<p>	
	*getter for column
	*</p>
	*
	*@return give a int that represents column
	*/
	public int get_en() { return en;} //const func
	/**
	*<p>	
	*getter for tetromino number 
	*</p>
	*
	*@return give a int that represents tetromino number
	*/
	public int get_tetron() {return tetro_n;}//const func
	/**
	*<p>	
	*getter for index
	*</p>
	*
	*@return give a int that represents index
	*/
	public int get_index() {return index;}	//const func
	
	/**
	*<p>	
	*prints the actual board
	*</p>
	*
	*/
	public void print_board(){
	
		for(int a=0; a<boy+2; a++){
			for(int b=0; b<en+2; b++){
				System.out.printf("%s",board[a][b]);//cout << board[a][b];
			}
		System.out.printf("\n");//cout << endl;
		}
	
	}				//const func			//print board
	
	
	
	/**
	*<p>	
	*this function is responsible to count how much empty location under the given object
	*</p>
	*
	*@param obje tetromino object to will be scrolled
	*
	*@return an integer to say counting
	*/
	public int kaydirma_s(final Tetromino obje){		//const func	// parametresi 2boyutlu char vektor		// asagıya ne kadar kaydırması gerektıgını bıldırır

		int kaydirma=99, kaydirma_y =0, kaydirma_y1 =0,kaydirma_y2 =0;

		for(int b = 1 ; b < boy+1 ; b++){
		
			for(int a = 1; a < 5; a++){
				
				if(board[a][b] == obje.get_symbol()){ // burası ve asasgısı
					
					kaydirma_y=0;
					kaydirma_y1 =0;
					kaydirma_y2 =0;	
					for(int c = a; c < boy+1; c++){
					
						if(board[c][b] == ' '){
						
						kaydirma_y++;
						
						}
						if(board[c][b+1] == ' ') kaydirma_y1++;
						
						
						if(board[c][b+1] != '&'){
						 	
						 	if( board[c][b+2] == ' ') kaydirma_y2++;
						
						}
					}	
				if(kaydirma_y2 < kaydirma_y1) kaydirma_y1 = kaydirma_y2; 
				if(kaydirma_y1 < kaydirma_y) kaydirma_y = kaydirma_y1; 
				if((kaydirma_y != 0) && (kaydirma_y < kaydirma)) kaydirma = kaydirma_y;
				
				}
			
			
			}
		
		}

		
		return kaydirma;

	}
	
	/**
	*<p>	
	*this function is responsible to scroll down
	*</p>
	*
	*@param obje tetromino object to be wanted to scroll down
	*/
	public void kaydir_asagi(final Tetromino obje){	//const func							// tetromınoyu kaydırır
		
	boolean kontrol = true;
	char temp;
	
		for(int a=1; a < en+1; a++ ){
			for(int b=1; b < boy+1; b++){
				temp = 'x';		
				if(board[b][a] == obje.get_symbol()){
					for(int c=b+1; c<boy+1; c++){
						if(board[c][a] == ' '){
								temp = board[c][a];
								board[c][a] = board[b][a];		
								board[b][a] = temp;
								temp = ' ';
						}
					}	
				}
				if(temp == ' ') break;
			}
		}	

	}
	//public void fit();									// yatayda dogru konumuna koyar 
	//public int calc_haritax();
//	public void add_tetro(char){								//tetromınolar tetrısın classının ıcınde tetromıno vektorune eklenir
	
	/**
	*<p>	
	*this function is responsible to add tetro to map
	*</p>
	*
	*@param tetrs tetrs is given by user
	*/
	public void add_tetro_tomap(final Tetromino tetrs){								// tetromınoları boardın ortasına ekler
		
		for(int a=1; a< 5; a++){
		
		for(int b =(en/2); b<(en/2 + 4) ; b++){
		
			board[a][b] = ' '; 
		
		}
	}



	for(int a=1; a< 5; a++){
		
		for(int b = (en/2); b < (en/2 + 4) ; b++){
		
			board[a][b] =  tetrs.get_vectorc( a-1 , b-(en/2) ); 
		
		}
	}


	}
	//public void rotate();
	
	/**
	*<p>	
	*this function is responsible to swipe left
	*</p>
	*
	*@param obje tetromino object to be wanted to swipe left
	*/
	public void kaydir_sola(final Tetromino obje){
		
	boolean kontrol = true;
	char temp;
		
	
		for(int a = 0; a<boy+2 ;a++){
		
			for(int b=0; b<en+2; b++){
			
			board_yedek[a][b] = board[a][b]; 
			
			
			}
		
		
		}
		
		for(int b=1; b < boy; b++){
		
			for(int a=en; a > 0 ; a-- ){
				
				temp = 'x';		
				
				if(board_yedek[b][a] == obje.get_symbol()){ 
				
					for(int c=a; c>0; c--){
						
						if(board_yedek[b][c] == ' ' ){
							
							temp = board_yedek[b][c];
							board_yedek[b][c] = board_yedek[b][a];		
							board_yedek[b][a] = temp;
							temp = ' ';
						
						}
					
					
					}	
					
				
				}
			
				
				if(temp == ' ') break;
			
			}
		
		
		}
		
		for(int a = 0; a<boy+2 ;a++){
		
			for(int b=0; b<en+2; b++){
			
			board[a][b] = board_yedek[a][b]; 
			
			
			}
		
		
		}
	
	
	}
	
	/**
	*<p>	
	*this function is responsible to swipe right
	*</p>
	*
	*@param obje tetromino object to be wanted to swipe right
	*/
	public void kaydir_saga(final Tetromino obje){
	
	boolean kontrol = true;
	char temp;
		
		for(int a = 0; a<boy+2 ;a++){
		
			for(int b=0; b<en+2; b++){
			
			board_yedek[a][b] = board[a][b]; 
			
			
			}
		
		
		}
		
		

		for(int b=1; b < 5; b++){
		
			for(int a=1; a < en; a++ ){
				
				temp = 'x';		
					
				if(board_yedek[b][a] == obje.get_symbol()){ // burası ve asgısı
				
					for(int c=a; c<en+1; c++){
					
						if(board_yedek[b][c] == ' ' ){
							
							temp = board_yedek[b][c];
							board_yedek[b][c] = board_yedek[b][a];		
							board_yedek[b][a] = temp;
							temp = ' ';
						
						}
					
					
					}	
					
				
				}
			
				
				if(temp == ' ') break;
			
			}
		
		
		}
		
		for(int a = 0; a<boy+2 ;a++){
		
			for(int b=0; b<en+2; b++){
			
			board[a][b] = board_yedek[a][b]; 
			
			
			}
		
		
		}
	
	}
	/**
	*<p>	
	*checks the given char is whether appropriate
	*</p>
	*
	*@param pre_shape it is a tetromino type
	*@return a boolean for given char
	*/
	public boolean isLegal(char pre_shape){
	
		return (pre_shape == 'T' || pre_shape == 'I' || pre_shape == 'O' || pre_shape == 'Z'|| pre_shape == 'S'|| pre_shape == 'J'|| pre_shape == 'L' || pre_shape == 'Q');
	
	}
	
	/**
	*<p>	
	*is_finished funcıton for tetris board
	*</p>
	*
	*@return a boolean that checks the game whether is finished or not
	*/
	public boolean is_finished(){
	
		boolean finished = false;

		for(int a = 1; a < 5; a++ ){
		
			for(int b = 1; b < en + 1 ; b++){
			
						
			if( board[a][b] != ' ') finished = true;		
			
			
			}
		
		}

	return finished;

	}
	
	//}


	public static void main(String[] args){}

}
