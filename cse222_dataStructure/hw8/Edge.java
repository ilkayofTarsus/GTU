


/**Edge class includes source vertex, destination vertex and weight
*@author Tarsuslu
*/
public class Edge{

	private Vertex source;
	private Vertex dest;
	private double weight;
	/**getter for x
	*@param src source vertex
	*@param dst destination vertex
	*@param wght weight of edge
	*/
	public Edge(Vertex src, Vertex dst, double wght){
		
		source = src;
		dest = dst;
		weight = wght;
	}
	/**getter for source
	*@return source vertex
	*/	
	public Vertex getSource(){return source;}
	/**getter for dest
	*@return destination vertex
	*/
	public Vertex getDest(){return dest;}
	/**getter for weight
	*@return weight of edge
	*/
	public double getWeight(){return weight;}
	/**
	*@param e is going to be compared with .this edge
	*@return true when edges has same source and dest vertexes
	*/
	public boolean equals(Edge e){
		return (e.getSource().equals(source) && e.getDest().equals(dest)&& weight == e.getWeight() );	
	}
}
