#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <complex.h>
#include <lapacke.h>
#include <pthread.h> 
#include <time.h>
#include <math.h>
#include <signal.h>
#include "common.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#define FIFO_PATH "./myfifo"
#define BUFFER_SIZE 256
struct CookArgs {
    double mealPrepTime;
    double cookTime;
    int id;
};
struct Node {
    struct Order order;
    struct Node* next;
};
struct Queue {
    struct Node* front;
    struct Node* rear;
};
struct OpeningPlace {
    int free;
};
struct Oven {
    int capacity;
    int size;
    struct Order* orderInOven;
};

struct Aparat{
	int id;
	int free;
};

struct DeliveryPerson{
	int id;
	int capacity;
	int size;
	int onRoad;
	int speed;
	int amountOfDeliveries;
	int locationQ;
	int locationP;
	struct Queue *ordersInBag;
};
struct CookPerson{
	int id;
	int amountOfOrder;
	int onOven;
};



struct Node* newNode(struct Order order);
struct Queue* createQueue();
void error(const char *msg);
void enqueue(struct Queue* q, struct Order order);
struct Order dequeue(struct Queue* q);
int isEmpty(struct Queue* q);
struct Node* peek(struct Queue* q);
struct Order take_order();
struct Aparat* chooseAparat();
struct OpeningPlace* choosePlace();
void giveAparat(struct Aparat* aparat);
void freePlace(struct OpeningPlace* place);
void* functionCook(void*args);
double calculatePrepTime();
void* functionManager(void* args);
int kacEleman(struct Queue* q);
void giveOrderToMoto(int id, int orderCount);
int findFreeMoto();
void* functionMoto(void* args);
void carryOrders(int id);
void carryToClient(struct Order order, int id);
int ordersFinish();
int findBestMoto();
int findBestCook();
void backToShop(int id);
void putToOven(int cookId, struct Order order);
void takeFromOven(int cookId, int orderId);
void* startPool(void *args);
int findMeal();
void giveFireToMeal(int mealId);
int isAnyMealReady();
void freeQueue(struct Queue* q);
void writeToLog(const char *message);
void* terminate(void* args);
double calculateMealTime();

int pid;
int delPool,cookPool;
int numReadyOrders = 0;
int deliveredOrders = 0;
int numOfClients = 0;
int isFirst= 0;
    int sockfd, newsockfd;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
char buffer[BUFFER_SIZE];
int fd;
struct DeliveryPerson* motos;
struct CookPerson* cooks;
struct Queue* unready;
struct Queue* ready;
struct OpeningPlace* openingPlaces;
struct Oven oven;
struct Order *orders;
struct Aparat* aparats;
pthread_mutex_t mutex_aparat;
pthread_mutex_t mutex_place;
pthread_mutex_t mutex_order;
pthread_mutex_t mutex_oven;
pthread_mutex_t mutex_oven_find;
pthread_mutex_t mutex_moto;
pthread_mutex_t mutex_ready_order;
pthread_cond_t cond_oven;
pthread_cond_t cond_meal_added;

void signalHandler(int signal) {
		
	printf("\t Quiting.. Writing Log file");
	pthread_mutex_destroy(&mutex_order);
	pthread_mutex_destroy(&mutex_moto);
	pthread_mutex_destroy(&mutex_oven);
	pthread_mutex_destroy(&mutex_oven_find);
	pthread_mutex_destroy(&mutex_ready_order);
	pthread_mutex_destroy(&mutex_aparat);
	pthread_mutex_destroy(&mutex_place);
	pthread_cond_destroy(&cond_oven);
	pthread_cond_destroy(&cond_meal_added);
	for (int a = 0; a < delPool; a++) {
        freeQueue(motos[a].ordersInBag); 
    }
	freeQueue(unready);
	freeQueue(ready);
	free(cooks);
    free(aparats);
    free(openingPlaces);
    free(oven.orderInOven);
    free(motos);
   	close(newsockfd);
    close(sockfd);
	exit(1);
}


