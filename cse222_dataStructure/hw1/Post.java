


/**

@author Tarsuslu
*/
public class Post{

	private String postID;
	private	String accountID;
	private String content;
	private int numberOfLikes;
	private int numberOfComments;
	private Account[] likers;
	private Comment[] comments;

	/**
	<p>Constructor of Post class</p>
	@param postid is postid as a string
	@param accountid is an account id number as string
	@param cont is content of post
	*/
	public Post(String postid, String accountid, String cont){
	
		this.postID = postid;
		this.accountID = accountid;
		this.content = cont;
		this.numberOfLikes = 0;
		this.numberOfLikes = 0;
		this.likers = new Account[0];
		this.comments= new Comment[0];
	}

	/**
	<p>a setter for number of likes</p>
	*/
	public void setNumOfLikes() { this.numberOfLikes++; }
	/**
	<p>a setter for number of comments</p>
	*/
	public void setNumOfComments() { this.numberOfComments++; }
	/**
	<p>if a post get comment then comment needs to be added in comments array</p>
	@param yorum is the comment incoming
	*/
	public void getCommented(Comment yorum){
	
		if(comments.length <= numberOfComments){
		
			Comment[] yedek = new Comment[comments.length + 5];	
			for(int a = 0; a < comments.length; a++){
			
				yedek[a] = comments[a];
			}
			yedek[comments.length] = yorum; 
	
			comments = new Comment[yedek.length];
			for(int a = 0; a < comments.length; a++){
			
			comments[a] = yedek[a];
			}
	
		numberOfComments++;	
		}
		
		else {
		
			comments[numberOfComments] = yorum;
			numberOfComments++;
		}
	
	}
	/**
	<p>if a post gets like then the acount that likes the post has to be added in likers array</p>
	@param hesap is the account that liked the post
	*/
	public void getLiked(Account hesap){
		
		if(likers.length <= numberOfLikes){
		
			Account[] yedek = new Account[likers.length + 5];	
			for(int a = 0; a < likers.length; a++){
			
				yedek[a] = likers[a];
			}
			yedek[likers.length] = hesap; 
	
			likers = new Account[yedek.length];
			for(int a = 0; a < likers.length; a++){
			
			likers[a] = yedek[a];
			}
	
		numberOfLikes++;	
		}
		
		else {
		
			likers[numberOfLikes] = hesap;
			numberOfLikes++;
		}
	
	
	}
	/**
	<p>if a viewing request comes this function handle it</p>
	*/
	public void getViewed(){
	
		System.out.printf("\n(postID : " + postID + ") " + accountID + " : " + content + "\n");
		if(numberOfLikes > 0) {
			
			System.out.printf("\nThis post was liked by : ");
			for(int a = 0; a < numberOfLikes; a++){
				
				System.out.printf(likers[a].getUsername() + ", ");
			}
		}
		else System.out.printf("\nThis post has no like");
		if(numberOfComments > 0) {
			
			System.out.printf("\nThis post has %d comment(s) : ", numberOfComments);
			for(int a = 0; a < numberOfComments; a++){
				
				System.out.printf(comments[a].toString());
			}
		}
		else System.out.printf("\nThis post has no comment");
	}
	
	/**
	<p>a getter</p>
	@return postID is a string that represent postID 
	*/
	public final String getPostID()   {return postID;   }
	/**
	<p>a getter</p>
	@return accountID represents account ID
	*/
	public final String getAccountID(){return accountID;}
	/**
	<p>a getter</p>
	@return numberOfLikes is responsible for number of likes
	*/
	public final int getNumberOfLikes(){ return numberOfLikes;}
	/**
	<p>a getter</p>
	@return numberOfComments is responsible for number of comments
	*/
	public final int getNumberOfComments(){return numberOfComments;}
	/**
	<p>a getter</p>
	@return likers is array that includes accounts likes the post
	*/
	public final Account[] getLikers(){ return likers;}
	/**
	<p>a getter</p>
	@return comments is array that includes comments in the post
	*/
	public final Comment[] getComments(){ return comments;}
	
	/**
	<p>overriding of toString function</p>
	@return returns a string
	
	*/
	@Override
	public final String toString(){
		
		return ( "\n(postID : " + postID + ") " + accountID + " : " + content + "\n"  );

	}


}
