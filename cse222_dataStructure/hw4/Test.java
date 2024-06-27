import java.util.Stack;



public class Test{

	
	public static void main(String[] args){
			
		Username un1 = new Username("sibelgulmez");
		Username un2 = new Username("");
		Username un3 = new Username("sibel1");
		Username un4 = new Username("sibel");
		Password p1  = new Password("[rac()ecar]",74);
		Password p2  = new Password("pass[]",74);
		Password p3  = new Password("abcdabcd",74);
		Password p4  = new Password("[[[[]]]]",74);
		Password p5  = new Password("[no](no)",74);
		Password p6  = new Password("[rac()ecar]]",74);
		Password p7  = new Password("[rac()ecars]",74);
		Password p8  = new Password("[rac()ecar]",5);
		Password p9  = new Password("[rac()ecar]",35);
		
		System.out.printf("\n\nTest1... Inputs:\nusername: 'sibelgulmez'  -  password1: '[rac()ecar]'  -  password2: '74'");
		if(un1.controlUsername() && p1.controlPasswords(un1.getUsername())) System.out.printf("\nThe username and passwords are valid. The door is opening, please wait..");
		
		System.out.printf("\n\nTest2... Inputs:\nusername: ''  -  password1: '[rac()ecar]'  -  password2: '74'");
		if(un2.controlUsername() && p1.controlPasswords(un2.getUsername()))  System.out.printf("\nThe username and passwords are valid. The door is opening, please wait..");
		
		System.out.printf("\n\nTest3... Inputs:\nusername: 'sibel1'  -  password1: '[rac()ecar]'  -  password2: '74'");
		if(un3.controlUsername() && p1.controlPasswords(un3.getUsername()))  System.out.printf("\nThe username and passwords are valid. The door is opening, please wait..");
		
		System.out.printf("\n\nTest4... Inputs:\nusername: 'sibel'  -  password1: 'pass[]'  -  password2: '74'");
		if(un4.controlUsername() && p2.controlPasswords(un4.getUsername()))  System.out.printf("\nThe username and passwords are valid. The door is opening, please wait..");
		
		System.out.printf("\n\nTest5... Inputs:\nusername: 'sibel'  -  password1: 'abcdabcd'  -  password2: '74'");
		if(un4.controlUsername() && p3.controlPasswords(un4.getUsername()))  System.out.printf("\nThe username and passwords are valid. The door is opening, please wait..");
		
		System.out.printf("\n\nTest6... Inputs:\nusername: 'sibel'  -  password1: '[[[[]]]]'  -  password2: '74'");
		if(un4.controlUsername() && p4.controlPasswords(un4.getUsername()))  System.out.printf("\nThe username and passwords are valid. The door is opening, please wait..");
		
		System.out.printf("\n\nTest7... Inputs:\nusername: 'sibel'  -  password1: '[no](no)'  -  password2: '74'");
		if(un4.controlUsername() && p5.controlPasswords(un4.getUsername()))  System.out.printf("\nThe username and passwords are valid. The door is opening, please wait..");
		
		System.out.printf("\n\nTest8... Inputs:\nusername: 'sibel'  -  password1: '[rac()ecar]]'  -  password2: '74'");
		if(un4.controlUsername() && p6.controlPasswords(un4.getUsername()))  System.out.printf("\nThe username and passwords are valid. The door is opening, please wait..");
		
		System.out.printf("\n\nTest9... Inputs:\nusername: 'sibel'  -  password1: '[rac()ecars]'  -  password2: '74'");
		if(un4.controlUsername() && p7.controlPasswords(un4.getUsername()))  System.out.printf("\nThe username and passwords are valid. The door is opening, please wait..");
		
		System.out.printf("\n\nTest10... Inputs:\nusername: 'sibel'  -  password1: '[rac()ecar]'  -  password2: '5'");
		if(un4.controlUsername() && p8.controlPasswords(un4.getUsername()))  System.out.printf("\nThe username and passwords are valid. The door is opening, please wait..");
		
		System.out.printf("\n\nTest11... Inputs:\nusername: 'sibel'  -  password1: '[rac()ecar]'  -  password2: '35'");
		if(un4.controlUsername() && p9.controlPasswords(un4.getUsername()))  System.out.printf("\nThe username and passwords are valid. The door is opening, please wait..");
	}

}
