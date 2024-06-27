import javax.swing.*;  
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreeNode;
import java.util.Queue;
import java.util.Stack;
import java.util.LinkedList;
import java.util.ArrayList;

/**


@author Tarsuslu
*/
public class Tree{

	private DefaultMutableTreeNode rot;
	
	/**
	@param arr is the String array which tree is created acording to
	*
	*/
	public Tree(String[][] arr){
	
	rot = makeTree(arr);
	
	}
	
	
	/**
	@param node a treenode which is controlled whether has isimm or not
	@param isim a string which is controlled whether exists in node subtree
	@return returns isim's index in node subtree
	*/
	public int indexOfChild(DefaultMutableTreeNode node, String isim){
		int index = 0, kontrol = 0;
		kontrol = node.getChildCount();
		if(kontrol != 0){
		DefaultMutableTreeNode current = (DefaultMutableTreeNode) node.getFirstChild();
		while(node.getChildCount() != index){
			if(current.toString().compareTo(isim) == 0) return index;
			current = (DefaultMutableTreeNode) node.getChildAfter(current);
			index++;
		}
		}
		return -1;
	}
	
	/**
	@param arr is the String array which tree is created acording to
	@return root of tree
	*/
	public DefaultMutableTreeNode makeTree(String[][] arr){
		DefaultMutableTreeNode root = new DefaultMutableTreeNode("Root"); 
		DefaultMutableTreeNode temp = root;
		DefaultMutableTreeNode temp1;
		for(int a = 0 ; a < arr.length; a++){
			for(int b = 0 ; b < arr[0].length ; b++){
				if(arr[a][b] != null){
					int index = indexOfChild(temp,arr[a][b]);
					if(index == -1) temp1 = new DefaultMutableTreeNode(arr[a][b]);
					else temp1 = (DefaultMutableTreeNode) temp.getChildAt(index);
					temp.add(temp1);
					temp = temp1;
				}
			}
		temp = root;
		}
	
	
		return root;
	}
	/**shows tree
	*/
	public void showTree(){
		JFrame f = new JFrame(); 
		JTree jt=new JTree(rot);  
		f.add(jt);  
		f.setSize(200,200);  
		f.setVisible(true);  
	
	}
	
	/**
	@param que is a Queue. it is needed to BFS algorıthm
	@param aranan is the wanted node 
	@param sayac counts steps 
	@return a boolean to be used recursive method
	*/
	public boolean partB1(Queue<DefaultMutableTreeNode> que,DefaultMutableTreeNode aranan,int sayac){
		DefaultMutableTreeNode temp = que.poll();
		if(temp == null) return false;
		if(aranan.toString().compareTo(temp.toString()) == 0){
			System.out.printf("\nStep %d -> %s (Found!)",sayac,temp.toString());
			return true;
		}
		System.out.printf("\nStep %d -> %s",sayac,temp.toString());
		if(!temp.isLeaf()){
			DefaultMutableTreeNode child = (DefaultMutableTreeNode) temp.getFirstChild();
			for(int a = 0; a < temp.getChildCount(); a++){
				que.offer(child);
				child = child.getNextSibling();
			}
		}
		return partB1(que,aranan,++sayac);
	}

	/**
	@param aranan is the wanted node 
	@param sayac counts steps 
	@return indicate return of partb1
	*/
	public boolean partB(DefaultMutableTreeNode aranan,int sayac){
		
		Queue<DefaultMutableTreeNode> que = new LinkedList<DefaultMutableTreeNode>();
		que.offer(rot);
		System.out.printf("\nBFS to find '%s'",aranan.toString() );
		boolean ret = partB1(que,aranan,sayac); 
		if(!ret) System.out.printf("\n Not Found");
		return ret;
	
	}
	
	
	
	/**
	@param stack is a Stack. it is needed to NFS algorıthm
	@param aranan is the wanted node 
	@param sayac counts steps 
	@return a boolean to be used recursive method
	*/
	public boolean partC1(Stack<DefaultMutableTreeNode> stack,DefaultMutableTreeNode aranan,int sayac){
		if(stack.empty()) return false;
		DefaultMutableTreeNode temp = stack.pop();
		if(temp == null) return false;
		if(aranan.toString().compareTo(temp.toString()) == 0){
			System.out.printf("\nStep %d -> %s (Found!)",sayac,temp.toString());
			return true;
		}
		System.out.printf("\nStep %d -> %s",sayac,temp.toString());
		if(!temp.isLeaf()){
			DefaultMutableTreeNode child = (DefaultMutableTreeNode) temp.getFirstChild();
			for(int a = 0; a < temp.getChildCount(); a++){
				stack.push(child);
				child = child.getNextSibling();
			}
		}
		return partC1(stack,aranan,++sayac);
	}
	/**
	@param aranan is the wanted node 
	@param sayac counts steps 
	*/
	public void partC(DefaultMutableTreeNode aranan,int sayac){
		Stack<DefaultMutableTreeNode> stack = new Stack<DefaultMutableTreeNode>();
		stack.push(rot);
		System.out.printf("\nDFS to find '%s'",aranan.toString() );
		if(!partC1(stack,aranan,sayac)) System.out.printf("\n Not Found");
	
	}
	