int main(int argc , char* argv[]) {

	if(argc != 6){
		perror("Gİve correct arguments");
		exit(-1);
	}
	
	signal(SIGINT, signalHandler);

	// variables
	////////////////////

	double mealPrepTime, cookTime;
	int  speed, portno;
	int prevSize=0;
	char* ip = argv[1];
 	portno = atoi(argv[2]);
	cookPool =  atoi(argv[3]);
	delPool =  atoi(argv[4]);
	speed =  atoi(argv[5]);

while(1){
	
	fd = 0;
	newsockfd = 0; sockfd = 0; 
	oven.capacity = 6;
	oven.size = 0;
	oven.orderInOven = malloc(6 * sizeof(struct Order));
	
	int numberOfPlaces = 3;
	openingPlaces = malloc(numberOfPlaces * sizeof(struct OpeningPlace));
	for(int a = 0; a < numberOfPlaces; a++ ){ openingPlaces[a].free = 1 ; }
	
	int numberOfAparats = 3;
	aparats = malloc(numberOfAparats * sizeof(struct Aparat));
	for(int a = 0; a < numberOfAparats; a++ ){ aparats[a].id = a ; aparats[a].free = 1; }


	motos = malloc(delPool * sizeof(struct DeliveryPerson));
	for(int a = 0 ; a < delPool ; a++){
		motos[a].id = a;
		motos[a].capacity = 3;
		motos[a].size = 0;
		motos[a].amountOfDeliveries = 0;
		motos[a].onRoad = 0;
		motos[a].locationQ = 0;
		motos[a].locationP = 0;
		motos[a].speed = speed;
		motos[a].ordersInBag = createQueue();

	}
	cooks = malloc(cookPool * sizeof(struct CookPerson));
	for(int a = 0 ; a < cookPool ; a++){
		cooks[a].id = a;
		cooks[a].amountOfOrder = 0;
		cooks[a].onOven = 0;
	
	}
	unready = createQueue();
	ready = createQueue();

	pthread_mutex_init(&mutex_order, NULL);
	pthread_mutex_init(&mutex_moto, NULL);
	pthread_mutex_init(&mutex_ready_order, NULL);
	pthread_mutex_init(&mutex_place, NULL);
	pthread_mutex_init(&mutex_aparat, NULL);
	pthread_mutex_init(&mutex_oven, NULL);
	pthread_mutex_init(&mutex_oven_find, NULL);
	pthread_cond_init(&cond_oven, NULL);
	pthread_cond_init(&cond_meal_added, NULL);
	pthread_t cookMeals[6];
	pthread_t manager;
	pthread_t sigHand;
	pthread_t cookers[cookPool];
	pthread_t motos_t[delPool];
	pthread_t deliveries[delPool];
	////////////////////

	printf("\n\t<<  PideShop active waiting for connection ... \n");
	// Bağlantı kurma
	////////////////////	


    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }
	if (mkfifo(FIFO_PATH, 0666) == -1) {
		if (errno != EEXIST) {
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    }
    fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(portno);
	
	int opt = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		error("setsockopt failed");
	}
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) {
        error("ERROR on accept");
    }
	//////////////////////
	mealPrepTime = calculatePrepTime();
	cookTime = mealPrepTime / 2 ;
    // orderları alma
    /////////////////////
    if (read(newsockfd, &numOfClients, sizeof(int)) < 0) {
        error("ERROR reading from socket");
    }
   	
	if(){}
	if (prevSize == 0) {
    orders = malloc(numOfClients * sizeof(struct Order));
    if (orders == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }
} else {
    orders = realloc(orders, numOfClients * sizeof(struct Order));
    if (orders == NULL) {
        free(orders); // realloc başarısız oldu, eski bloğu serbest bırak
        perror("Error reallocating memory");
        exit(EXIT_FAILURE);
    }
}

	
	printf("\t<<  %d new customers... Serving \n ",numOfClients);
    if (read(newsockfd, orders, numOfClients * sizeof(struct Order)) < 0) {/*numOfClients*sizeof(struct Order)*/
      error("ERROR reading from socket");
    }
    
    if (read(newsockfd, &pid, sizeof(int)) < 0) {
    	error("ERROR reading from socket");
    }
    
    
    for(int a = 0 ; a < numOfClients ; a++){
	 orders[a].orderId = a;
	 enqueue(unready,orders[a]);    
    }
    /////////////////////
   	for (int i = 0; i < 6; ++i) {
		pthread_create(&cookMeals[i], NULL, startPool, NULL);   	
    
    }
    int* args_moto;
    struct CookArgs* args_cook;
    pthread_create(&manager, NULL, functionManager, NULL);
   	for (int i = 0; i < cookPool; ++i) {
        args_cook = malloc(sizeof(struct CookArgs));
        args_cook->mealPrepTime = mealPrepTime;
        args_cook->cookTime = cookTime;
        args_cook->id = i;
		pthread_create(&cookers[i], NULL, functionCook, (void*) args_cook);
	}
   	for (int i = 0; i < delPool; i++) {
		args_moto = malloc(sizeof(int));
		args_moto[0] = i;
		pthread_create(&motos_t[i], NULL, functionMoto, (void*) args_moto);
		
	}
	pthread_create(&sigHand, NULL, terminate, NULL);
	for (int i = 0; i < cookPool; ++i) {
		pthread_join(cookers[i], NULL);
	}
	for (int i = 0; i < delPool; ++i) {
		pthread_join(motos_t[i], NULL);
	}
	pthread_join(manager, NULL);     
	pthread_cond_broadcast(&cond_meal_added);
   	for (int i = 0; i < 6; ++i) {
		pthread_join(cookMeals[i], NULL);   	
    }
   pthread_join(sigHand, NULL);     
	printf("\t<<  Done serving client PID %d \n",pid);
	int id_cook = findBestCook();
	int id_moto = findBestMoto();
	printf("\t<<  Thanks Cook %d and Moto %d \n",id_cook,id_moto);
    
	pthread_mutex_destroy(&mutex_order);
	pthread_mutex_destroy(&mutex_moto);
	pthread_mutex_destroy(&mutex_oven);
	pthread_mutex_destroy(&mutex_oven_find);
	pthread_mutex_destroy(&mutex_ready_order);
	pthread_mutex_destroy(&mutex_aparat);
	pthread_mutex_destroy(&mutex_place);
	pthread_cond_destroy(&cond_oven);
	pthread_cond_destroy(&cond_meal_added);
	free(orders);
	close(newsockfd);
    close(sockfd);
	free(args_moto);
	free(args_cook);
 	for (int a = 0; a < delPool; a++) {
        freeQueue(motos[a].ordersInBag); 
    }
	freeQueue(unready);
	freeQueue(ready);
	free(cooks);
    free(aparats);
    free(openingPlaces);
    free(oven.orderInOven);
    free(motos);
    close(fd);
    printf("\t<< active ..\n");
    prevSize += numOfClients;
    isFirst = 1;
}
    return 0;
}
double calculateMealTime() {
	
	int M = 30, N = 40;

    lapack_complex_double A[M*N];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            A[i*N + j] = i + j * I;
        }
    }

    lapack_complex_double U[M*M];
    lapack_complex_double VT[N*N];
    double S[N];
    lapack_complex_double superb[N-1];
    lapack_complex_double work[M*N];
    int lwork = M*N;
    int info;

    clock_t start, end;
    double cpu_time_used;
    start = clock();

	info = LAPACKE_zgesdd(LAPACK_ROW_MAJOR, 'A', M, N, A, N, S, U, M, VT, N);
    if (info > 0) {
        printf("The algorithm computing SVD failed to converge.\n");
        exit(1);
    }

    lapack_complex_double A_pinv[N*M]; 

    for (int i = 0; i < N*M; i++) {
        A_pinv[i] = 0.0 + 0.0 * I;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < M; k++) {
                if (S[k] > 1e-10) { 
                    A_pinv[i*M + j] += conj(VT[i*N + k]) * (1.0 / S[k]) * conj(U[j*M + k]);
                }
            }
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	return cpu_time_used;

}


