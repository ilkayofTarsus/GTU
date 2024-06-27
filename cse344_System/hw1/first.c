#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

//#define MAX_NAME_LENGTH 50
//#define MAX_GRADE_LENGTH 3

void addStudentGrade(const char *fileName,  char *name, const char *grade);
int searchStudent(const char *fileName,const char *name);
int checkName(const char* name_grade, const char* name);
void sortStudent(const char* fileName, int mode);
int satirSayisi(const char* fileName);
void sirala_isim(char dongu[][33], int satir);
void sirala_not(char not[][3] ,char dongu[][33],int satir);
char** parcala(char** args);
void kayit(char*msg);
void show_log();

int main(int argc, char *argv[]) {

	char **args ;
	int arg_no = 0;
	int exit_t = 0;
	do{	
	fflush(stdin);
	
	printf("\n\n----	q to exit	----\n");
	args = parcala(args);

	if (strcmp(args[0], "addStudentGrade") == 0) {
		kayit("command is given --> addStudentGrade\n");
		char *name = args[1];
		char *grade =args[2];
		char *fileName = args[3];
		addStudentGrade(fileName, name, grade);
	}
	else if (strcmp(args[0], "q") == 0) {
		kayit("command is given --> exit\n");
		exit_t = 1;
	} 
	else if (strcmp(args[0], "showLog") == 0) {
		kayit("command is given --> showLog\n");
		show_log();		
	} 
	else if (strcmp(args[0], "gtuStudentGrades") == 0 && strlen(args[1]) != 0) {
		kayit("command is given --> gtuStudentGrades\n");
		mode_t mod = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
		char *fileName = args[1];
		int dosya_tutucu = creat(fileName, mod);
		if (dosya_tutucu == -1) {
			perror("Dosya oluşturma hatası");
			kayit("Error opening file\n");
			exit(EXIT_FAILURE);
		}
		printf("\n %s is created\n",args[1]);
		kayit("File is created\n");
	} 
	else if (strcmp(args[0], "searchStudent") == 0) {
		kayit("command is given --> searchStudent\n");
		char *name = args[1];
		char *fileName = args[2];
		searchStudent(fileName,name);
	}
	else if (strcmp(args[0], "sortAll") == 0) {
		kayit("command is given --> sortAll\n");
		printf("\n\n\nEnter sort mode as integer:\n");
		printf("(1)Descending by name:\n");
		printf("(2)Ascending by name:\n");
		printf("(3)Descending by grade:\n");
		printf("(4)Ascending by grade:\n");
		char mode_c[3];
		int mode = 1;

		fgets(mode_c, sizeof(mode_c), stdin);
		mode_c[strcspn(mode_c, "\n")] = 0;
		mode = atoi(mode_c);

		fflush(stdin);		
		char *fileName = args[1];
		sortStudent(fileName,mode);
		
	}
	else if (strcmp(args[0], "showAll") == 0) {
		kayit("command is given --> showAll\n");
		int fd = open(args[1],O_RDWR);
		char buffer[999];
		size_t bytes_read;
		char *line_start = buffer;
		while ((bytes_read = read(fd, line_start, 1)) > 0) {
			if (*line_start == '\n') {
				*line_start = '\0';
				line_start = buffer;
				write(STDIN_FILENO,buffer,strlen(buffer));
				write(STDIN_FILENO,"\n",strlen("\n"));
			}
			else {
				line_start++;
			}

		}
		close(fd);
	}
	else if (strcmp(args[0], "listGrades") == 0) {
		kayit("command is given --> listGrades\n");
		int fd = open(args[1],O_RDWR);
		int dongu = 0;
		char buffer[16];
		size_t bytes_read;
		char *line_start = buffer;
		while ((bytes_read = read(fd, line_start, 1)) > 0) {
			if (*line_start == '\n') {
				if(dongu == 5) break;
				*line_start = '\0';
				line_start = buffer;
				write(STDIN_FILENO,buffer,strlen(buffer));
				write(STDIN_FILENO,"\n",strlen("\n"));
				dongu++;
			}
			else {
				line_start++;
			}

		}
		close(fd);
	}
	else if (strcmp(args[0], "listSome") == 0) {
		kayit("command is given --> listSome\n");
		int fd = open(args[3],O_RDWR);
		int dongu = 0,entries=0,page=0;
		char buffer[16];
		size_t bytes_read;
		char *line_start = buffer;
		
		entries = atoi(args[1]);
		page = atoi(args[2]);
		char *fileName = args[3];
		
		if(entries >= satirSayisi(fileName) || page*5 >= satirSayisi(fileName)){
			perror("Argument is too big");
			kayit("Error opening file\n");
			exit(EXIT_FAILURE);
		}
		while ((bytes_read = read(fd, line_start, 1)) > 0) {
			if (*line_start == '\n') {
				*line_start = '\0';
				line_start = buffer;
				if(dongu >= entries && dongu < 5*page){					
					write(STDIN_FILENO,buffer,strlen(buffer));
					write(STDIN_FILENO,"\n",strlen("\n"));
				}
				dongu++;
			}
			else {
				line_start++;
			}

		}
		close(fd);	
	}
	else if (strcmp(args[0], "gtuStudentGrades") == 0 && strlen(args[1]) == 0) {
		kayit("command is given --> gtuStudentGrades\n");
		int fd1 = open("menu.txt",O_RDWR);
		char buffer[16];
		size_t bytes_read;
		char *line_start = buffer;
		
		while ((bytes_read = read(fd1, line_start, 1)) > 0) {
			if (*line_start == '\n') {
				*line_start = '\0';
				line_start = buffer;
				write(STDIN_FILENO,buffer,strlen(buffer));
				write(STDIN_FILENO,"\n",strlen("\n"));
			
			}
			else {
				line_start++;
			}
		}
				close(fd1);
		}
		else {
			printf("Invalid command. args == %s\n",args[0]);
			kayit("Invalid command\n");
		}

		for(int a = 0; a < 5; a++) {
			args[a] = "\0";
	    	}

		if(exit_t){
			printf("exit\n");
			/*for(int a = 0; a < 5; a++) {
					free(args[a]);
			}
			free(args);	*/
		}
	}while(!exit_t);
	

	
	return 0;
}

