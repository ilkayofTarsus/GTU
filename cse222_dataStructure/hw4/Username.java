import java.util.Stack;



public class Username{

	private String ad;

	public Username(){
		ad = new String();
	}
	public Username(String isim){
		ad = new String(isim);
	}
	
	public String getUsername(){ return ad;}

	public boolean checkIfValidUsername(String name){
		
		if(name.isEmpty()){
			System.out.printf("\nError: The username is invalid. It should have at least 1 character.\n");		
			return false;
		}
		return wrapRecursive(name);
	}
	
	public boolean wrapRecursive(String name){
	
		if(0 == name.length()) return true;
		
		if(!Character.isLetter(name.charAt(0))){
			System.out.printf("\nError: The username is invalid. It should have letters only.");	
			return false;
		}
		return wrapRecursive(name.substring(1));
	}

	public boolean controlUsername(){
		return checkIfValidUsername(ad);	
	}

}