double calculatePrepTime() {
	
	int M = 30, N = 40;

    lapack_complex_double A[M*N];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            A[i*N + j] = i + j * I;
        }
    }

    lapack_complex_double U[M*M];
    lapack_complex_double VT[N*N];
    double S[N];
    lapack_complex_double superb[N-1];
    lapack_complex_double work[M*N];
    int lwork = M*N;
    int info;

    clock_t start, end;
    double cpu_time_used;
    start = clock();

	info = LAPACKE_zgesdd(LAPACK_ROW_MAJOR, 'A', M, N, A, N, S, U, M, VT, N);
    if (info > 0) {
        printf("The algorithm computing SVD failed to converge.\n");
        exit(1);
    }

    lapack_complex_double A_pinv[N*M]; 

    for (int i = 0; i < N*M; i++) {
        A_pinv[i] = 0.0 + 0.0 * I;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < M; k++) {
                if (S[k] > 1e-10) { 
                    A_pinv[i*M + j] += conj(VT[i*N + k]) * (1.0 / S[k]) * conj(U[j*M + k]);
                }
            }
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	return cpu_time_used;

}


struct Node* newNode(struct Order order) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->order = order;
    temp->next = NULL;
    return temp;
}

struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

void error(const char *msg) {
    perror(msg);
    exit(1);
}


