/**

@author Tarsuslu
*/
public class Account{

	private String accountID;
	private String username;
	private String birthdate;
	private String location;
	private Post[] posts;
	private Account[] followings;
	private Account[] followers;
	private Account[] blockedList;
	private Account[] blockingList;
	private Message[] messages;
	private int numberOfMessages;	
	private int postNumber;
	private int followerNumber;
	private int followingNumber;
	private boolean isLoggedIn;
	/**
	<p> Counstructor of Account </p>
	@param accID reprsent accountID that represent first account as 0
	@param userName an username
	@param birthDate a birthdate includes day / month / year
	@param Location user's location
	*/
	public Account(String accID, String userName, String birthDate, String Location){
		
		this.accountID = accID;
		this.username = userName;
		this.birthdate =  birthDate;
		this.location = Location;
		this.isLoggedIn = false;
		this.postNumber = 0;
		this.followingNumber = 0;
		this.followerNumber = 0;
		this.numberOfMessages = 0;
		this.posts = new Post[0];
		this.followings = new Account[0];
		this.followers = new Account[0];
		this.blockedList = new Account[0];
		this.blockingList = new Account[0];
		this.messages = new Message[0];
		System.out.printf("\nAn account with username " + username + " has been created");
		
	}
	/**
	<p>block function is used for blocking an account</p>
	@param hesap the parametre represents an account to get blocked
	*/
	public void block(Account hesap){
	
		Account[] yedek = new Account [blockingList.length + 1];
		for (int a = 0; a <blockingList.length; a++){

			yedek[a] = blockingList[a];
		}		
		
		yedek[blockingList.length] = hesap;
		
		this.blockingList = new Account [yedek.length];
		for (int a = 0; a <yedek.length; a++){

			blockingList[a]= yedek[a];
		}	
		hesap.getBlocked(this);
	}
	/**
	<p>The function provides to put parameter account to getblocked list (an array)</p>
	@param hesap is the account that blocks this account
	*/
	public void getBlocked(Account hesap){
		
		Account[] yedek = new Account [blockedList.length + 1];
		for (int a = 0; a <blockedList.length; a++){

			yedek[a] = blockedList[a];
		}		
		
		yedek[blockedList.length] = hesap;	
		this.blockedList = new Account [yedek.length];
		for (int a = 0; a <yedek.length; a++){

			blockedList[a] = yedek[a];
		}
	
	}
	/**
	<p>The function provides to functions whether this account is blocked or not  </p>
	@param hesap hesap parameter is going to be checked whether block this account or not
	@return kontrol value represents as 1 when this account get blocked
	*/
	public final boolean checkBlocked(Account hesap){
	
		boolean kontrol = false;
		for(Account a1: blockedList){
			
			if(a1 == hesap) kontrol = true;		
		}
	
		return kontrol;
	}
	
	/**
	<p> basic login function that make isLoggedIn value true</p>
	*/
	public void login(){
	
		this.isLoggedIn = true;
	}
	
	/**
	<p> basic logout funtıon that make isLoggedIn value false</p>
	*/
	public void logout(){
	
		this.isLoggedIn = false;
	}
	/**
	<p>The function checks this account is login or not</p>
	@return isLoggedIn is true if account logs in
	*/
	public final boolean checkLog(){
	
		if(!isLoggedIn) System.out.printf("\n Error : The account that you want to do an implementation is not logged in currently ");
		
		return isLoggedIn;
	}	
	
	/**
	<p>The function provides to send a message to another account</p>
	@param hesap is the account that get a message
	@param cont is the content of messages
	@return kontrol is true when message is sent
	*/
	public boolean sendMessage(Account hesap, String cont){
		if(checkBlocked(hesap)){
		
			System.out.printf("\n Error : The account blocked you");	
			return false;
		}
		if(!checkLog()) return isLoggedIn;
		boolean kontrol;
		kontrol = isFollowed(hesap);
		if(!kontrol) System.out.printf("\n Error : You can not send message. You do not follow the account");		
		else{
			if(messages.length <= numberOfMessages){
				
				Message[] yedek = new Message[messages.length + 5];
				for(int a = 0; a < messages.length; a++){

					yedek[a] = messages[a];
				}
			
				yedek[numberOfMessages] = new Message(String.valueOf(numberOfMessages),username,hesap.getUsername(),cont);
				this.messages = new Message[yedek.length];	
				for(int a = 0; a < messages.length; a++){

					messages[a] = yedek[a] ;
				}
			
				this.numberOfMessages++;	
			}
			else{
			
				messages[numberOfMessages] = new Message(String.valueOf(numberOfMessages),username,hesap.getUsername(),cont);		
				numberOfMessages++;
			}			
		
		
		}
		hesap.receiveMessage(new Message(String.valueOf(numberOfMessages),username,hesap.getUsername(),cont));
		return kontrol;
	}
	
