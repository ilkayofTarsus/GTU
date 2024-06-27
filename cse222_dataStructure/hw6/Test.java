import java.util.List;
import java.util.ArrayList;
import java.util.Set;
import java.util.Map;
import java.util.LinkedHashMap;

/**Test class for testing methods and other class
*@author Tarsuslu
*/
public class Test{
	
	/**main method
	*@param args usual main parameter
	*/
	public static void main(String [] args){
	
		//Step 1	
		String str = new String();
		Info inf = new Info();
		str = "Buzzing bees buzz";
		System.out.printf("\nOriginal string : \t" + str);
		str = inf.preprocess(str);
		inf.push(str);
		System.out.printf("\nPreprocessed string : \t" + str);
		
		//Step 2
		System.out.printf("\n\nOriginal (Unsorted) Map: \n");
		MyMap map = new MyMap(str);
		map.printMap();
		
		//Step 3
		MergeSort ms = new MergeSort(map);
		ms.createSortedMap();
		System.out.printf("\n\nThe Sorted Map:\n" );
		ms.getSortedMap().printMap();
		
	}


}
