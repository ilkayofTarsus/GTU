import java.util.List;
import java.util.ArrayList;
import java.util.Set;
import java.util.Map;
import java.util.LinkedHashMap;

/**MergeSort class for sorting by merge sort algorithm
*@author Tarsuslu
*/
public class MergeSort{

	private MyMap originalMap;
	private MyMap sortedMap;
	private String[] aux;
	
	/**
	*@param original is the original MyMap object will not be edited
	*Inıtıalizes original map with parameter
	*creates sortedMap 
	*and Inıtıalızes aux without sorted
	*/
	public MergeSort(MyMap original){
	
		originalMap = original;
		sortedMap = new MyMap();
		aux = new String[original.getMapSize()];
		Set<String> keySet ;
		keySet = original.getMap().keySet();
		for (int i=0;i<keySet.toArray().length;i++) aux[i] = keySet.toArray()[i].toString();
	}
	
	/**
	*It sorts auxCounts int array and aux String array with same time by merge sort algorithm
	*Then puts the keys and its values according to sorted aux string array
	*/
	public void createSortedMap(){
		
		int[]auxCounts = new int[aux.length];
		for(int a = 0; a < aux.length; a++){
			Info inf = originalMap.getMap().get(aux[a]);		
			auxCounts[a] = inf.getCount();
		}
		mergeSort(auxCounts,0,aux.length-1);
		for(String a : aux){
			Info tempInf = originalMap.getMap().get(a);
			LinkedHashMap<String,Info> mp = sortedMap.getMap();
			mp.put(a,tempInf);
		}
	}
	/**
	*@param auxCounts is count values of element of aux string array
	*@param first is a index for subarray's first index
	*@param last is a index for subarray's last index
	*/
	public void mergeSort(int[] auxCounts,int first, int last){
		
			if(first >= last) return;
			
			int middle = (last+first)/2;
			mergeSort(auxCounts,first,middle);
			mergeSort(auxCounts,middle+1,last);
			merge(auxCounts,first,middle,last);

	} 

	/** It applies standart mergesort algortihm but It includes also String array. Strng array update whenever auxCounts updates
	*@param auxCounts is count values of element of aux string array. Sorting is handled according to this
	*@param first  is a index for subarray's first index
	*@param middle  is a index for subarray's middle index
	*@param last  is a index for subarray's last index
	*/
	public void merge(int[] auxCounts,int first, int middle ,int last){
			
			int index1 = middle - first + 1;
			int index2 = last - middle;

			String[] LS =new String[index1];
			String[] MS =new String[index2];

			for(int a = 0; a < index1; a++) LS[a] = aux[first + a];
			for(int a = 0; a < index2; a++) MS[a] = aux[middle+1+a];

			int[] L = new int[index1];
			int[] M = new int[index2];
			
			for(int a = 0; a < index1; a++) L[a] = auxCounts[first+a];
			for(int a = 0; a < index2; a++) M[a] = auxCounts[middle+1+a];
			
			int counter1 = 0 , counter2 = 0, arrayCounter = first;
			
			while(counter1 < index1 && counter2 < index2){
				
				if(L[counter1] <= M[counter2]){
					aux[arrayCounter] = LS[counter1];
					auxCounts[arrayCounter] = L[counter1];
					counter1++;
				}	
				else{
					aux[arrayCounter] = MS[counter2];
					auxCounts[arrayCounter] = M[counter2];
					counter2++;					
				}
				arrayCounter++;			
			}
			while(counter1 < index1){
				aux[arrayCounter] = LS[counter1];
				auxCounts[arrayCounter] = L[counter1];
				counter1++;
				arrayCounter++;		
			}
			
			while(counter2 < index2){
				aux[arrayCounter] = MS[counter2];
				auxCounts[arrayCounter] = M[counter2];
				counter2++;
				arrayCounter++;
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
