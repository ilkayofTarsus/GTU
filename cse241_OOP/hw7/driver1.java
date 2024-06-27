import java.util.Random;
import java.util.Scanner;

public class driver1{

	public static void main(String[] args){
			
		try{
				
			int row = 0, column = 0,sayac=0;
			int tetro_n=0, kaydirma=0, kay=0, donus_s=0;
			char pre_shape , donus;
			Random rand = new Random();
			int aralik;
			row = 20;
			column = row;
			Tetris board1 = new Tetris(row,column);
			board1.print_board();

			for(int runs = 0; runs < 3; runs++){
				
					pre_shape = 'O' ;
				
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
			
				Thread.sleep(500);
			}//while(!board1.is_finished());
		
			Tetromino obje1 = new Tetromino('S');
			Tetromino obje2 = new Tetromino('T');
				
			
				board1.add_tetro_tomap(obje1); // += obje;
				board1.print_board();

				donus_s = rand.nextInt()%4;
				String alphabet1 = "lr"	;
				donus = (alphabet1.charAt(rand.nextInt(alphabet1.length())));
				
				if(donus == 'l')
					for(int a = 0; a<donus_s; a++)
						obje1.rotate_l();

				if(donus == 'r') 
					for(int a = 0; a<donus_s; a++)
						obje1.rotate_r();
					
					
				board1.add_tetro_tomap(obje1);//+= obje;
				board1.print_board();
				donus_s = rand.nextInt(10) % (row/2-1);
				
				switch(donus){
					case 'l':
						for(int a=0; a<donus_s; a++) board1.kaydir_sola(obje1);
					break;
					case 'r':
						for(int a=0; a<donus_s; a++) board1.kaydir_saga(obje1);
					break;
				
				}
				board1.animate(obje1);
				Thread.sleep(500);
				
				board1.add_tetro_tomap(obje2); // += obje;
				board1.print_board();

				donus_s = rand.nextInt()%4;
				String alphabet2 = "lr"	;
				donus = (alphabet2.charAt(rand.nextInt(alphabet2.length())));
				
				if(donus == 'l')
					for(int a = 0; a<donus_s; a++)
						obje2.rotate_l();

				if(donus == 'r') 
					for(int a = 0; a<donus_s; a++)
						obje2.rotate_r();
					
					
				board1.add_tetro_tomap(obje2);//+= obje;
				board1.print_board();
				donus_s = rand.nextInt(10) % (row/2-1);
				
				switch(donus){
					case 'l':
						for(int a=0; a<donus_s; a++) board1.kaydir_sola(obje2);
					break;
					case 'r':
						for(int a=0; a<donus_s; a++) board1.kaydir_saga(obje2);
					break;
				
				}
				board1.animate(obje2);			
					

		}
		catch(InterruptedException e){
		
		
		
		}
	}

}
