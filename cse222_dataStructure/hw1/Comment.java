




public class Comment extends Interaction{

	private String content;

	public Comment(String interaction, String account, String post, String cont){
	
		super(interaction,account,post);
		this.content = cont ;
	}

	public final String toString(){
	
		return ("\nComment " + this.interactionID + ": " + "'" + this.accountID + "' said '" + this.content + "'" );
	
	}

}
