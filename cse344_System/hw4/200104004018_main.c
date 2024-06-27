#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <signal.h>

#define MAX_PATH_LENGTH 1024
#define BUFFER_SIZE 1024

char** tasks;
int task_count = 0;
int task_index = 0;
int task_capacity = 0;
int worker_count;
int fifo_file_count = 0;
int directory_count = 0;
off_t total_bytes_copied = 0;
pthread_mutex_t mutex;
pthread_cond_t cond_task_added;
int ctrl_c = 0;

void handle_sigint(int sig) {
	ctrl_c= 1;
}


void add_task(const char* source, const char* destination) {

	pthread_mutex_lock(&mutex);

	if (task_count >= task_capacity) {

		task_capacity = task_capacity == 0 ? 1 : task_capacity * 2;
		char** new_tasks = malloc(task_capacity * sizeof(char*));
		if (new_tasks == NULL) {
			perror("malloc");
			pthread_mutex_unlock(&mutex);
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < task_count; ++i) {
		new_tasks[i] = tasks[i];
		}

		free(tasks);
		tasks = new_tasks;
	}

	tasks[task_count] = malloc((strlen(source) + strlen(destination) + 2) * sizeof(char));
	if (tasks[task_count] == NULL) {
		perror("malloc");
		pthread_mutex_unlock(&mutex);
		exit(EXIT_FAILURE);
	}

	snprintf(tasks[task_count], (strlen(source) + strlen(destination) + 2), "%s|%s", source, destination);
	task_count++;
	pthread_cond_signal(&cond_task_added);
	pthread_mutex_unlock(&mutex);

}

char* get_task() {

	while (task_index >= task_count) {
		pthread_cond_wait(&cond_task_added, &mutex);
	}
	char* task = tasks[task_index];
	task_index++;
	return task;
}

void* copy_file(void* arg) {
	while (1) {
		if(ctrl_c) return NULL;
		
		pthread_mutex_lock(&mutex);
		
		if (task_index >= task_count) {
			pthread_mutex_unlock(&mutex);
			break;
		}
		char* task = get_task();
		pthread_mutex_unlock(&mutex);

		if (task == NULL) continue; 
		char* task_copy = strdup(task);
		if (task_copy == NULL) {
			perror("strdup");
			continue;
		}

		char* source = strtok(task_copy, "|");
		char* destination = strtok(NULL, "|");
		if (source == NULL || destination == NULL) {
			fprintf(stderr, "Invalid task format: %s\n", task);
			free(task_copy);
			continue;
		}

		struct stat st;
		if (stat(source, &st) == 0 && S_ISDIR(st.st_mode)) {
			mkdir(destination, 0755);
		} else {
		int src_fd = open(source, O_RDONLY);
		if (src_fd < 0) {
			perror("open source file");
			free(task_copy);
			continue;
		}
		int dest_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (dest_fd < 0) {
			perror("open destination file");
			close(src_fd);
			free(task_copy);
			continue;
		}
		char* buffer = malloc(BUFFER_SIZE);
		if (buffer == NULL) {
			perror("malloc buffer");
			close(src_fd);
			close(dest_fd);
			free(task_copy);
			continue;
		}

		ssize_t bytes_read, bytes_written;
		off_t file_size = 0;
		while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
			bytes_written = write(dest_fd, buffer, bytes_read);
			if (bytes_written != bytes_read) {
				perror("write");
				break;
			}
			file_size += bytes_written;
		}

		if (bytes_read < 0) perror("read");

		free(buffer);
		close(src_fd);
		close(dest_fd);

		pthread_mutex_lock(&mutex);
		total_bytes_copied += file_size;
		pthread_mutex_unlock(&mutex);

		}

		free(task_copy);
	}
	return NULL;
}

void list_files_recursive(const char* directory, const char* dest_dir) {
	DIR* dir = opendir(directory);
	if (dir == NULL) {
		perror("opendir");
		return;
	}
	if(ctrl_c) return;

	struct dirent* entry;

	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
			continue;
	}

	char source_path[MAX_PATH_LENGTH];
	char destination_path[MAX_PATH_LENGTH];

	snprintf(source_path, MAX_PATH_LENGTH, "%s/%s", directory, entry->d_name);
	snprintf(destination_path, MAX_PATH_LENGTH, "%s/%s", dest_dir, entry->d_name);

	if (entry->d_type == DT_DIR) {
		mkdir(destination_path, 0755);
		directory_count++;
		list_files_recursive(source_path, destination_path);
	} else if (entry->d_type == DT_REG) {
		add_task(source_path, destination_path);
	}else if (entry->d_type == DT_FIFO) {
		pthread_mutex_lock(&mutex);
		fifo_file_count++;
		pthread_mutex_unlock(&mutex);
		}
	}

	closedir(dir);
}

void* manager_thread(void* arg) {
	char** args = (char**)arg;
	char* source_directory = args[0];
	char* destination_directory = args[1];

	list_files_recursive(source_directory, destination_directory);
	pthread_mutex_lock(&mutex);
	pthread_cond_broadcast(&cond_task_added);
	pthread_mutex_unlock(&mutex);

	return NULL;
}

int main(int argc, char* argv[]) {
	clock_t start_time = clock(); 
	struct sigaction sa;
	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1) {
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

	if (argc != 5) {
		fprintf(stderr, "Usage: %s buffer worker_number source destination\n", argv[0]);
		return EXIT_FAILURE;
	}

	size_t buffer_size = atoi(argv[1]);
	worker_count = atoi(argv[2]);
	char* source_directory = argv[3];
	char* destination_directory = argv[4];

	if (mkdir(destination_directory, 0755) < 0 && errno != EEXIST) {
		perror("mkdir");
		return EXIT_FAILURE;
	}

	task_capacity = 1; 
	tasks = malloc(task_capacity * sizeof(char*));
	if (tasks == NULL) {
		perror("malloc");
		return EXIT_FAILURE;
	}

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond_task_added, NULL);

	pthread_t manager;
	pthread_t workers[worker_count];

	char* manager_args[] = {source_directory, destination_directory};
	pthread_create(&manager, NULL, manager_thread, manager_args);

	pthread_join(manager, NULL); 



	for (int i = 0; i < worker_count; ++i) {
		pthread_create(&workers[i], NULL, copy_file, destination_directory);
	}

	for (int i = 0; i < worker_count; ++i) {
		pthread_join(workers[i], NULL);
	}

	for (int i = 0; i < task_count; ++i) {
		free(tasks[i]);
	}
	free(tasks);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond_task_added);

	clock_t end_time = clock(); 
	double elapsed_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

	long minutes = (long)(elapsed_time / 60);
	long seconds = (long)(elapsed_time) % 60;
	long milliseconds = (long)((elapsed_time - (long)elapsed_time) * 1000);
	printf("\n---------------STATISTICS--------------------\n");
	printf("Consumers: %d - Buffer Size: %lu\n", worker_count, buffer_size);
	printf("Number of Regular Files: %d\n", task_count);
	printf("Number of FIFO Files: %d\n", fifo_file_count);
	printf("Number of Directories: %d\n", directory_count);
	printf("TOTAL BYTES COPIED: %ld\n", total_bytes_copied);
	printf("TOTAL TIME: %02ld:%02ld.%03ld (min:sec.milli)\n", minutes, seconds, milliseconds);

	return EXIT_SUCCESS;
}