void enqueue(struct Queue* q, struct Order order) {
    struct Node* temp = newNode(order);

    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
    
}

struct Order dequeue(struct Queue* q) {
    if (q->front == NULL) {
        error("Queue is empty\n");
    }

    struct Node* temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    struct Order data = temp->order;
    free(temp);
    return data;
}

int isEmpty(struct Queue* q) {
    return q->front == NULL;
}

struct Node* peek(struct Queue* q) {
    if (q->front == NULL) {
        return NULL;

    }
    return q->front;
}
struct Order take_order(){
	struct Order order;	
	order = dequeue(unready);
	return order;
}

struct Aparat* chooseAparat(){
	int a = 0;
	struct Aparat* aparat;
	pthread_mutex_lock(&mutex_aparat);
	do{
		a = a%3;		
		aparat = &aparats[a];
		if(aparat->free){
			aparat->free = 0;
			break;
		}
		a++;
	}while(1);
	pthread_mutex_unlock(&mutex_aparat);
	return aparat;
}
struct OpeningPlace* choosePlace(){
	int a = 0;
	struct OpeningPlace* place;
	pthread_mutex_lock(&mutex_place);
	do{
		a = a%2;		
		place= &openingPlaces[a];
		if(place->free){
			place->free = 0;
			break;
		}
		a++;
	}while(1);
	pthread_mutex_unlock(&mutex_place);
	return place;
}

void giveAparat(struct Aparat* aparat){
	aparat->free = 1;
}


void freePlace(struct OpeningPlace* place){
	place->free = 1;
}


