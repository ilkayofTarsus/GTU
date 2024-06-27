#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <signal.h>
#include "common.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#define FIFO_PATH "./myfifo"
#define BUFFER_SIZE 256

int sockfd, portno, n;
struct sockaddr_in serv_addr;
char buffer[256];
int fd;


void writeToLog(const char *message) {

    FILE *file;
    file = fopen("logClient.txt", "a"); 
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
    sleep(0.1);
}


void error(const char *msg) {
    perror(msg);
    exit(1);
}

void signalHandler(int signal) {
		
	printf("\t Quiting.. Writing Log file");
	writeToLog("Client sent Ctrl+C signal... Terminated");
	char kapat[7] = "sigint";

    size_t size = write(fd, kapat, 7*sizeof(char));
    printf("mesage == %s sizet == %d",kapat,size);
    close(fd);

	close(sockfd);
	exit(1);
}

struct Order generateOrder(int p, int q){
	struct Order order;
    int min_range_p = -p/2;
    int max_range_p = p/2;
    int min_range_q = -q/2;
    int max_range_q =  q/2;


	do{
	order.p = (rand() % (max_range_p - min_range_p + 1)) + min_range_p;
	order.q = (rand() % (max_range_q - min_range_q + 1)) + min_range_q;
	}while(order.p == 0 && order.q == 0);
	order.delivered = 0;
	order.orderId = 0;
	order.readyToEat = 0;
	return order;
}


int main(int argc , char* argv[]) {

	if(argc != 6){
		perror("Gİve correct arguments");
		exit(-1);
	}
signal(SIGINT, signalHandler);
	// Bağlantı kurma
	/////////////////////////////

	
	int numOfClients, p , q ;
    char* ip = argv[1];
 	portno = atoi(argv[2]);
	numOfClients = atoi(argv[3]);
	p = atoi(argv[4]);
	q = atoi(argv[5]);
	
    fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
	
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
    }
	/////////////////////////////
    srand(time(NULL));
    int pid = getpid();
    printf("\n\t<<PID %d\n",pid);
    printf("\t<< ... \n");
	struct Order *orders = malloc(numOfClients * sizeof(struct Order));
	for(int a = 0 ; a < numOfClients; a++){
		orders[a] = generateOrder(p,q);
	}

	if (write(sockfd, &numOfClients, sizeof(int)) < 0) {
        error("ERROR writing numofclient to socket");
    }
	if (write(sockfd, orders, numOfClients * sizeof(struct Order)) < 0) {
        error("ERROR writing to socket");
    }
  	
  	if (write(sockfd, &pid, sizeof(int)) < 0) {
        error("ERROR writing to socket");
    }
  
  	struct MessageToClient* mesaj = malloc(sizeof(struct MessageToClient));
    for(int a = 0 ;  a < numOfClients*3; a++){
		if (read(sockfd, mesaj, sizeof(struct MessageToClient)) < 0) {
	        error("ERROR reading fron socket");
	    }	
		char logMessage[100];
		if(mesaj->durum == 1){
			snprintf(logMessage, sizeof(logMessage), "Your order %d is in oven",mesaj->orderId);
			writeToLog(logMessage);
		}
		if(mesaj->durum == 2){
			snprintf(logMessage, sizeof(logMessage), "Your order %d is taken from oven",mesaj->orderId);
			writeToLog(logMessage);
		}
		if(mesaj->durum == 3){
			snprintf(logMessage, sizeof(logMessage), "Moto is carrying your order %d ",mesaj->orderId);
			writeToLog(logMessage);
		}
	}
    
	size_t size = write(fd, "aaaaaa", 7*sizeof(char));
   	printf("\t<< All customers served\n");
   	printf("\t<< log file written ...\n");
    
	close(fd);
    close(sockfd);
    free(orders);
    free(mesaj);
    return 0;
}

