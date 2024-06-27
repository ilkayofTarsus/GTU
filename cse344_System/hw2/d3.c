#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIRST_FIFO "/tmp/first_fifo"
#define SECOND_FIFO "/tmp/second_fifo"
int child_count = 0; 

void child_process(int id,int size) {
	int* array = (int *)malloc(size * sizeof(int));
	int fd = open(FIRST_FIFO, O_RDONLY);
	int sum=0;
	if (fd == -1) {
		perror("open");
		free(array);
		exit(EXIT_FAILURE);
	}
	sleep(10);
	if (read(fd, array, size * sizeof(int)) == -1) {
		perror("read");
		free(array);
		exit(EXIT_FAILURE);
	}
	for(int a = 0; a < size; a ++){
		sum += array[a];
	}
	close(fd);
	int fd2 = open(SECOND_FIFO, O_WRONLY);
	if (fd2 == -1) {
		perror("open");
		free(array);
		exit(EXIT_FAILURE);

	}
	sleep(1);
	if (write(fd2, &sum, sizeof(int)) == -1) {
		perror("write");
		free(array);
		exit(EXIT_FAILURE);
	}
	close(fd2);
	free(array);
}
void child_process2(int id,int size) {
	int* array = (int *)malloc(9 * sizeof(int));
	char* str = (char *)malloc(5 * sizeof(char));
	int mult=1;
	int fd= open(SECOND_FIFO, O_RDONLY);
	if (fd == -1) {
		perror("open");
		free(array);
		free(str);
		exit(EXIT_FAILURE);
	}
	sleep(4);
	if (read(fd, str, 5 * sizeof(char)) == -1) {
		perror("open");
		free(array);
		free(str);
		exit(EXIT_FAILURE);
	}
	int deger;
	if (read(fd, array, size * sizeof(int)) == -1) {
		perror("open");
		free(array);
		free(str);
		exit(EXIT_FAILURE);
	}
	close(fd);
	if(strcmp(str,"mult") == 0)  for(int a = 0; a < size; a ++) mult *= array[a];

	int fd2 = open(SECOND_FIFO, O_RDONLY);
	if (read(fd2, &deger,sizeof(int)) == -1) {
		perror("open");
		free(array);
		free(str);
		exit(EXIT_FAILURE);
	}
	printf("\nsummition == %d multiplication == %d summition + multiplication == %d\n\n",deger,mult,mult+deger);
	close(fd2);
	free(array);
	free(str);
}


void child_handler(int sig) {
	pid_t pid;
	int status;
	while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
		printf("Child process with PID %d has exited. status == %d\n", pid,status);
		--child_count;
	}
}
int main(int argc, char *argv[]) {

	srand(time(NULL));
	if (mkfifo(FIRST_FIFO, 0666) == -1 && errno != EEXIST) {
		perror("mkfifo");
		exit(EXIT_FAILURE);
	}
	if (mkfifo(SECOND_FIFO, 0666) == -1 && errno != EEXIST) {
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
	printf("Give size for array that will be sent to child processes\n");
	char* size_string = (char*)malloc(sizeof(char)*10);
	int bytes_read = read(1, size_string, sizeof(char)*10);
	 if (bytes_read == -1) {
		perror("read"); 	
		free(size_string);
		exit(EXIT_FAILURE);
    	}
    	size_string[9] = '\0';
    	int size = atoi(size_string);
	free(size_string);
	pid_t child_pid = fork();
	if (child_pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (child_pid == 0) {
		child_process2((int)getpid(),size);
		exit(EXIT_SUCCESS);
	}
	child_count++; 
	pid_t child_pid2 = fork();
	if (child_pid2 == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (child_pid2 == 0) {
		child_process((int)getpid(),size);
		exit(EXIT_SUCCESS);
		
	} 
		child_count++;
		int message[size];
		printf("--------random variables--------\n");
		for(int a = 0 ; a < size; a++) message[a] =  rand() % 11;
		for(int a = 0 ; a < size; a++) printf("message[%d] == %d\n",a,message[a]);
		printf("--------------------------------\n");
		char message2[] = "mult";
		char buffer[BUFSIZ];
		int fd,fd2;

		fd2 = open(SECOND_FIFO, O_WRONLY);
		if (fd2 == -1) {
			perror("open");
			exit(EXIT_FAILURE);

		}		
		if (write(fd2, message2, 5*sizeof(char)) == -1) {
			perror("write");
			exit(EXIT_FAILURE);

		}		
		if (write(fd2, message, size*sizeof(int)) == -1) {
			perror("write");
			exit(EXIT_FAILURE);

		}
		close(fd2);

		fd = open(FIRST_FIFO, O_WRONLY);
		if (fd == -1) {
			perror("open");
			exit(EXIT_FAILURE);
		}
		write(fd, message, size*sizeof(int));
		close(fd);		
	
	printf("Parent process started with PID %d size == %d\n", getpid(),size);
	printf("Waiting for child processes to exit...\n");
	while (child_count > 0) { 
		sleep(2);
		write(STDOUT_FILENO,"Proceed...\n",11);
	}
	printf("All child processes have exited. Parent process is exiting...\n");
	unlink(FIRST_FIFO);
	unlink(SECOND_FIFO);
	
	return 0;
}