void* functionCook(void* args){

	struct Aparat* chosenAparat;
	struct OpeningPlace* chosenPlace;
    struct CookArgs* cookArgs = (struct CookArgs*) args;
    double prepTime = cookArgs->mealPrepTime;
    double mealTime = cookArgs->cookTime;
    int id = cookArgs->id;
	while(!isEmpty(unready) || oven.size != 0){

		if(oven.size < 6 && !isEmpty(unready) ){
			struct Order order;
			pthread_mutex_lock(&mutex_order);
			if(!isEmpty(unready)){ 
				cooks[id].onOven = 1;
				order = take_order();
				char logMessage[256];
			    snprintf(logMessage, 256*sizeof(char), "Cook %d put order %d in oven",id,order.orderId);
				writeToLog(logMessage);
				struct MessageToClient* mesaj= malloc(sizeof(struct MessageToClient));
				mesaj->orderId = order.orderId;
				mesaj->durum = 3;
				if (write(newsockfd, mesaj, sizeof(struct MessageToClient)) < 0) {
					free(mesaj); // Hata durumunda belleği serbest bırak
					error("ERROR writing to socket");
				}
				free(mesaj);
			}
			else{ pthread_mutex_unlock(&mutex_order); break; }
			pthread_mutex_unlock(&mutex_order);
			putToOven(id,order);
		}else if(oven.size == 6 || isEmpty(unready)){
			int mealId = isAnyMealReady();
			takeFromOven(id,mealId);
			if(mealId != -1) {
				char logMessage[256];
				snprintf(logMessage, 256*sizeof(char), "Cook %d take order %d from oven",id,mealId);
				writeToLog(logMessage);
	
				struct MessageToClient* mesaj= malloc(sizeof(struct MessageToClient));
				mesaj->orderId = mealId;
				mesaj->durum = 3;
				if (write(newsockfd, mesaj, sizeof(struct MessageToClient)) < 0) {
					free(mesaj); // Hata durumunda belleği serbest bırak
					error("ERROR writing to socket");
				}
				free(mesaj);	
			}
		}else{
			printf("senkronizasyon hatası");
		}

	}
//	free(cookArgs);
}


void putToOven(int cookId, struct Order order){
	
	struct Aparat* chosenAparat;
	struct OpeningPlace* chosenPlace;

	pthread_mutex_lock(&mutex_oven);
	while (oven.size >= oven.capacity) {
		pthread_cond_wait(&cond_oven, &mutex_oven);
	}
	chosenAparat = chooseAparat();
	chosenPlace = choosePlace();	
	calculatePrepTime();//sleep(prepTime);												// hazırlık yap	
	if(oven.size < oven.capacity){
		oven.orderInOven[oven.size] = order;
		oven.size++;
	}else printf("cook %d kapasiteyi aştı HATA \n",cookId);
	pthread_cond_signal(&cond_meal_added);
	pthread_mutex_unlock(&mutex_oven);
	

	giveAparat(chosenAparat);
	freePlace(chosenPlace);
	cooks[cookId].amountOfOrder++;		

}

void takeFromOven(int cookId, int orderId){

	struct Aparat* chosenAparat;
	struct OpeningPlace* chosenPlace;
	struct Order order;
	for(int a = 0 ; a < oven.size ; a++){
		pthread_mutex_lock(&mutex_ready_order);
		if(oven.orderInOven[a].orderId == orderId){

			order = oven.orderInOven[a]; 
			pthread_mutex_lock(&mutex_oven);
			for(int b = a; b < oven.size - 1 ; b++){
				oven.orderInOven[b] = oven.orderInOven[b+1]; 
			}
			
			oven.size--;
			pthread_mutex_unlock(&mutex_oven);

			chosenPlace = choosePlace();
			chosenAparat = chooseAparat();
			enqueue(ready,order);
			numReadyOrders++;
			giveAparat(chosenAparat);
			freePlace(chosenPlace);
			cooks[cookId].onOven = 0;
			pthread_cond_broadcast(&cond_oven);
		}
		pthread_mutex_unlock(&mutex_ready_order); /////// bu mutexe dikkat mutex içinbde mutex var
	}
	
}

void* startPool(void *args){

	while(!ordersFinish()){
			pthread_mutex_lock(&mutex_oven);
			while(oven.size == 0 && !ordersFinish()){
				pthread_cond_wait(&cond_meal_added,&mutex_oven);
			}	
			int mealId = findMeal();
			giveFireToMeal(mealId);
			pthread_mutex_unlock(&mutex_oven);
	}
}

