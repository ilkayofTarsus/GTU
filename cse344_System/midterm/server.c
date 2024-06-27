#include<stdio.h>
#include<stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include"server.h"
#include"SC_lib.h"
#define DIRNAME "/tmp/%s"
#define LOGFILE "/tmp/%s/logfile"
int child_count = 0;

struct queue {
	int capacity;
	int size;
	int last_client;
	
	struct client_t **clients;
	int first_client;
	
};
void serve();
int kelimeSay(char *string);
int kelimeAyir(char *string, char **kelimeler);
int create_q(struct queue *clients);
int sirala(struct queue *que, struct client_t *item);
int resize(struct queue *que);
void child_handler(int sig);
void create_dir(char dirname[],char path[]);
void save_log(char message[],char dirname[]);

int main(int args, char* argv[]){

	//Argvden gelen dosya ismi ile dosya oluşturma
	char dirname[256]; 
	char path[256];
	struct queue client_q;	
	strcpy(dirname, argv[1]);
	snprintf(path, sizeof(path), DIRNAME, dirname);
	printf("Tam yol: %s\n", path);
	create_dir(dirname,path);
	
	// logdile oluşturma
	snprintf(path, sizeof(path), LOGFILE, dirname);
	int log_fd = open(path,O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (log_fd == -1) {
		perror("open"); 
		exit(EXIT_FAILURE); 
	}
	close(log_fd);

	int max_client;
	args_handler_server(args,argv,&max_client);
	if (mkfifo(FIFO, 0666) == -1 && errno != EEXIST) {
		perror("mkfifo");
		exit(EXIT_FAILURE);
	}
	if (mkfifo(FIFO2, 0666) == -1 && errno != EEXIST) {
		perror("mkfifo");
		exit(EXIT_FAILURE);
	}
	if (mkfifo(FIFO3, 0666) == -1 && errno != EEXIST) {
		perror("mkfifo");
		exit(EXIT_FAILURE);
	}
	struct sigaction sa;
	sa.sa_handler = child_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	
	sigset_t sigmask;
	sigemptyset(&sigmask);
	sigaddset(&sigmask, SIGINT);

	
	int* array = (int *)malloc(9 * sizeof(int));
	char* str = (char *)malloc(5 * sizeof(char));
	int mult=1;
	int fd= open(FIFO, O_RDONLY);
	if (fd == -1) {
		perror("open");
		free(array);
		free(str);
		exit(EXIT_FAILURE);
	}
	struct client_t new_cl;
	int dummy_fd;
	if ((dummy_fd = open(FIFO, O_WRONLY)) == -1) return -1;

	create_q(&client_q);
	while(1){

		int num_read;
		num_read = read(fd, &new_cl, sizeof(struct client_t));
		if(num_read == -1){
	                continue;
		}else{
			if(child_count <= atoi(argv[2])){
				int pid = fork();
				child_count++;
				if(pid == -1){
					return -1;
				}
				else if(pid == 0){
					printf("newcl pid == %d, tryconnext == %d\n",new_cl.cl_pid,new_cl.try_connect);
					printf("child count == %d\n",child_count);
					while(1){ serve();}
					printf("exit_success\n");
					exit(EXIT_SUCCESS);

				}
				
				
			}
			else{
				if(new_cl.try_connect){
					printf("client has tryConnect argument so does not wait PID == %d\n",new_cl.cl_pid);
				}
				else{
					printf("client %d is put the queue\n",new_cl.cl_pid);	
					sirala(&client_q,&new_cl);
				}	
			}
		}
	}	
	close(fd);
	close(dummy_fd);
	free(array);
	free(str);
	return 0;
}

int args_handler_server(int args, char* argv[], int* max_client){
	
	if(args != 3) return -1;
	char* dir_name = argv[1];
	*max_client = atoi(argv[2]);
}	
void child_handler(int sig) {
	pid_t pid;
	int status;
	while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
		printf("Child process with PID %d has exited. status == %d\n", pid,status);
		child_count--;
	}
}

void create_dir(char dirname[],char path[] ){
	if (access(path, F_OK) != -1) {
		printf("Directory already exists: %s\n", dirname);
	} else {
		if (mkdir(path, 0777) == -1) {
			perror("Dizin oluşturma hatası");
			exit(EXIT_FAILURE);
		}
			printf("Directory is created: %s\n", dirname);
	}
}

