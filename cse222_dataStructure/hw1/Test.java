
/**
* @version  17.0.6
* @author Tarsuslu
*/
public class Test{
	/**
	*<p>The main function</p>
	*@param args arguemnt of main
	*/
	public static void main(String[] args){
	
	System.out.printf("\n\n\nScenario 1  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n\n");
	
	System.out.printf("\nStep 1: Creating accounts ...");
	Account gizem = new Account("0","gizemsungu","Istanbul","10.03.1995");	
	Account sibel = new Account("1","sibelgulmez","Istanbul","10.03.1995");
	Account gokhan = new Account("2","gokhankaya","Istanbul","10.03.1995");
	
	System.out.printf("\n\n\n\nStep 2: Logging in the account with username 'sibelgulmez' ...");
	sibel.login();
	
	System.out.printf("\n\n\n\nStep 3 : Sharing two posts ...");
	sibel.addPost("I like java");
	sibel.addPost("Java the coffe");
	
	System.out.printf("\n\n\n\nStep 4 : Following gizemsungu and gokhankaya ...");
	sibel.follow(gokhan);
	sibel.follow(gizem);
	
	System.out.printf("\n\n\n\nStep 5 : Logging out from account 'sibelgulmez' ...");
	sibel.logout();
	System.out.printf("\n\n\n\nStep 6 : Logging into another account (username: gokhankaya) ..." );
	gokhan.login();
	System.out.printf("\n\n\n\nStep 7 : Viewing sibelgulmez's profile ... ");
	gokhan.viewProfile(sibel);
	
	System.out.printf("\n\n\n\nStep 8 : Viewing sibelgulmez's posts ...");
	gokhan.viewPosts(sibel);
	
	System.out.printf("\n\n\nStep 9 : Liking sibelgulmez's posts ... ");
	gokhan.likePost(sibel.getPost()[0]);
	gokhan.likePost(sibel.getPost()[1]);
	
	System.out.printf("\n\n\nStep 10: Adding comment on a post of sibelgulmez ...");
	gokhan.commentPost(sibel.getPost()[0], "me too");
	
	System.out.printf("\n\n\nStep 11: Following sibelgulmez and gizemsungu ...");
	gokhan.follow(gizem);
	gokhan.follow(sibel);
	
	System.out.printf("\n\n\nStep 12: Sending message to gizemsungu ...");
	gokhan.sendMessage(gizem,"This homework too easy!");
	
	System.out.printf("\n\n\nStep 13: Logging out from the account 'gokhankaya'...");
	gokhan.logout();
	
	System.out.printf("\n\n\nStep 14: Logging into another account (username: gizemsungu)...");
	gizem.login();
	
	System.out.printf("\n\n\nStep 15: Checking outbox ...");
	gizem.checkOutbox();
	
	System.out.printf("\n\n\nStep 16: Checking inbox ...");
	gizem.checkInbox();
	
	System.out.printf("\n\n\nStep 17: Viewing inbox ...");
	gizem.viewInbox();
	
	System.out.printf("\n\n\nStep 18: Viewing sibelgulmez's profile ...");
	gizem.viewProfile(sibel);
	
	System.out.printf("\n\n\nStep 19: Viewing sibelgulmez's posts...");
	gizem.viewPosts(sibel);

	System.out.printf("\n\n\nStep 20: Viewing sibelgulmez's post's interactions...");
	gizem.viewPostsInteractions(sibel);
	
	System.out.printf("\n\n\nStep 21: Liking sibelgulmez's posts...");
	gizem.likePost(sibel.getPost()[0]);
	gizem.likePost(sibel.getPost()[1]);
	
	System.out.printf("\n\n\nStep 22: Viewing sibelgulmez's post's interactions ...");
	gizem.viewPostsInteractions(sibel);
	
	gizem.logout();
	System.out.printf("\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n\n");
	
	System.out.printf("\n\n\nScenario 2  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n\n");
	
	System.out.printf("\n\n\nStep 1: gizemsungu logs in...");
	gizem.login();
	
	System.out.printf("\n\n\nStep 2: gizemsungu shares a post (Post1) ...");
	gizem.addPost("Post1");
	
	System.out.printf("\n\n\nStep 3: gizemsungu shares another post (Post2) ...");
	gizem.addPost("Post2");
	
	System.out.printf("\n\n\nStep 4: gizemsungu logs out ...");
	gizem.logout();
	
	System.out.printf("\n\n\nStep 5: sibelgulmez logs in ...");
	sibel.login();
	
	System.out.printf("\n\n\nStep 6: sibelgulmez views gizemsungur's profile ...");
	sibel.viewProfile(gizem);	
		
	System.out.printf("\n\n\nStep 7: sibelgulmez likes Post1 ...");
	sibel.likePost(gizem.getPost()[0]);
	
	System.out.printf("\n\n\nStep 8: sibelgulmez logs out ...");
	sibel.logout();
	
	System.out.printf("\n\n\nStep 9: gokhankaya logs in ...");
	gokhan.login();
	
	System.out.printf("\n\n\nStep 10: gokhankaya views gizemsungur's profile ...");
	gokhan.viewProfile(gizem);
	
	System.out.printf("\n\n\nStep 11: gokhankaya makes a comments on Post2 ...");
	gokhan.commentPost(gizem.getPost()[1], "Nice!");
	
	System.out.printf("\n\n\nStep 12: gokhankaya sends a message to gizemsungu...");
	gokhan.sendMessage(gizem, "Hello!");
	
	System.out.printf("\n\n\nStep 13: gokhankaya logs out ...");
	gokhan.logout();
	
	System.out.printf("\n\n\nStep 14: gizemsungu logs in...");
	gizem.login();
	
	System.out.printf("\n\n\nStep 15: gizemsungu views her own profile...");
	gizem.viewProfile(gizem);
	
	System.out.printf("\n\n\nStep 16: gizemsungu reads the message from gokhankaya...");
	gizem.viewInbox();
	gizem.logout();
	System.out.printf("\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n\n");
	
	System.out.printf("\n\n\nScenario 3  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n\n");
	
	System.out.printf("\n\n\nStep 1: gizemsungu logs in...");
	gizem.login();
	
	System.out.printf("\n\n\nStep 2: gizemsungu blocks sibelgulmez...");
	gizem.block(sibel);
	
	System.out.printf("\n\n\nStep 3: gizemsungu logs out...");
	gizem.logout();
	
	System.out.printf("\n\n\nStep 4: sibelgulmez logs in...");
	sibel.login();
	
	System.out.printf("\n\n\nStep 5: sibelgulmez tries to view profile of 'gizemsungu'...");
	sibel.viewProfile(gizem);
	
	System.out.printf("\n\n\nStep 6: sibelgulmez tries to send a message to 'gizemsungu'...");
	sibel.sendMessage(gizem,"deneme");
	
	System.out.printf("\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n\n");
	}
}