int findMeal(){
	int id = -1;
	pthread_mutex_lock(&mutex_oven_find);
	for(int a = 0 ; a < oven.size ; a++){
		if(oven.orderInOven[a].readyToEat == 0)
			id = oven.orderInOven[a].orderId;
	}	
	pthread_mutex_unlock(&mutex_oven_find);
	return id;

}
void giveFireToMeal(int mealId){
	calculateMealTime();
	for(int a = 0 ; a < oven.size; a++){
		if(oven.orderInOven[a].orderId == mealId)
			oven.orderInOven[a].readyToEat = 1;
	
	}
}
int isAnyMealReady(){
	int id = -1;	
	pthread_mutex_lock(&mutex_oven);

	for(int a = 0 ; a < oven.size ; a++){
		if(oven.orderInOven[a].readyToEat == 1)
			id = oven.orderInOven[a].orderId;
	}
	pthread_mutex_unlock(&mutex_oven);
	return id;	
}


void* functionManager(void* args){

	while( !ordersFinish() || kacEleman(unready)) {
		if(kacEleman(ready) >= 3){
			int id = findFreeMoto();
			giveOrderToMoto(id,3);
		}	
		else if(isEmpty(unready) && kacEleman(ready) < 3 && kacEleman(ready) > 0){
			int id = findFreeMoto();
			int orderCount = kacEleman(ready);
			giveOrderToMoto(id,orderCount);
		}
	}
}
int kacEleman(struct Queue* q){
	int sayac = 0;
	struct Node* temp = peek(q); 
	while(!(temp == NULL)){
		sayac++;
		temp = temp->next;		
	}
	return sayac;

}
void* functionMoto(void* args){
	int* motoId = (int*) (args);
	while( !ordersFinish() ){
		if(motos[*motoId].onRoad){
			carryOrders(*motoId);		
			motos[*motoId].onRoad = 0;
		}
	}
}

int findFreeMoto(){
	int id = 0;
	while(1){
		id = id%delPool;
		if(!motos[id].onRoad && motos[id].size < 3)
			break;						
		id++;
	}
	return id;
}

void giveOrderToMoto(int id, int orderCount){
	for(int a = 0; a < orderCount ; a++){
		pthread_mutex_lock(&mutex_ready_order);
		struct Order order = dequeue(ready);
		pthread_mutex_unlock(&mutex_ready_order);
		pthread_mutex_lock(&mutex_moto);
		enqueue( motos[id].ordersInBag , order ) ;		
		motos[id].size++;
		motos[id].onRoad = 1;
		pthread_mutex_unlock(&mutex_moto);
	}
}

void carryOrders(int id){
	while(!isEmpty(motos[id].ordersInBag )&& motos[id].size != 0){
		pthread_mutex_lock(&mutex_moto);
		struct Order order = dequeue(motos[id].ordersInBag);
		pthread_mutex_unlock(&mutex_moto);
		carryToClient(order,id);
		motos[id].amountOfDeliveries++;
		motos[id].size--;
	}
	backToShop(id);
}
void carryToClient(struct Order order, int id){
	int motoSpeed = motos[id].speed;
	int motoQ = motos[id].locationQ;
	int motoP = motos[id].locationP;
	int orderQ = order.q;
	int orderP = order.p;
	
	double motoSpeed_km_second = motoSpeed * 1.6 / 100000;
	
	int distanceKm =  sqrt( ((motoQ - orderQ) * (motoQ - orderQ)) + ((motoP - orderP) * (motoP - orderP))  );
	int carryTime = distanceKm / motoSpeed_km_second;

	struct MessageToClient* mesaj= malloc(sizeof(struct MessageToClient));
	mesaj->orderId = order.orderId;
	mesaj->durum = 3;
	if (write(newsockfd, mesaj, sizeof(struct MessageToClient)) < 0) {
		free(mesaj); // Hata durumunda belleği serbest bırak
		error("ERROR writing to socket");
	}
	free(mesaj);
	
	sleep(carryTime);					/// taşıma süresi
	motos[id].locationQ = orderQ;
	motos[id].locationP = orderP;
	pthread_mutex_lock(&mutex_order);
	deliveredOrders++;
	pthread_mutex_unlock(&mutex_order);
	char logMessage[256];
    snprintf(logMessage, 256*sizeof(char), "Moto %d delivered order %d to p -> %d , q -> %d",id,order.orderId,order.p,order.q);
	writeToLog(logMessage);
	
}

