

public class Interaction{

	
	protected String interactionID;
	protected String accountID;
	protected String postID;
	
	public final String getInteractionID(){return interactionID;}
	public final String getAccountID(){return accountID;}
	public final String getPostID(){return postID;}	
	public Interaction(String interaction, String account, String post){
	
		this.interactionID = interaction;
		this.accountID = account;
		this.postID = post;
	}


}
