import java.util.Stack;



public class Password{

	private String password1;
	private int password2;

	public Password(String pss1, int pss2){
	
		password1 = new String(pss1);
		password2 = pss2;
	
	}
	public Password(int pss2){
		password1 = new String();
		password2 = pss2;
	}
	
	public Password(String pss2){
		password1 = new String(pss2);
	}
	
	public String getpss1(){ return password1;}
	public int getpss2(){ return password2;}
	public boolean containUsernameSpirit(String name, String passwd){
	
		boolean kontrol = false;
		Stack<Character> stack = new Stack<>();
		for(int a = 0; a < passwd.length(); a++){
			stack.push(passwd.charAt(a));
		}
		while(!stack.empty()){
			if(name.indexOf(stack.pop()) > -1) kontrol = true;	
		}
		return kontrol;
	}
	public boolean isBracket(Character ch){
		
		String parantez = new String("{[]}()");
		if(parantez.indexOf(ch) > -1) return true;
		
		return false;
	}
	public boolean parantezStack(String passwd){
		
		Stack<Character> stack = new Stack<>();
		String parantez = new String("{[]}()");
		for(int a = 0; a < passwd.length(); a++){
			if(parantez.indexOf(passwd.charAt(a)) > -1 ) stack.add(passwd.charAt(a));
		}
		return (stack.size() >= 2);
	}
	
	public boolean isBalanced(String passwd){
		Stack<Character> stack = new Stack<>();
		boolean kontrol = true;
		for(int a = 0; a < passwd.length(); a++){
			if(isBracket(passwd.charAt(a))){
				char ch = passwd.charAt(a);
					
				switch(ch){
					case'{':
						stack.push(ch);
					break;
					case'(':
						stack.push(ch);
					break;
					case'[':
						stack.push(ch);
					break;

					case'}':
						if(!stack.empty() && stack.peek() == '{') stack.pop();
						else kontrol = false;
					break;
					case')':
						if(!stack.empty() && stack.peek() == '(') stack.pop();
						else kontrol = false;
					break;
					case']':
						if(!stack.empty() && stack.peek() == '[') stack.pop();
						else kontrol = false;
					break;
				}
			}
		}
		if(!stack.empty()) kontrol = false;
		return kontrol;
	}
	
	public boolean isPalindromePossible(String psswd){
		String temp = new String(psswd.replaceAll("[^a-zA-Z]",""));
		
		return wrapPalindrome(temp);
		
	}
		
	public boolean wrapPalindrome(String psswd){
		
		if(psswd.length() <= 1) return true;
		
				
		for(int a = 0; a < psswd.length(); a++){		
			char ch = psswd.charAt(a);
			if(!(psswd.indexOf(ch,a+1) < 0)){
				String st = new String();
				st = psswd.substring(0,a) + psswd.substring(a+1, psswd.indexOf(ch,a+1)) + psswd.substring(psswd.indexOf(ch,a+1)+1);
				return wrapPalindrome(st);
			}
			
		}
		return false;
	}

	public boolean isExactDivision(int psswd,int[] denoms, int index){
	
		if(psswd == 0) return true;
		if(index == denoms.length || psswd < 0) return false;
		
	
		int denom = denoms[index];
		for(int a = 0; a*denom <= psswd ; a++){
			if(isExactDivision(psswd - a*denom, denoms, index + 1 )) return true;
		
		}
		
		return false;
	
	}
	public boolean isValueValid(int pss2){

		return (pss2 >= 10 && pss2 <= 10000 );	
	}
	
	public boolean isLengthEnough(String pss2){

		return (pss2.length() >= 8 );	
	}
	
	
	public boolean controlPasswords(String username){
		int[] denoms = {4,17,29};
		boolean b1,b2,b3,b4,b5,b6,b7;
		
		b1 = containUsernameSpirit(username,password1);
		b6 = isPalindromePossible(password1);
		b3 = isBalanced(password1);
		b5 = isExactDivision(password2, denoms,0);
		b4 = isValueValid(password2);
		b7 = parantezStack(password1);
		b2 = isLengthEnough(password1);
		
		if(!b1) System.out.printf("\nError: The password1 is invalid. It should have at least 1 character from the username.");
		if(b1 && !b2) System.out.printf("\nError: The password1 is invalid. It should have at least 8 characters.");
		if(b1 && b2 && !b3) System.out.printf("\nError: The password1 is invalid. It should be balanced.");
		if(b1 && b2 && b3 && !b4) System.out.printf("\nError: The password2 is invalid. It must be between 10 and 10.000.");
		if(b1 && b2 && b3 && b4 && !b5) System.out.printf("\nError: The password2 is invalid. It is not compatible with the denominations.");
		if(b1 && b2 && b3 && b4 && b5 && !b6) System.out.printf("\nError: The password1 is invalid. It should be possible to obtain a palindrome from the password1.");
		if(b1 && b2 && b3 && b4 && b5 && b6 && !b7) System.out.printf("\nError: The password1 is invalid. It should have at least 2 brackets.");
		
		return b1 && b2 && b3 && b4 && b5 && b6 && b7;
	
	}


}