int ordersFinish(){
	return deliveredOrders == numOfClients;
}

int findBestCook(){
	int id_cook;
	int works= -1;
	
	for(int a = 0 ; a < cookPool ; a++){
		if(works < cooks[a].amountOfOrder){
			works = cooks[a].amountOfOrder;
			id_cook = a;
		}
			
	}	
	return id_cook;
}
int findBestMoto(){
	int id_moto;
	int works= -1;
	
	for(int a = 0 ; a < delPool ; a++){
		if(works < motos[a].amountOfDeliveries){
			works = motos[a].amountOfDeliveries;
			id_moto = a;
		}
			
	}	
	return id_moto;
}
void backToShop(int id){
	int motoSpeed = motos[id].speed;
	int motoQ = motos[id].locationQ;
	int motoP = motos[id].locationP;
	int orderQ = 0;
	int orderP = 0;
	
	double motoSpeed_km_second = motoSpeed * 1.6 / 100000;
	
	int distanceKm =  sqrt( ((motoQ - orderQ) * (motoQ - orderQ)) + ((motoP - orderP) * (motoP - orderP))  );
	int carryTime = distanceKm / motoSpeed_km_second;
	sleep(carryTime);					/// dönme süresi

	motos[id].locationQ = 0;
	motos[id].locationP = 0;

}
void freeQueue(struct Queue* q) {
    struct Node* current = q->front;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(q);
}

void writeToLog(const char *message) {
    FILE *file;
    file = fopen("logServer.txt", "a"); 
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S] ", timeinfo);
    fprintf(file, "%s %s\n", timestamp, message);

    fclose(file);
}

void* terminate(void* args){
	char sigint[7];
	ssize_t bytesRead = read(fd, sigint, 7*sizeof(char) );
	if (bytesRead == -1){
		perror("read");
		close(fd);
		exit(EXIT_FAILURE);
	} else if (bytesRead == 0) {
	}
	if(strcmp(sigint,"sigint") == 0){
		printf("Order cancelled PID %d\n",pid);
		
		char logMessage[100];
	 	for (int a = 0; a < delPool; a++) {
        	freeQueue(motos[a].ordersInBag); 
		}
		freeQueue(unready);
		freeQueue(ready);
		free(cooks);
		free(aparats);
		free(openingPlaces);
		free(oven.orderInOven);
		free(motos);
		pthread_mutex_lock(&mutex_order); 			// her mutex kılıtlı mı kontorlu yapılıp yokediliyor
		pthread_mutex_unlock(&mutex_order);
		pthread_mutex_destroy(&mutex_order);
		pthread_mutex_lock(&mutex_order);
		pthread_mutex_unlock(&mutex_order);
		pthread_mutex_destroy(&mutex_moto);
		pthread_mutex_lock(&mutex_oven);
		pthread_mutex_unlock(&mutex_oven);
		pthread_mutex_destroy(&mutex_oven);
		pthread_mutex_lock(&mutex_ready_order);
		pthread_mutex_unlock(&mutex_ready_order);
		pthread_mutex_destroy(&mutex_ready_order);
		pthread_mutex_lock(&mutex_aparat);
		pthread_mutex_unlock(&mutex_aparat);
		pthread_mutex_destroy(&mutex_aparat);
		pthread_mutex_lock(&mutex_order);
		pthread_mutex_unlock(&mutex_order);
		pthread_mutex_destroy(&mutex_place);
		pthread_cond_destroy(&cond_oven);
		pthread_cond_destroy(&cond_meal_added);
		close(newsockfd);
		close(sockfd);
		close(fd);
		exit(1);	
	}
}
