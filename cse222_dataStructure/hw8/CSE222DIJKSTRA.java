import java.util.*;
import java.io.*;

/**
*CSE222DISJKSTRA class
*@author Tarsuslu
*/
public class CSE222DIJKSTRA{

	private CSE222GRAPH graph;
	private Set<Vertex> S;
	private Set<Vertex> VS;
	private double[] d;
	private int[] p;
	/**
	*length of path 
	*/
	public double length;
	
	/** constructor
	*@param gr is the CSE222GRAPH object 
	*/
	public CSE222DIJKSTRA (CSE222GRAPH gr){
		graph = gr;
		S = new HashSet<Vertex>();
		VS = new HashSet<Vertex>();
		d = new double[gr.getMap().getVertexes().size()];
		p = new int[gr.getMap().getVertexes().size()];	
		length = 999999;
	}
	/**
	*fill VS array to use in dijkstra algorithm 
	*/
	public void fillVS(){
		for(int a = 0 ; a <graph.getMap().getVertexes().size();a++)
				VS.add(graph.getMap().getVertexes().get(a));
	
	}
	/**
	*This method is the place dijk algorithm implemented
	*VS set fill all the vertexes except starting vertex
	*S set initiliated with starting vertex
	*d array includes the information distance from starting vertex for all vertexes
	*p array includes the label of previous vertex for all vertexes
	*@return path to end from starting vertex
	*/
	public ArrayList<Vertex> Dijkstra()throws Exception{
		S.add(graph.getMap().getStarting());		
		fillVS();
		VS.remove(graph.getMap().getStarting());
		Vertex s = graph.getMap().getStarting();
		for(Vertex v : VS){
			p[v.getLabel()] = s.getLabel();
			d[v.getLabel()] = graph.isEdge(s,v);
		}		
		double smallest = 999999;
		Vertex aranan = new Vertex(-1,-1);
		
		while(!VS.isEmpty()){
			smallest = 999999;
			for(Vertex v1 : VS){
				if(d[v1.getLabel()] <= smallest){
					aranan = v1;
					smallest = d[v1.getLabel()];
				}
				
			}
			VS.remove(aranan);
			S.add(aranan);
			Set<Vertex> adj = graph.findAdj(aranan);
			for(Vertex v2 : adj){
				double w = graph.isEdge(v2,aranan);
				if(d[aranan.getLabel()] + w < d[v2.getLabel()]){
					d[v2.getLabel()] = d[aranan.getLabel()] + w;
					p[v2.getLabel()] = aranan.getLabel();
				}
			}
		}
		ArrayList<Vertex> ret = new ArrayList<Vertex>();
		int index = graph.getMap().getEnding().getLabel();
		int sayac = 0;
		for(; sayac < p.length; sayac++){
			Vertex v = graph.getMap().getVertexes().get(p[index]);
			ret.add(v);
			index = p[index];
			if(v.equals(graph.getMap().getStarting())) break;
		}
		
		length =  sayac;//d[graph.getMap().getEnding().getLabel()];
		if(d[graph.getMap().getEnding().getLabel()] == 999999) throw new Exception("can not find a path");
			
		return ret;
			
	}
}
