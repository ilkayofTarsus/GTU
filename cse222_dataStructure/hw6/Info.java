import java.util.List;
import java.util.ArrayList;
import java.util.Set;
import java.util.Map;
import java.util.LinkedHashMap;

/**Info class for Holding words with frequency to represent value of LinkedHasMap
*@author Tarsuslu
*/
public class Info{

	private int count;
	private String [] words;
	private int capacity;
	/**
	*constructor initializes count to 0 
	*creates String array object which name is words and holds capacity for String array
	*/
	public Info(){
		count = 0;
		words = new String[0];	
		capacity = 0; 
	}
	
	/**it does reallocaitn if it is needed
	*@param str a single str to be added words 
	*
	*/
	public void push(String str){
				if(capacity == count ) realloc();				
				words[count] = str ;
				count++;
	}
	
	/**
	*It does reallocation for words
	*every calls causes getting big for 5 
	*/
	public void realloc(){
	
		String [] temp = new String[count+5];
		
		for(int a = 0 ; a < count ; a++){
		
			temp[a] = words[a];
		}
		words = temp;
		capacity += 5;		
	}
	/**
	*@param str is the given input
	*@return str is the preprocessed string according to given rule
	* return null is a error handling
	*/
	public String preprocess(String str){
	
		str = str.toLowerCase();
		str = str.replaceAll("[^a-z \s]","");
		if(str.length() == 0 ){
		System.out.printf("Error: After the preprocess lenght of String is zero");	//Error handling
		return null;
		}		
		
		return str;
	}

	/**getter for count
	*@return count value
	*/
	public int getCount()	{	return count;	}
	/**getter for words
	*@return string array words
	*/
	public String[] getWords(){	return words; 	}
}