	/**
	@param node is the current node to be checked with aranan node
	@param aranan is the wanted node 
	@param sayac counts steps 
	@return a boolean to be used recursive method
	*/
	public boolean partD1(DefaultMutableTreeNode node , DefaultMutableTreeNode aranan,int sayac){
		if(node.toString().compareTo(aranan.toString()) == 0 ){
			System.out.printf("\nStep %d -> %s (Found!)",sayac,node.toString());
			return true;
		}
		System.out.printf("\nStep %d -> %s",sayac,node.toString());
		if(!node.isLeaf()){
			DefaultMutableTreeNode temp = (DefaultMutableTreeNode) node.getFirstChild();
			for(int a = 0; a < node.getChildCount(); a++){
				if(partD1(temp,aranan,++sayac)) return true;
				temp = temp.getNextSibling();
			}		
		}
	
		return false;
	}
	
	/**
	@param aranan is the wanted node 
	@param sayac counts steps 
	*/
	public void partD(DefaultMutableTreeNode aranan,int sayac){
		System.out.printf("\nPost-Order Traversal to find '%s'",aranan.toString() );
		if(!partD1(rot,aranan,sayac)) System.out.printf("\n Not Found");
	}
	
	
	/**
	@param path is the erased from tree
	@param year will include path 
	*/
	public void partE(String path, String year){
		boolean kontrol = pathExists(path,rot);
		if(kontrol){
			DefaultMutableTreeNode node = findNode(path);
			DefaultMutableTreeNode nodeParent = (DefaultMutableTreeNode) node.getParent();
			if(nodeParent.getChildCount() == 1 ) nodeParent.removeFromParent();
			node.removeFromParent();
			DefaultMutableTreeNode tail = createPath(path);
			DefaultMutableTreeNode toYear;
			int indexYear = indexOfChild(rot,year);
			if(indexYear == -1)  toYear = new DefaultMutableTreeNode(year);
			else  toYear = (DefaultMutableTreeNode) rot.getChildAt(indexYear);
			
			while(!tail.isLeaf()){
				tail = (DefaultMutableTreeNode) tail.getFirstChild();
				int index = indexOfChild(toYear,tail.toString());
				if(index == -1){
					DefaultMutableTreeNode ekle = new DefaultMutableTreeNode(tail);
					toYear.add(ekle);
					toYear = ekle;
				}
				else toYear = (DefaultMutableTreeNode) toYear.getChildAt(index);
			}
			for(int a = 0 ; a < node.getChildCount(); a++){
				DefaultMutableTreeNode child = (DefaultMutableTreeNode) node.getChildAt(a);
				toYear.add(child);
			}	
		}
		else System.out.printf("\n\n%s does not exist !!",path);
	}
	
	/**Creates a TreeNode path with given array
	@param path tells us to path to node 
	@return tail which is wanted
	*/
	public DefaultMutableTreeNode createPath(String path){
		
		String[] splitArr = path.split("-");
		DefaultMutableTreeNode tail = new DefaultMutableTreeNode(splitArr[0]);
		DefaultMutableTreeNode iter = tail;
		for(int a = 1; a < splitArr.length; a++) {
			DefaultMutableTreeNode temp = new DefaultMutableTreeNode(splitArr[a]);
			iter.add(temp);
			iter = temp;
		}
						
		return tail;	
	}
	/**
	@param path tells us to path to node 
	@return node which is wanted
	*/
	public DefaultMutableTreeNode findNode(String path){
	
		String[] splitArr;
		DefaultMutableTreeNode iter = rot;
		splitArr = path.split("-");
		int index2 ,index = indexOfChild(rot,splitArr[0]);
		boolean kontrol = true;
		if(index != -1){
			iter = (DefaultMutableTreeNode) iter.getChildAt(index);
			for(int a = 1; a < splitArr.length; a++){
				index2 = indexOfChild(iter,splitArr[a]); 			
				if(index2 == -1) kontrol = false;
				else iter = (DefaultMutableTreeNode) iter.getChildAt(index2);
			}
		}
		if(!kontrol)return null;
		
		return (DefaultMutableTreeNode) iter;
	
	}
	
	/**
	@param path a string to tells the way for wanted node
	@param node will be controlled to includes path or not
	@return a boolean to be used whether given path exists or not
	*/
	public boolean pathExists(String path, DefaultMutableTreeNode node){
	
		String[] splitArr;
		boolean kontrol = true;
		splitArr = path.split("-");
		int index = indexOfChild(node,splitArr[0]);
		if(index != -1){
			for(int a = 1 ; a < splitArr.length; a++){
				node = (DefaultMutableTreeNode) node.getChildAt(index);
				index = indexOfChild(node,splitArr[a]); 
				if( index == -1){
					kontrol = false;
					break;
				}
			}
		}
		else kontrol = false;
	
	return kontrol;
	}
	
	
	/**
	@return root of tree
	*/
	public DefaultMutableTreeNode getRoot(){return rot;}


}
