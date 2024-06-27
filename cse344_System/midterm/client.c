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
#include"client.h"
#include"SC_lib.h"

void sig_handler(int signum) {
	signal(SIGTSTP, sig_handler); 
	printf("Cannot execute Ctrl+Z\n"); 
}

int main(int args, char* argv[]){
	
	signal(SIGTSTP, sig_handler);
	if (mkfifo(FIFO, 0666) == -1 && errno != EEXIST) {
		perror("mkfifo");	
		exit(EXIT_FAILURE);
	}
	if (mkfifo(FIFO2, 0666) == -1 && errno != EEXIST) {
		perror("mkfifo");	
		exit(EXIT_FAILURE);
	}

	char* message = "ilkay";
	int fd = open(FIFO, O_WRONLY);
	if (fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);

	}
	
	sigset_t sigmask;
	sigemptyset(&sigmask);
	sigaddset(&sigmask, SIGINT);
	
	struct client_t cl_itself;
	cl_itself.cl_pid = getpid();
	cl_itself.try_connect = 0;
	int wr_read;
//	printf("c side Client pid == %d\n",getpid());			
	
	wr_read = write(fd, &cl_itself, sizeof(client_t));
	close(fd);
	int size_in;
	char buffer[256];

	//int rd_fd = open(FIFO2, O_RDONLY);
	//int num_read = read(rd_fd,buffer,20*sizeof(char));
	//printf("%s\n",buffer);
	//close(rd_fd);
	
	
	int wr_fd = open(FIFO3,O_WRONLY);
	char command_client[256],respond_server[256];
	int respond = open(FIFO2,O_RDONLY);

	while(1){
	
		printf(">> Enter comment :");
		fgets(command_client, sizeof(command_client), stdin);
		int num_read = write(wr_fd,command_client, strlen(command_client)*sizeof(char));
		
		num_read = read(respond,respond_server,sizeof(respond_server));

	}
	close(respond);
	close(wr_fd);
	
/*		
	printf(buffer);
	/*for(int a = 0; a < 6; a++){
		int pid = fork();
		struct client_t cl_itself;
		cl_itself.cl_pid = getpid();
		cl_itself.try_connect = 0;		
		if(pid != 1 && pid != -1){
				
			if (write(fd, &cl_itself, sizeof(client_t)) == -1) {
				perror("write");
				exit(EXIT_FAILURE);
			}
		
		}
	}
	*/



return 0;
}
