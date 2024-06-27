#include<stdio.h>
#include<stdlib.h>

char** generateMap(int,int);
void printMap(char**,int,int);
void printSayacMap(int**,int,int);
void takeXY(int*,int*);
void takeInput(int,int,char**);
void bombaSayac(int**,char**,int,int);
int** generateSayacMap(int,int);
void sayacSay(char**,int**,int,int);
void patlat(char**,int**,int,int,int,int);
void plantBombs(char**,int,int);


int main(){
	int inpX;
	int inpY;
	int numberLoop;
	int corX, corY;
	takeXY(&corX,&corY);
	char** map = generateMap(corX,corY);
	int** sayacMap = generateSayacMap(corX,corY);
	printf("give the number of loop\n");
	scanf("%d",&numberLoop);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
	printMap(map,corX,corY);
	takeInput(corX,corY,map);
	bombaSayac(sayacMap,map,corX,corY);
	for(int a = 0; a < numberLoop; a++){
		sayacSay(map,sayacMap,corX,corY);
		//printSayacMap(sayacMap,corX,corY);
		printMap(map,corX,corY);	
		plantBombs(map,corX,corY);
		bombaSayac(sayacMap,map,corX,corY);
	}
	printf("\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");	
	return 0;
}


char** generateMap(int x, int y){

	char** map;
	map = (char**)malloc(y*sizeof(char*));
	for(int a=0; a < y; a++) map[a] = (char*)malloc(x*sizeof(char));

	for(int a=0; a < y; a++)
		for(int b=0; b < x; b++)
			map[a][b] = '*';
	return map;
}

void printMap(char** map, int x, int y){
	for(int a=0; a < y; a++){
		for(int b=0; b < x; b++){
			printf("%c ",map[a][b]);
		}
		printf("\n");
	}
	printf("\n");

}



int** generateSayacMap(int x,int y){

	int** map;
	map = (int**)malloc(y*sizeof(int*));
	for(int a=0; a < y; a++) map[a] = (int*)malloc(x*sizeof(int));

	for(int a=0; a < y; a++)
		for(int b=0; b < x; b++)
			map[a][b] = 9;
			
	printf("\n");
	return map;
}


void printSayacMap(int** map,int x,int y){
	for(int a=0; a < y; a++){
		for(int b=0; b < x; b++){
			printf("%d ",map[a][b]);
		}
		printf("\n");
	}
}

void takeInput(int x,int y,char** map){
	printf("give an map to plant bomb\n");
	char temp[x];
	for(int a = 0; a < y ; a++){
			scanf("%s",temp);
			for(int b = 0; b < x ; b++){
			map[a][b] = temp[b];
			}
	}
	printf("\n");
	printf("\n");
}

void takeXY(int*corX,int*corY){
	printf("give the size of map(x y format ex: 16 16)\n");
	scanf("%d %d",corX,corY);
}


void patlat(char** map,int** sayacMap,int x,int y ,int sizeX,int sizeY){
	
	
	map[y][x] = '*';
	sayacMap[y][x] = 9;
	if(x > 0){
		map[y][x-1] = '*';
		sayacMap[y][x-1] = 9;
	}
	if(x < sizeX-1){
		if(sayacMap[y][x+1] != 1){
			map[y][x+1] = '*';
			sayacMap[y][x+1] = 9;
		}
	}
	if(y > 0){
		map[y-1][x] = '*';
		sayacMap[y-1][x] = 9;
	}
	if(y < sizeY-1){
		if(sayacMap[y+1][x] != 1){
			map[y+1][x] = '*';
			sayacMap[y+1][x] = 9;
		}
	}
}
void sayacSay(char** map,int** sayacMap,int sizeX, int sizeY){
	int temp = 0;
	for(int a = 0; a < sizeY; a++){
		for(int b = 0; b < sizeX; b++){
			if(sayacMap[a][b] != 9 ){
				sayacMap[a][b] = sayacMap[a][b] -1 ;
				if(sayacMap[a][b] == 0)
					patlat(map,sayacMap,b,a,sizeX,sizeY);
			}
		}
	}
}
void plantBombs(char** map,int x,int y){
	for(int a=0; a < y; a++){
		for(int b=0; b < x; b++){
			if(map[a][b] != 'B') map[a][b] = 'B';
		}
	}
}
void bombaSayac(int** sayacMap,char** map,int x, int y){
	
	for(int a = 0; a < y; a++){
		for(int b = 0; b < x; b++){
			if(map[a][b] == 'B' && sayacMap[a][b] == 9){
				sayacMap[a][b] = 3;
			}
		}
	}
}
