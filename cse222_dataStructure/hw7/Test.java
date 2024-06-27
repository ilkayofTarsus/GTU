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

		MyMap map = new MyMap(str);
		
		String bestCase,avarageCase,worstCase;
		bestCase = "a bb ccc dddd eeeee ffffff";
		avarageCase = "a bbb ccccc dd eeee fffffff";
		worstCase = "aaaaaa bbbbb cccc ddd ee f";
		
		bestCase = inf.preprocess(bestCase);
		avarageCase = inf.preprocess(avarageCase);
		worstCase = inf.preprocess(worstCase);
		
		MyMap bestMap, avarageMap, worstMap;
		bestMap = new MyMap(bestCase);
		avarageMap = new MyMap(avarageCase);
		worstMap = new MyMap(worstCase);
		
		
		//Merge Sort
		MergeSort bestMerge = new MergeSort(bestMap);
		MergeSort avarageMerge = new MergeSort(avarageMap);
		MergeSort worstMerge = new MergeSort(worstMap);
		
		System.out.printf("\n\nThe original worst:\n" );
		worstMap.printMap();	
		System.out.printf("\n\nThe worst Merge Sort:\n" );
		worstMerge.createSortedMap();
		worstMerge.getSortedMap().printMap();
		
		System.out.printf("\n\nThe original avarage:\n" );
		avarageMap.printMap();
		System.out.printf("\n\nThe avarage Merge Sort:\n" );
		avarageMerge.createSortedMap();
		avarageMerge.getSortedMap().printMap();
		
		System.out.printf("\n\nThe original best:\n" );
		bestMap.printMap();
		System.out.printf("\n\nThe best Merge Sort:\n" );
		bestMerge.createSortedMap();
		bestMerge.getSortedMap().printMap();
		
		//Bubble Sort
		BubbleSort bestBubble = new BubbleSort(bestMap);
		BubbleSort avarageBubble = new BubbleSort(avarageMap);
		BubbleSort worstBubble = new BubbleSort(worstMap);
		
		System.out.printf("\n\nThe original worst:\n" );
		worstMap.printMap();
		System.out.printf("\n\nThe worst Bubble Sort:\n" );
		worstBubble.createSortedMap();
		worstBubble.getSortedMap().printMap();

		System.out.printf("\n\nThe original avarage:\n" );
		avarageMap.printMap();
		System.out.printf("\n\nThe avarage Bubble Sort:\n" );
		avarageBubble.createSortedMap();
		avarageBubble.getSortedMap().printMap();
		
		System.out.printf("\n\nThe original best:\n" );
		bestMap.printMap();
		System.out.printf("\n\nThe best Bubble Sort:\n" );
		bestBubble.createSortedMap();
		bestBubble.getSortedMap().printMap();
		
		//Insertıon Sort
		InsertionSort bestInsertion = new InsertionSort(bestMap);
		InsertionSort avarageInsertion = new InsertionSort(avarageMap);
		InsertionSort worstInsertion = new InsertionSort(worstMap);
		
		System.out.printf("\n\nThe original worst:\n" );
		worstMap.printMap();
		System.out.printf("\n\nThe worst Insertion Sort:\n" );
		worstInsertion.createSortedMap();
		worstInsertion.getSortedMap().printMap();

		System.out.printf("\n\nThe original avarage:\n" );
		avarageMap.printMap();
		System.out.printf("\n\nThe avarage Insertion Sort:\n" );
		avarageInsertion.createSortedMap();
		avarageInsertion.getSortedMap().printMap();
		
		System.out.printf("\n\nThe original best:\n" );
		bestMap.printMap();
		System.out.printf("\n\nThe best Insertion Sort:\n" );
		bestInsertion.createSortedMap();
		bestInsertion.getSortedMap().printMap();
		
		//Selection Sort
		SelectionSort bestSelection = new SelectionSort(bestMap);
		SelectionSort avarageSelection = new SelectionSort(avarageMap);
		SelectionSort worstSelection = new SelectionSort(worstMap);
		
		System.out.printf("\n\nThe original worst:\n" );
		worstMap.printMap();
		System.out.printf("\n\nThe worst Selection Sort:\n" );
		worstSelection.createSortedMap();
		worstSelection.getSortedMap().printMap();

		System.out.printf("\n\nThe original avarage:\n" );
		avarageMap.printMap();
		System.out.printf("\n\nThe avarage Selection Sort:\n" );
		avarageSelection.createSortedMap();
		avarageSelection.getSortedMap().printMap();

		System.out.printf("\n\nThe original best:\n" );
		bestMap.printMap();
		System.out.printf("\n\nThe best Selection Sort:\n" );
		bestSelection.createSortedMap();
		bestSelection.getSortedMap().printMap();
		
		
		//Quıck Sort
		bestCase = "a bb cccc dddddd eeeee fff";
		avarageCase = "a bb ccc ddddd eeee ffffff";
		worstCase = "aaa bbbbb cccccc dddd ee f";
		bestMap = new MyMap(bestCase);
		avarageMap = new MyMap(avarageCase);
		worstMap = new MyMap(worstCase);
		
		QuickSort bestQuick = new QuickSort(bestMap);
		QuickSort avarageQuick = new QuickSort(avarageMap);
		QuickSort worstQuick = new QuickSort(worstMap);

		System.out.printf("\n\nThe original worst:\n" );
		worstMap.printMap();
		System.out.printf("\n\nThe worst Quick Sort:\n" );
		worstQuick.createSortedMap();
		worstQuick.getSortedMap().printMap();

		System.out.printf("\n\nThe original avarage:\n" );
		avarageMap.printMap();
		System.out.printf("\n\nThe avarage Quick Sort:\n" );
		avarageQuick.createSortedMap();
		avarageQuick.getSortedMap().printMap();
		
		System.out.printf("\n\nThe original best:\n" );
		bestMap.printMap();
		System.out.printf("\n\nThe best Quick Sort:\n" );
		bestQuick.createSortedMap();
		bestQuick.getSortedMap().printMap();
		
	}


}
