import java.util.*;
import java.io.*;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;


/**
*@author Tarsuslu
*/
public class CSE222MAP{
	
	private Vertex startingPoint;
	private Vertex endingPoint;
	private String[][] map;
	private ArrayList<Vertex> vertexes;
	private int numV;
	
	/**constructor of CSE222MAP
	*@param scan is the scanner object which is responsible to scan input map 
	*@param Y is the size of row
	*@param X is the size of column
	*/
	public CSE222MAP(Scanner scan, int Y, int X)throws Exception{
		
		String[] st = scan.nextLine().split(",");
		startingPoint = new Vertex(Integer.parseInt(st[0]),Integer.parseInt(st[1]));
		st = scan.nextLine().split(",");
		endingPoint = new Vertex(Integer.parseInt(st[0]),Integer.parseInt(st[1])) ;	
		map = new String[Y][X];
		vertexes = new ArrayList<Vertex>();
		numV = fillMap(scan);
		if(map[startingPoint.getY()][startingPoint.getX()].equals("1")) throw new Exception("starting point 1!!!");
		if(map[endingPoint.getY()][endingPoint.getX()].equals("1")) throw new Exception("ending point 1!!!");
	}
	
	/**method to convert txt map file to png file
	*@param nm is the name of map Code needs to this parameter due to seperate png files for every map
	*@param type is the algortihm name. This is used to put the png files to correct directory
	*/
	public void toPng(String nm, String type)throws Exception{
		String pngFilePath =  "pngMaps/" + type + "Maps/" + nm + ".png";
		int width = map[0].length; 
		int height = map.length; 
		    BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
		    for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
			    String pixelChar = map[y][x];
			    int color = (pixelChar.equals("1")) ? 0xFFFFA500 : 0xFFFFFFFF; 
			    image.setRGB(x, y, color);
			}
		    }

		    ImageIO.write(image, "png", new File(pngFilePath));
	}
	/**method to draw feasible paths to png files
	*@param line is the vertex list which has feasible way to ending point
	*@param nm is the name of map Code needs to this parameter due to seperate png files for every map
	*@param type is the algortihm name. This is used to put the png files to correct directory
	*/	
	public void drawLine(ArrayList<Vertex> line,String nm, String type)throws Exception{
	
		String imageFile = "pngMaps/" + type + "Maps/" + nm + ".png";
		int colorRGB = 0xFFAA0000; 
		for(Vertex v : line){
		    BufferedImage image = ImageIO.read(new File(imageFile));
		    image.setRGB(v.getX(), v.getY(), colorRGB);
		    ImageIO.write(image, "PNG", new File(imageFile));
		}
	}
		
	/**method to fill map from txt file and specify vertexes to vertexes ArrayList
	*@param scan is the scanner object to scan txt file for filling map
	*@return number of vertexes
	*/
	public int fillMap(Scanner scan)throws Exception{
		int sayac = 0,sayac3 = 0 ;
		String st;
		String[] st2;
		while(scan.hasNext()){
			st = scan.nextLine();
			st2 = st.split(",");
			for(int a = 0; a < st2.length; a++){
				
				map[sayac][a] = st2[a];
				if(st2[a].equals("0")){
					Vertex nVert = new Vertex(sayac,a,sayac3);
					vertexes.add(nVert);
					sayac3++;
					if(startingPoint.equals(nVert)) startingPoint = nVert;
					if(endingPoint.equals(nVert)) endingPoint = nVert;
				}

			}
			sayac++;
		}
		
		return sayac3;
			
	}
	/**method to write path to txt file coordinate o coordinate
	*@param path includes vertexes which constructs feasible way to end
	*@param mp is the name of map Code needs to this parameter due to seperate txt files for every map
	*@param type is the algortihm name. This is used to put the png files to correct directory
	*/
	public void writePath(List<Vertex> path,String type,String mp)throws Exception{
		File file = new File("paths/" + type +"/" + mp + "Path.txt");
		if (!file.exists()) {
			file.createNewFile();
		}

		FileWriter fileWriter = new FileWriter(file, false);
		BufferedWriter bWriter = new BufferedWriter(fileWriter);
		for(Vertex v: path){
			bWriter.write(v.getY() + "," + v.getX() + "\n");
		}
		bWriter.close();
	
	}
	/**getter for starting point
	*@return starting point of map
	*/
	public Vertex getStarting(){ return startingPoint;}
	/**getter for ending point
	*@return ending point of map
	*/
	public Vertex getEnding(){ return endingPoint;}
	/**getter for vertexes arraylist
	*@return vertexes
	*/
	public ArrayList<Vertex> getVertexes(){ return vertexes;}
	/**getter for map array
	*@return map
	*/
	public String[][] getMap(){ return map;}
	/**getter for number of vertex
	*@return number of vertex
	*/
	public int getNumV(){ return numV;}

}
