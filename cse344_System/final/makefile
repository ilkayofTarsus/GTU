all: clean compilePide compileClient
clean:
	@rm HungeryVeryMuch
	@rm PideShop
	@rm logServer.txt
	@rm logClient.txt

compilePide:
	@gcc PideMain.c -o PideShop -llapacke -lm
compileClient:
	@gcc Client.c -o HungeryVeryMuch
