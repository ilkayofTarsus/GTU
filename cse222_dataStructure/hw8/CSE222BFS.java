import java.util.*;
import java.io.*;


/**
*@author Tarsuslu
*/
public class CSE222BFS{

	private CSE222GRAPH graph;
	/**
	*length of path 
	*/
	public double length;
	
	
	/**constructor
	*@param gr  is the CSE222GRAPH object
	*length is initiliated to 999999 if algorithm does not change the length it maintains
	*/
	public CSE222BFS(CSE222GRAPH gr){
		graph = gr;
		length = 999999;
	}
	
	/**
	*This method is the place bfs algorithm implemented
	*visited array keeps the information of whether the vertex visited or not before. indexes of array are label of vertexes
	*When you give a index to parent array it gives a index which is label of vertex that saw the vertex first 
	*que is a Queue that keeps vertexes for examining every adjacent of vertexes
	*@return path to end from starting vertex
	*/
	public ArrayList<Vertex> BFSAlgorithm()throws Exception{
		boolean kontrol = false;
		boolean[] visited = new boolean[graph.getMap().getVertexes().size()];
		Vertex[] parents = new Vertex[graph.getMap().getVertexes().size()];
		Queue<Vertex> que = new LinkedList<Vertex>();
		que.offer(graph.getMap().getStarting());
		
		while(!que.isEmpty()){
			Vertex v = que.poll();
			Set<Vertex> adj = graph.findAdj(v);

			if(v.equals(graph.getMap().getEnding())){
				kontrol = true;	
				break;
			}
			for(Vertex v1 : adj){
				if(!visited[v1.getLabel()]){
					visited[v1.getLabel()] = true;
					parents[v1.getLabel()] = v;
					que.offer(v1);
				}
			}
		}
		if(!kontrol) throw new Exception("Can not find a path");
		ArrayList<Vertex> path = new ArrayList<Vertex>();
		int index = graph.getMap().getEnding().getLabel();
		int sayac = 0;
		for(;sayac < parents.length; sayac++){
			Vertex v = graph.getMap().getVertexes().get(parents[index].getLabel());
			path.add(v);
			index = parents[index].getLabel();
			if(v.equals(graph.getMap().getStarting())){
				break;
			}
		}
		length = sayac;
		
		return path;
	}
}
