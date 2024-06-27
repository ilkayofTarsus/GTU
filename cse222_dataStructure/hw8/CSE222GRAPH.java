import java.util.*;
import java.io.*;

/** Includes edges and CSE222MAP object as fields
*@author Tarsuslu
*/
public class CSE222GRAPH{
	
	private ArrayList<List<Edge>> edges;
	private CSE222MAP map;
	
	/**constructor
	*@param map is the CSE222MAP object for creating graph
	*/
	public CSE222GRAPH(CSE222MAP map){
		this.map = map;
		edges = new ArrayList<List<Edge>>();
		for(int a = 0; a < map.getNumV(); a++){
			edges.add(new LinkedList<Edge>());
		}
		
		createEdges();	
	}
	/**
	*@param e is going to be inserted edges List accordimng to source vertex number
	*/
	public void insert(Edge e){
		edges.get(e.getSource().getLabel()).add(e);
	
	}
	
	/**
	*it just has a for loop 
	*the for loop iterates every vertex and inserts these edges to array by insert method and adjVertexes method
	*/
	public void createEdges(){
		for(int a = 0; a < map.getNumV(); a++){
				adjVertexes(map.getVertexes().get(a));
		}
	}
	/**
	*@param v adjacents of v create edge with v vertex
	*/
	public void adjVertexes(Vertex v){

		for(int a = v.getLabel(); a < map.getVertexes().size(); a++/*Vertex v2 : map.getVertexes()*/){
			Vertex v2 =  map.getVertexes().get(a);
			if(v.getX()-1 == v2.getX() && v.getY()+1 == v2.getY()){
				insert(new Edge(v,v2,1.41));
				insert(new Edge(v2,v,1.41));
			}
			if(v.getX() == v2.getX() && v.getY()+1 == v2.getY()){
				insert(new Edge(v,v2,1));
				insert(new Edge(v2,v,1));	
			}
			if(v.getX()+1 == v2.getX() && v.getY() == v2.getY()){
				insert(new Edge(v,v2,1));
				insert(new Edge(v2,v,1));
			}
			if(v.getX()+1 == v2.getX() && v.getY()+1 == v2.getY()){
				insert(new Edge(v,v2,1.41));
				insert(new Edge(v2,v,1.41));
			}
			if(v.getX()+1 < v2.getX() && v.getY()+1 < v2.getY()) break;
		}
	}
	/** this function checks whether v and s made a edge or not
	*@param v one of the vertexes
	*@param s one of the vertexes
	*@return if v and s edge found in edges List then return the weight of edge otherwise returns biggest number
	*/
	public double isEdge(Vertex v,Vertex s){
		List<Edge> ed = new LinkedList<Edge>();		
		ed = edges.get(v.getLabel());
		for(Edge e : ed)
			if(e.getDest().equals(s)) 
				return e.getWeight();
		
		return 999999;
	}
	
	/**
	*@param v to find its adjacents
	*@return Set of adjacent of v
	*/
	public HashSet<Vertex> findAdj(Vertex v){
		
		HashSet<Vertex> ret = new HashSet<Vertex>();
		boolean kontrol = true;
		List<Edge> ed = new LinkedList<Edge>();		
		ed = edges.get(v.getLabel());
		for(Edge e: ed) ret.add(e.getDest());
	
		return ret;
		
	}
	/** getter for CSE222MAP map
	*@return map 
	*/
	public CSE222MAP getMap(){return map;}
	/**getter or edges List
	*@return edges 
	*/
	public ArrayList<List<Edge>> getEdges(){return edges;}
}
