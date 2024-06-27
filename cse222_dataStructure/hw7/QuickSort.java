import java.util.List;
import java.util.ArrayList;
import java.util.Set;
import java.util.Map;
import java.util.LinkedHashMap;

/**QuickSort class for sorting by Quick sort algorithm
*@author Tarsuslu
*/
public class QuickSort{

	private MyMap originalMap;
	private MyMap sortedMap;
	private String[] aux;
	
	/**
	*@param original is the original MyMap object will not be edited
	*Inıtıalizes original map with parameter
	*creates sortedMap 
	*and Inıtıalızes aux without sorted
	*/
	public QuickSort(MyMap original){
	
		originalMap = original;
		sortedMap = new MyMap();
		aux = new String[original.getMapSize()];
		Set<String> keySet ;
		keySet = original.getMap().keySet();
		for (int i=0;i<keySet.toArray().length;i++) aux[i] = keySet.toArray()[i].toString();
	}
	
	/**
	*It sorts auxCounts int array and aux String array with same time by Quick sort algorithm
	*Then puts the keys and its values according to sorted aux string array
	*/
	public void createSortedMap(){
		
		int[]auxCounts = new int[aux.length];
		for(int a = 0; a < aux.length; a++){
			Info inf = originalMap.getMap().get(aux[a]);		
			auxCounts[a] = inf.getCount();
		}
		long start = System.nanoTime();
		quickSort(auxCounts,0,auxCounts.length-1);
    		long end = System.nanoTime();
    		System.out.println("running time -> " + (end - start));
		for(String a : aux){
			Info tempInf = originalMap.getMap().get(a);
			LinkedHashMap<String,Info> mp = sortedMap.getMap();
			mp.put(a,tempInf);
		}
	}
	
	/**sorts with quıck sort algoırthm
	*@param auxCounts is count values of element of aux string array
	*@param min quıck sort is a divide and conquer method so min is min index of subarray
	*@param max is max index of subarray
	*/
	public void quickSort(int[] auxCounts,int min, int max){
		
		if(min >= max) return;
		int i = min-1;
		int j =	min;
		while(j < max){
			if(auxCounts[j] <= auxCounts[max]){
				i++;
				int tempInt = auxCounts[j];
				auxCounts[j] = auxCounts[i];
				auxCounts[i] = tempInt;
				
				String tempString = aux[j];
				aux[j] = aux[i];
				aux[i] = tempString;
				
			}
		j++;
		}	
	
		i++;
		int tempInt = auxCounts[i];
		auxCounts[i] = auxCounts[max];
		auxCounts[max] = tempInt;
			
		String tempString = aux[i];
		aux[i] = aux[max];
		aux[max] = tempString;
		quickSort(auxCounts,min,i-1);		
		quickSort(auxCounts,i+1,max);
		
			
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
