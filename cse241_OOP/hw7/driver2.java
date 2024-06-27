import java.util.Random;
import java.util.Scanner;

public class driver2{

	public static void main(String[] args){
			
		try{
				
			int row = 0, column = 0,sayac=0;
			int tetro_n=0, kaydirma=0, kay=0, donus_s=0;
			char pre_shape , donus;
			Random rand = new Random();
			int aralik;
			Scanner inpt = new Scanner(System.in);

			System.out.printf("\n\n\n Give the size of Tetris board (row )\n"); //cout << endl << endl << endl << " Give the size of Tetris board (row )"<< endl;

			row = inpt.nextInt();

			column = row;
			Tetris board1 = new Tetris(row,column);
			board1.print_board();

			do{
				
				System.out.printf(" give the tetromino type\n");//cout << "give the tetromino type" << endl;

				do{
					pre_shape = inpt.next().charAt(0) ;
					
					if(pre_shape == 'R'){
						String alphabet = "TSLJZIO";
						pre_shape = (alphabet.charAt(rand.nextInt(alphabet.length())));
					}
					
					if(!board1.isLegal(pre_shape)) System.out.printf(" give the legal tetromino type \n"); //cerr << "Give the legal tetromno type" << endl;
				
				} while(!board1.isLegal(pre_shape));
				
				if(pre_shape == 'Q') break;	
				
				Tetromino obje = new Tetromino(pre_shape);
				
				board1.add_tetro_tomap(obje); // += obje;
				board1.print_board();

				donus_s = rand.nextInt()%4;
				String alphabet = "lr"	;
				donus = (alphabet.charAt(rand.nextInt(alphabet.length())));
				
				if(donus == 'l')
					for(int a = 0; a<donus_s; a++)
						obje.rotate_l();

				if(donus == 'r') 
					for(int a = 0; a<donus_s; a++)
						obje.rotate_r();
					
					
				board1.add_tetro_tomap(obje);//+= obje;
				board1.print_board();
				donus_s = rand.nextInt(10) % (row/2-1);
				
				switch(donus){
					case 'l':
						for(int a=0; a<donus_s; a++) board1.kaydir_sola(obje);
					break;
					case 'r':
						for(int a=0; a<donus_s; a++) board1.kaydir_saga(obje);
					break;
				
				}
				board1.animate(obje);
				if(board1.sil()) board1.print_board();	
			}while(!board1.is_finished());
			Thread.sleep(500);
		}
		catch(InterruptedException e){
		
		
		
		}
	}

}