	/**
	<p> The function provides to get a message </p>
	@param mesaj is the Message object that includes sender receiver and content
	*/
	public void receiveMessage(Message mesaj){
		if(messages.length <= numberOfMessages){
			
			Message[] yedek = new Message[messages.length + 5];
			for(int a = 0; a < messages.length; a++){
					yedek[a] = messages[a];
			}
		
			yedek[numberOfMessages] = mesaj;
			this.messages = new Message[yedek.length];	
			for(int a = 0; a < messages.length; a++){
				messages[a] = yedek[a] ;
			}
		
			this.numberOfMessages++;	
		}
		else{
		
			messages[numberOfMessages] = mesaj;
			numberOfMessages++;
		}			
	}
	
	/**
	<p>Give the output that says how many message are there in the outbox</p>
	*/
	public final void checkOutbox(){
		if(!checkLog()) return;
		int numOutbox = 0;
		for(int a = 0; a < numberOfMessages; a++){
		
			if(messages[a].getSenderID().equals(username)) numOutbox++ ;
		}
		System.out.printf("\nThere is/are %d message(s) in the outbox", numOutbox);	
	}
	
	/**
	<p>Gives the output that says how many message are there in the inbox</p>
	*/
	public final void checkInbox(){
		if(!checkLog()) return;
		int numInbox = 0;
		for(int a = 0; a < numberOfMessages; a++){
		
			if(messages[a].getReceiverID().equals(username)) numInbox++ ;
		}
		System.out.printf("\nThere is/are %d message(s) in the inbox", numInbox);	
	}
	
	/**
	<p>Gives the messages in inbox contents</p>
	*/
	public final void viewInbox(){
		if(!checkLog()) return;
		int numOutbox = 0;
		
		
		for(int a = 0; a < numberOfMessages; a++){
			if(messages[a].getReceiverID().equals(username)) {
							
				System.out.printf(messages[a].toString());								
			}
		}
	}
	/**
	<p> Creates an Post objects represents a post in social media</p>
	@param cont that represents posts content
	*/
	public void addPost(String cont){
		if(!checkLog()) return;
		if(posts.length <= this.postNumber){

			Post[] yedek = new Post[posts.length + 5];
			for(int a = 0; a < posts.length; a++){

				yedek[a] = posts[a];
			}
		
			yedek[postNumber] = new Post(String.valueOf(postNumber),username,cont);
			this.posts = new Post[yedek.length];	
			for(int a = 0; a < posts.length; a++){

				posts[a] = yedek[a] ;
			}
		
			this.postNumber++;				
		}			

		else{

		posts[postNumber] = new Post(String.valueOf(postNumber),username,cont);		
		postNumber++;
		
		}
	
		System.out.printf(posts[postNumber-1].toString());
	
	}
	/**
	<p>proivdes to like a post</p>
	@param gonderi is the post that is going to be liked
	*/
	public final void likePost(Post gonderi){
		if(!checkLog()) return ;
			gonderi.getLiked(this);
		
	}
	/**
	<p>comments a post</p>
	@param gonderi is the post that is going to be commented
	@param yorum is the content of the comment
	*/
	public final void commentPost(Post gonderi, String yorum){
		if(!checkLog()) return ;
		
		
			gonderi.getCommented(new Comment(String.valueOf(gonderi.getNumberOfComments()),username,gonderi.getPostID(),yorum));
	}
	
