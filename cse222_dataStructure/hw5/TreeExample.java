import javax.swing.*;  
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreeNode;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Queue;
import java.util.Stack;
import java.util.LinkedList;
import java.util.Scanner;

/**
*@author ilkay
*/
public class TreeExample {  
	
	/**
	@throws FileNotFoundException if file is not found
	@param arr will be filled strings from tree.txt
	@return filled array
	*/
	public static String[][] fillArray(String[][] arr) throws FileNotFoundException{
		
		File dosya = new File("tree.txt");
		Scanner scan = new Scanner(dosya);
		String line = new String();
		String[] splitArr = new String[8];
		int i1=0,i2=0;
		while(scan.hasNextLine()){
			line = scan.nextLine();
			splitArr = line.split(";");
			if(i1 == arr.length) arr = reallocRow(arr,i1);
			
			for(int a = 0 ; a < splitArr.length; a++){
				if(i2 == arr[0].length) arr = reallocColumn(arr,i2);
				arr[i1][i2] = splitArr[i2];	

			i2++;
			}
		i1++;
		i2 = 0;
		}
	scan.close();
	return arr;
	}
	
	/**
	@param arr array which is going to be larger two time for row
	@param rowCapacity is going to be larger two times 
	@return reallocated array
	*/
	public static String[][] reallocRow(String[][] arr, int rowCapacity){
		String[][] newArr = new String[rowCapacity*2][arr[0].length];
		for(int a = 0 ; a < rowCapacity; a++){
			for(int b = 0 ; b < arr[0].length; b++){
			newArr[a][b] = arr[a][b];
			}
		}
	return newArr;	
	}
	
	/**
	@param arr array which is going to be larger two time for column
	@param columnCapacity is going to be larger two times 
	@return reallocated array
	*/
	public static String[][] reallocColumn(String[][] arr, int columnCapacity){
		String[][] newArr = new String[arr.length][columnCapacity*2];
		for(int a = 0 ; a < arr.length; a++){
			for(int b = 0 ; b < columnCapacity; b++){
			newArr[a][b] = arr[a][b];
			}
		}
	return newArr;	
	}
	
	/**
	*main method
	*@param args main parameter
	*/	
	public static void main(String[] args) {  
		try{
			System.out.printf("\nFilling array and making tree from array for Part A\n");
			String[][] arr = new String[2][2];
			String arann = new String();
			String year = new String();
			DefaultMutableTreeNode root,aranan,b;
			arr = fillArray(arr);
			Tree trot = new Tree(arr);
			trot.makeTree(arr);
			trot.showTree();

			System.out.printf("\n\nPart B\n");		
			Scanner scan = new Scanner(System.in);
			System.out.printf("\nEnter the input:\n");
			arann = scan.nextLine();
			aranan = new DefaultMutableTreeNode(arann);
			trot.partB(aranan,0);
			
			System.out.printf("\n\nPart C\n");
			trot.partC(aranan,0);
			
			System.out.printf("\n\nPart D\n");
			trot.partD(aranan,0);

			System.out.printf("\n\nPart E \n");
			System.out.printf("\nWhat part do you want to transfer (Form must be : Year-Lesson-LECTURE ....):\n");
			arann = scan.nextLine();
			System.out.printf("\nWhat year do you want to add this part:\n");
			year = scan.nextLine();
			trot.partE(arann,year);
			trot.showTree();
			scan.close();
		}

		catch(Exception e){
			System.out.printf(e.getMessage());
		}


	}
}  
