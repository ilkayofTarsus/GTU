import java.util.List;
import java.util.ArrayList;
import java.util.Set;
import java.util.Map;
import java.util.LinkedHashMap;

/**BubbleSort class for sorting by bubble sort algorithm
*@author Tarsuslu
*/
public class BubbleSort{


	private MyMap originalMap;
	private MyMap sortedMap;
	private String[] aux;


	/**
	*@param original is the original MyMap object will not be edited
	*Inıtıalizes original map with parameter
	*creates sortedMap 
	*and Inıtıalızes aux without sorted
	*/
	public BubbleSort(MyMap original){
	
		originalMap = original;
		sortedMap = new MyMap();
		aux = new String[original.getMapSize()];
		Set<String> keySet ;
		keySet = original.getMap().keySet();
		for (int i=0;i<keySet.toArray().length;i++) aux[i] = keySet.toArray()[i].toString();
	}
	
	/**
	*It sorts auxCounts int array and aux String array with same time by bubble sort algorithm
	*Then puts the keys and its values according to sorted aux string array
	*/
	public void createSortedMap(){
		
		int[]auxCounts = new int[aux.length];
		for(int a = 0; a < aux.length; a++){
			Info inf = originalMap.getMap().get(aux[a]);		
			auxCounts[a] = inf.getCount();
		}
		long start = System.nanoTime();
		bubbleSort(auxCounts);
    		long end = System.nanoTime();
    		System.out.println("running time -> " + (end - start));
		for(String a : aux){
			Info tempInf = originalMap.getMap().get(a);
			LinkedHashMap<String,Info> mp = sortedMap.getMap();
			mp.put(a,tempInf);
		}
	}
	
	/**sorts with bubble sort algoırthm
	*@param auxCounts is count values of element of aux string array
	*
	*/
	public void bubbleSort(int[] auxCounts){
			
			boolean kontrol = false;
			for(int a = 0; a < originalMap.getMapSize()-1;a++){
				kontrol = false;
				for(int b = 0; b < originalMap.getMapSize()-1-a ;b++){
					
					if(auxCounts[b] > auxCounts[b+1]){
						kontrol = true;
						String tempString = aux[b];					
						aux[b] = aux[b+1];
						aux[b+1] = tempString;
						
						int tempInt = auxCounts[b];
						auxCounts[b] = auxCounts[b+1];
						auxCounts[b+1] = tempInt;						
					}				
			
				}
			if(!kontrol) break;
			}
	}
	
	/**getter 
	*@return aux string array
	*/
	public String[] getAux(){return aux;}
	/**getter
	*@return sorted MyMap object
	*/
	public MyMap getSortedMap(){return sortedMap;}
	/**getter
	*@return original, not editedi MyMap object
	*/
	public MyMap getOriginalMap(){return originalMap;}


}