int indexAddStudent = -1;

void addStudentGrade(const char *fileName,  char *name, const char *grade) {
	pid_t pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork failed\n");
		kayit("Fork Failed\n");
		exit(EXIT_FAILURE);
	} 
	else if (pid == 0) {		
		indexAddStudent = searchStudent(fileName,name);
		exit(EXIT_SUCCESS);
		
	} 
	else {  
		wait(NULL);

		int fd = open(fileName, O_WRONLY);
		if (fd == -1) {
		    perror("Error opening file\n");
		    kayit("Error opening file\n");
		    exit(EXIT_FAILURE);
		}

		int kontrol_lseek =lseek(fd, 0, SEEK_END);
		if (kontrol_lseek == -1) {
		    perror("Error lseek\n");
		    kayit("Error lseek\n");
		    exit(EXIT_FAILURE);
		}
		

		strcat(name," ");
		strcat(name,grade);
		strcat(name,"\n");

				
		if(indexAddStudent == -1 ){
			ssize_t kontrol_yazma = write(fd, name, strlen(name));
			if(kontrol_yazma == -1){
				perror("Error writing to file");
				kayit("Error writing file");
				exit(EXIT_FAILURE);
			}
			printf("\n\nStudent grade added successfully.\n");
			kayit("Student grade added successfully\n");
			
		} 
		else{
			
		}
		close(fd);
	}
}

int searchStudent(const char *fileName,const char *name){
	int index = -1,re_index = 0;
	pid_t pid = fork();
	unsigned char buffer[16];
	if (pid < 0) {
		fprintf(stderr, "Fork failed\n");
		kayit("Fork Failed\n");
		exit(EXIT_FAILURE);
	} 
	else if (pid == 0) {
		exit(EXIT_SUCCESS);
	} 
	else {  
		wait(NULL);
		int fd = open(fileName,O_RDONLY);
		if (fd == -1) {
		    perror("Error opening file\n");
		    kayit("Error opening file\n");
		    exit(EXIT_FAILURE);
		}
		size_t bytes_read;
		char *line_start = buffer;
		while ((bytes_read = read(fd, line_start, 1)) > 0) {
			if (*line_start == '\n') {
				*line_start = '\0';
				index = checkName(buffer,name);
				if(index != -1) return re_index;
				line_start = buffer;
				re_index++;
			} 
			else {
				line_start++;
			}
		}
		close(fd);
	}
	return -1;

}

int checkName(const char* name_grade, const char* name){
	
	if(getpid() != 0){
		int index = -1;
		char buffer[strlen(name_grade)];
		strcpy(buffer,"");

		for(int a = 0; a < strlen(name_grade); a++){
			char c = name_grade[a];
			char c_str[2] = {c, '\0'};
			strcat(buffer,c_str);
			if(strcmp(buffer,name) == 0){
				printf("\n\nStudent Found = %s\n",name_grade);
				index = a;
			}
		}
		return index;
	}
}
void sortStudent(const char* fileName, int mode){
	pid_t pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork failed\n");
		kayit("Fork Failed\n");
		exit(EXIT_FAILURE);
	} 
	else if (pid == 0) {
		unsigned char buffer[33];
		int dongu = 0;
		int satir = satirSayisi(fileName);
		char grades[satir][33];
		size_t bytes_read;
		char *line_start = buffer;
		
		int fd = open(fileName,O_RDONLY);		
		
		if (fd == -1) {
		    perror("Error opening file\n");
		    kayit("Error opening file\n");
		    exit(EXIT_FAILURE);
		}
		
		while ((bytes_read = read(fd, line_start, 1)) > 0) {
			if (*line_start == '\n') {
				*line_start = '\0';
				line_start = buffer;
				strcpy(grades[dongu],buffer);
				dongu++;					
			}
			else {
				line_start++;
			}

		}
	
		if(mode == 1 || mode == 2) {
			sirala_isim(grades,satir);

			if(mode == 1) 
				for(int a = satir-1 ; a >= 0; a--)
					printf("%d %s \n",satir-a,grades[a]);
		
			if(mode == 2) 
				for(int a = 0 ; a <satir; a++)
					printf("%d %s \n",a+1,grades[a]);
		
		}
		else{
			char just_grades[satir][3];
			for(int a = 0 ; a < satir; a++){			
				strncpy(just_grades[a], (grades[a] + strlen(grades[a]) -2), 2);
				just_grades[a][2] = '\0';
			}	
			
			sirala_not(just_grades,grades,satir);			
			if(mode == 4) 
				for(int a = satir-1 ; a >= 0; a--)
					printf("%d %s \n",satir-a,grades[a]);
		
			if(mode == 3) 
				for(int a = 0 ; a <satir; a++)
					printf("%d %s \n",a+1,grades[a]);					
		}
	
		close(fd);
		exit(EXIT_SUCCESS);
	} 
	else {  
		wait(NULL);
	}
}

