import java.util.List;
import java.util.ArrayList;
import java.util.Set;
import java.util.Map;
import java.util.LinkedHashMap;

/**MyMap class for holding map and str that is coming input
*@author Tarsuslu
*/
public class MyMap{

	private LinkedHashMap <String, Info> map;
	private int mapSize;
	private String str ;
	/**No parameter COnstructor
	*Constructor of MyMap creates empty LinkedHashMap object and a String
	*/
	public MyMap( ){
	
		map = new LinkedHashMap<String, Info>();
		mapSize = 0;
		str = new String();
	}

	/**
	*Constructor of MyMap creates empty LinkedHashMap object
	*str with preprocessed String
	*@param preprocessedString is the edited Input 
	*/
	public MyMap(String preprocessedString){
	
		map = new LinkedHashMap<String, Info>();
		mapSize = 0;
		str = preprocessedString;
		createMap();
	}
	
	/**
	*First It splits preprocessed String 
	*Then Every splitted Strings is examined one by one to be putted map
	*/
	public void createMap(){
		
		String[] temp = this.str.split(" ");
		for(int a = 0; a < temp.length; a++){
			putMap(temp[a]);
		}
	
	}
	/**
	*@param tempSt splitted string from createMap method
	*It looks char by char and puts to map if the char is not a key
	*Then pushes the word
	*It does not duplıcate keys but It pushes words to Info.words String array whenever it see the key
	*/
	public void putMap(String tempSt){
		
		for(int a = 0; a < tempSt.length(); a++){
			String ch = String.valueOf(tempSt.charAt(a));
			if(!map.containsKey(ch)){
				Info temp = new Info();
				map.put(ch,temp);
				mapSize++;
			}
			map.get(ch).push(tempSt);
		}	
	
	}
	/**
	*prints map according to given examples
	*/
	public void printMap(){
		
		Set<String> keySet = map.keySet();
		String[] keyArray = new String[keySet.toArray().length];
		for (int i=0;i<keySet.toArray().length;i++) keyArray[i]= keySet.toArray()[i].toString();
		
		for(int a = 0; a < keyArray.length; a++){
			Info inf = map.get(keyArray[a]);
			System.out.printf("\nLetter : %s - Count : %d - Words : [",keyArray[a],inf.getCount());
			String[] stArray = inf.getWords();
			for(int b = 0; b < inf.getCount(); b++) System.out.printf("%s ,",stArray[b]);
			System.out.printf("\b\b] ");
		}
	
	
	}
	
	/**getter 
	*@return mapsize
	*/
	public int getMapSize(){return mapSize;}
	/**getter 
	*@return string str
	*/
	public String getString(){return str;}
	/**getter 
	*@return map structure
	*/
	public LinkedHashMap<String,Info> getMap(){return map;}
	

}