	/**
	<p>The function provides the follow another account</p>
	@param hesap is the account that is going to be followed
	*/
	public void follow(Account hesap){
		if(!checkLog()) return;
		if(checkBlocked(hesap)){
		
			System.out.printf("\n Error : The account blocked you");	
			return;
		}
		
		if(followings.length <= this.followingNumber){

				Account[] yedek = new Account[followings.length + 5];
				for(int a = 0; a < followings.length; a++){

					yedek[a] = followings[a];
				}
			
				yedek[followingNumber] = hesap;
				this.followings = new Account[yedek.length];	
				for(int a = 0; a < followings.length; a++){

					followings[a] = yedek[a] ;
				}
			
				this.followingNumber++;
				hesap.getFollowed(this);				
			}			

		else{

			followings[followingNumber] = hesap;		
			this.followingNumber++;
			hesap.getFollowed(this);
			
		}
		
		
	
	
	}
	/**
	<p>this function provides the to put hesap argument in the followers array</p>
	@param hesap is the acccount that follows this account
	*/
	public void getFollowed(Account hesap){
		if(followers.length <= this.followerNumber){

				Account[] yedek = new Account[followers.length + 5];
				for(int a = 0; a < followers.length; a++){

					yedek[a] = followers[a];
				}
			
				yedek[followerNumber] = hesap;
				this.followers = new Account[yedek.length];	
				for(int a = 0; a < followers.length; a++){

					followers[a] = yedek[a] ;
				}
			
				this.followerNumber++;				
			}			

		else{

			followers[followerNumber] = hesap;		
			this.followerNumber++;
			
		}
		
	
	}
	/**
	<p>the function provide that view an account's all post's contents</p>
	@param hesap is the account that is going to viewed all its posts
	*/
	public final void viewPosts(Account hesap){
		if(!checkLog()) return ;
		if(checkBlocked(hesap)){
		
			System.out.printf("\n Error : The account blocked you");	
			return;
		}
			if(0 == hesap.getPost().length) System.out.printf("\nError : This account has no post\n");
			else{
				for(int a = 0; a<hesap.getPostNumber(); a++){

					System.out.printf("\n" + hesap.getPost()[a].toString());
				}
			}		
	}
	/**
	<p>provides to take a look post's interactions</p>
	@param gonderi is the Post object that is going to be viewed its comments and likes
	*/
	public final void viewPostInteractions(Post gonderi){
		if(!checkLog()) return ;

			gonderi.getViewed();		
	}
	/**
	<p>provides to take a look hesap's all post's interactions</p>
	@param hesap all the post's of this hesap account and it's interactions get viewed
	*/
	public final void viewPostsInteractions(Account hesap){
		if(!checkLog()) return;
		int loop = hesap.getPostNumber();
	
		for(int a =0; a < loop; a++){
		
			viewPostInteractions(hesap.getPost()[a]);
			System.out.printf("\n\n ---------------------------------------");
		}
	}
	
	/**
	<p>provides the view an account ID Username birthdate etc. info's</p>
	@param hesap is the account that is viewed
	*/
	public final void viewProfile(Account hesap){
		if(!checkLog()) return ;
		if(checkBlocked(hesap)){
		
			System.out.printf("\n Error : The account blocked you");	
			return;
		}
			System.out.printf("\nViewing " + hesap.getUsername() + " 's profie...\n");
			System.out.printf(hesap.toString());
	}
	
	/**
	<p>checks wheter this account is followed by hesap</p>
	@param hesap is the account that is checked wheter follow this account or not
	@return kontrol is true when this account is getting followed by hesap
	*/
	public final boolean isFollowed(Account hesap){
		if(!checkLog()) return isLoggedIn;
	
	boolean kontrol = false;
		for(Account p1 : followings){

			if(hesap == p1) kontrol = true;
		}
	return kontrol;
	
	}
	/**
	<p>a getter function</p>
	@return accountID
	*/
	public final String getAccounID()  { return this.accountID;}
	/**
	<p>a getter function</p>
	@return username
	*/
	public final String getUsername()  { return this.username; }
	/**
	<p>a getter function</p>
	@return birthdate
	*/
	public final String getABirthdate(){ return this.birthdate;}
	/**
	<p>a getter function</p>
	@return location
	*/
	public final String getLocation()  { return this.location; }
	/**
	<p>a getter function</p>
	@return posts
	*/
	public final Post[] getPost()      { return this.posts;    }
	/**
	<p>a getter function</p>
	@return followerNumber
	*/
	public final int getFollowerNumber() { return this.followerNumber; }
	/**
	<p>a getter function</p>
	@return followingNumber
	*/
	public final int getFollowingNumber(){ return this.followingNumber;}
	/**
	<p>a getter function</p>
	@return postNumber
	*/
	public final int getPostNumber()   { return this.postNumber;}
	
	/**
	<p> overridin of toString function</p>
	@return a string
	*/
	
	@Override
	public final String toString(){

		String retString;
		
		retString = ("\nUserID = " + accountID + 
			     "\nUsername = " + username + 
			     "\nBirth date = " + birthdate + 
			     "\n" + username + " is following " + String.valueOf(followingNumber) +" account(s) and has " + String.valueOf(followerNumber) + " follower(s) ");
		
		if(followingNumber > 0) {
			retString = retString + "\n" + username +" is following :" ;
			for(int a = 0; a < followingNumber; a++){
			
				retString = retString + " " + followings[a].getUsername() + " , " ;
			}
		}


		if(followerNumber > 0) {
			retString = retString + "\n" + username +	" is followed by :";
			for(int a = 0; a < followerNumber; a++){
			
				retString = retString + " " + followers[a].getUsername() + " , " ;
			}	
	
		}
		retString = retString +  ("\n" + username + " has " + String.valueOf(postNumber) + " post \n");

		
		
		return retString;
	}


}
