

/**Due to a vertex has coordinates vertex class can help
*Also some implementation needs unıqe label for every vertex
*@author Tarsuslu
*/
public class Vertex{

	private int y;
	private int x;
	private int label;
	/**
	*@param a  y coordinate
	*@param b  x coordinate
	*@param c  label
	*/
	public Vertex(int a, int b, int c){
		
		y = a;
		x = b;
		label = c;
	}
	/**
	*@param a y coordinate
	*@param b x coordinate
	*/
	public Vertex(int a, int b){
		
		y = a;
		x = b;
	}
	/** compares the vertexes
	*@param v is the vertex which is going to be compared
	*@return true if x and y coordinates are equal
	*/
	public boolean equals(Vertex v){return (v.getX() == x && v.getY() == y);}
	/**getter for x
	*@return x coordinate
	*/
	public int getX(){return x;}
	/**getter for y
	*@return y coordinate
	*/
	public int getY(){return y;}
	/**getter for label
	*@return label
	*/
	public int getLabel(){return label;}
	/**setter for label
	*@param a is the new label
	*/
	public void setLabel(int a){label = a;}
	
}
