


public class Message{

	private String messageID;
	private String senderID;
	private String receiverID;
	private String content;
	
	public Message(String mesaj, String sender, String receiver, String cont){
	
		this.messageID = mesaj;
		this.senderID = sender;
		this.receiverID = receiver;
		this.content = cont;
	
	}	
	public final String getMessageID(){return messageID;}
	public final String getSenderID(){return senderID;}
	public final String getReceiverID(){return receiverID;}

	@Override
	public final String toString(){
	
	return ( "\nMessageID : " + messageID +
		 "\nFrom: " + senderID + 
		 "\nto: " + receiverID +
		 "\nMessage : " + content);
	
	
	}




}
