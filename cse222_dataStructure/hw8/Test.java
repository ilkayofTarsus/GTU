import java.util.*;
import java.io.*;


/**Test class
*@author Tarsuslu
*/
public class Test{


	/**
	*main method
	*@param args main param args
	*/
	public static void main(String[] args){
	
		try{
			String mapName,X,Y,fullName;
			Scanner scan1 = new Scanner(System.in);
			System.out.printf("\ngive the map name :(without file extention name  example: map01)");
			mapName = scan1.nextLine();
			fullName = "TextFiles/"+mapName + ".txt";
			System.out.printf("\ngive the row length :");
			Y = scan1.nextLine();
			System.out.printf("\ngive the cloumn length :");
			X = scan1.nextLine();		
			scan1.close();	
			
	
			File file = new File(fullName);
			Scanner scan = new Scanner(file);
	
			CSE222MAP map = new CSE222MAP(scan,Integer.parseInt(Y),Integer.parseInt(X));
			scan.close();
			CSE222GRAPH g = new CSE222GRAPH(map);
			CSE222DIJKSTRA dj = new CSE222DIJKSTRA(g);
 			
 			long startTime,endTime,total;
 			
 			startTime = System.currentTimeMillis();
 			ArrayList<Vertex> dijkLine = dj.Dijkstra();
			endTime = System.currentTimeMillis();
			total = endTime - startTime;
			System.out.printf("\ndijk hız = " + total/1000 + " seconds" );
			map.toPng(mapName,"dijk");
			map.drawLine(dijkLine,mapName,"dijk");
			map.writePath(dijkLine,"dijk",mapName);
 			System.out.printf("\nDijkstra pngMap created /pngMaps/dijkMaps/"+mapName+".png");
 			System.out.printf("\nDijkstra path created /paths/dijk/"+mapName+"Path.txt"+"\n");
 			
 			CSE222BFS bfs = new CSE222BFS(g);
 			startTime = System.currentTimeMillis();
 			ArrayList<Vertex> bfsLine = bfs.BFSAlgorithm();
			endTime = System.currentTimeMillis();
			total = endTime - startTime;
			System.out.printf("\nbfs hız = " + total + " milliseconds");
			map.toPng(mapName,"bfs");
			map.drawLine(bfsLine,mapName,"bfs");
 			map.writePath(bfsLine,"bfs",mapName);
			System.out.printf("\nBFS pngMap created /pngMaps/bfsMaps/"+mapName+".png");
 			System.out.printf("\nBFS path created /paths/bfs/"+mapName+"Path.txt"+"\n");
 			
 			System.out.printf("\nDijkstra path : %f", dj.length);
 			System.out.printf("\nBFS path : %f",bfs.length);
 			
			
			
		}
		catch(Exception e){
		
			System.out.printf(e.toString());
		
		}
	}




}