int satirSayisi(const char* fileName){
	int fd = open(fileName, O_RDONLY);
	if (fd == -1) {
		perror("Dosya açma hatası");
		kayit("Error opening file\n");
		return 1;
	}

	int satir_sayisi = 0;
	char karakter;
	ssize_t bytes_read;
	while ((bytes_read = read(fd, &karakter, 1)) > 0) {
		if (karakter == '\n') {
			satir_sayisi++;
		}
	}
	close(fd);
	return satir_sayisi;
}

void sirala_isim(char dongu[][33],int satir){
	for(int a = 0; a < satir; a++){
		for(int b = a; b < satir; b++){
			if(strcmp(dongu[a],dongu[b]) > 0){
				char temp[33];
				strcpy(temp, dongu[a]);
				strcpy(dongu[a], dongu[b]);
				strcpy(dongu[b], temp);
			}
		}
	}

}
void sirala_not(char not[][3] ,char dongu[][33],int satir){
	for(int a = 0; a < satir; a++){
		for(int b = a; b < satir; b++){
			if(strcmp(not[a],not[b]) > 0){
				char temp[33];
				char temp_not[3];
				strcpy(temp, dongu[a]);
				strcpy(dongu[a], dongu[b]);
				strcpy(dongu[b], temp);
				strcpy(temp_not, not[a]);
				strcpy(not[a], not[b]);
				strcpy(not[b], temp_not);
			}
		}
	}

}

char** parcala(char** args){
	int arg_no = 0;
	char *komut;
	char *command_buffer ;
	char c;
	komut = (char *)malloc(sizeof(char) * 333);
	command_buffer = (char *)malloc(sizeof(char) * 333);
	args = (char **)malloc(sizeof(char*) * 5);
	for(int a = 0; a < 5; a++){
		args[a] = (char *)malloc(sizeof(char) * 33);
		strcpy(args[a], "");
	}
	fflush(stdin);
	fgets(komut, 333, stdin);
	
	for(int a = 0; a < strlen(komut);a++){
		c = komut[a];		
		char c_str[2] = {c,'\0'};
		if(c == '\"' || c == '\n'){
			if(strlen(command_buffer) != 0) strcpy(args[arg_no++], command_buffer);
			command_buffer[0] = '\0';
		}        
		else {
			
			strcat(command_buffer, c_str);
		}
	}
	command_buffer[0] = '\0';
	komut = "\0";
	command_buffer = "\0";
	return args;
}

void kayit(char*msg){
	char fileName[] = {"log.log"};
	int fd;	
	fd = open(fileName, O_RDWR);
	if(fd == -1){
		mode_t mod = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
		fd = creat(fileName, mod);	
	}
	
	if (fd == -1) {
	    perror("Error opening file\n");
	    exit(EXIT_FAILURE);
	}

	int kontrol_lseek =lseek(fd, 0, SEEK_END);	
	if (kontrol_lseek == -1) {
	    perror("Error lseek\n");
	    exit(EXIT_FAILURE);
	}
	write(fd, msg, strlen(msg));
	close(fd);
}

void show_log(){
	pid_t pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork failed\n");
		kayit("Fork Failed\n");
		exit(EXIT_FAILURE);
	} 
	else if(pid == 0){
		char* fileName = {"log.log"};
		int fd = open(fileName, O_RDWR);
		if (fd == -1) {
		    perror("Error opening file\n");
		    exit(EXIT_FAILURE);
		}

		char buffer[666];
			size_t bytes_read;
			char *line_start = buffer;
			while ((bytes_read = read(fd, line_start, 1)) > 0) {
				if (*line_start == '\n') {
					*line_start = '\0';
					line_start = buffer;
					write(STDIN_FILENO,buffer,strlen(buffer));
					write(STDIN_FILENO,"\n",strlen("\n"));
				}
				else {
					line_start++;
			}
		}
		fflush(stdin);
		exit(EXIT_SUCCESS);
	}
	else{
		wait(NULL);		
	}

}