void save_log(char message[],char dirname[] ){
	char path[256];
	char yazilacak[256];
	snprintf(path, sizeof(path), LOGFILE, dirname);
	int dosya_fd = open(path, O_WRONLY | O_CREAT | O_APPEND);
	strcat(yazilacak,"\n");
	strcat(yazilacak,message);
	ssize_t yazilan = write(dosya_fd, yazilacak, strlen(message));
	if (yazilan == -1) {
		perror("write");
		exit(EXIT_FAILURE);
	}
	close(dosya_fd);
}

int create_q(struct queue *clients) {
	clients->clients = NULL;
	clients->first_client = 0;
	clients->last_client = 0;
	clients->capacity = 0;
	clients->size = 0;
	return 0;
}

int sirala(struct queue *que, struct client_t *item)  {
	if (que->size == que->capacity ) resize(que);

	que->clients[que->last_client] = malloc(sizeof(struct client_t));
	*(que->clients[que->last_client]) = *item;
	que->last_client = (que->last_client == que->capacity - 1) ? 0 : que->last_client + 1;
	que->size += 1;
	return 0;
}

int resize(struct queue *que) {
	int new_capa;
	struct client_t **new_elements;

	new_capa = que->capacity == 0 ? 1 : 2 * que->capacity;  
	new_elements = malloc(new_capa * sizeof(struct queue *));
	int a;
	for (a = 0; que->first_client != que->last_client; a++) { 
		new_elements[a] = que->clients[que->first_client];
		que->first_client = (que->first_client == que->capacity - 1) ? 0 : que->first_client + 1;
	}
	que->clients = new_elements;
	que->capacity = new_capa;
	que->first_client = 0;
	que->last_client = a;  
	return 0;
}

void serve(){

	int argc_command;
	char *argv_command[5];
	char buffer[256];

	int fd2= open(FIFO3, O_RDONLY);
	int num_read = read(fd2, buffer, 5*sizeof(char));		
	close(fd2);
	argc_command = kelimeSay(buffer);
	kelimeAyir(buffer,argv_command);
	
	if(strcmp(argv_command[0],"help") == 0){
		if(argc_command == 2){
		
		}
		else if(argc_command == 1){
			printf("asdadassa|hlp\n");
			char* message = "\nAvailable comments are :\nhelp, list, readF, writeT, upload, download, archServer, quit, killServer \n";
			int fd_help = open(FIFO2,O_WRONLY);
			int num_w = write(fd_help, message, strlen(message));	
			close(fd_help);
		
		}else{
			printf("Argc_command must be smaller than three\n");
			return;
		}	
	
	}
	else if(strcmp(argv_command[0],"list") == 0){}
	else if(strcmp(argv_command[0],"readF") == 0){
		
		char * args[] = {"sed", "-n", "", "", NULL};
		strtok(FIFO3, " ");
		args[3] = strtok(NULL, " ");
		char * lineNumberStr = strtok(NULL, "\n");
		int lineNumber = 0;
		if(lineNumberStr != NULL){
			lineNumberStr[strlen(lineNumberStr) - 1] = 'p';
			args[2] = lineNumberStr;
		}
		else{
			args[2] = "p";
		}
		execv("/bin/sed", args);

	
	}
	else if(strcmp(argv_command[0],"writeT") == 0){}
	else if(strcmp(argv_command[0],"upload") == 0){}
	else if(strcmp(argv_command[0],"download") == 0){}
	else if(strcmp(argv_command[0],"archServer") == 0){}
	else if(strcmp(argv_command[0],"killServer") == 0){}
	else if(strcmp(argv_command[0],"quit") == 0){}


}

int kelimeSay(char *string) {
	int uzunluk = strlen(string);
	int kelime_sayisi = 0;
	int i;

	if (string[0] != ' ')
		kelime_sayisi = 1;

	for (i = 0; i < uzunluk - 1; i++) {
		if (string[i] == ' ' && string[i + 1] != ' ') {
			kelime_sayisi++;
		}
	}
	printf("kelime %d \n",kelime_sayisi);
	return kelime_sayisi;
}
int kelimeAyir(char *string, char **kelimeler) {
	char *kelime = strtok(string, " ");
	int index = 0;
	while (kelime != NULL && index < 6) {
		kelimeler[index] = strdup(kelime);
		index++;
		kelime = strtok(NULL, " ");
	}
	return index; 
}


