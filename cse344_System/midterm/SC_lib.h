#ifndef SC_LIB_H
#define SC_LIB_H
#define FIFO "/tmp/fifo"
#define FIFO2 "/tmp/fifo2"
#define FIFO3 "/tmp/fifo3"
#define CMD_SIZE 

#define HELP "help"
#define LIST "list"
#define READF "readF"
#define WRITET "writeT"
#define UPLOAD "upload"
#define DOWNLOAD "download"
#define ARCHSERVER "archServer"
#define KILLSERVER "killServer"
#define QUIT "quit"

//enum commands {HELP,LIST,READF,WRITET,UPLOAD,DOWNLOAD,ARCHSERVER,KILLSERVER,QUIT};

struct client_t{
	pid_t cl_pid;
	int try_connect;
}client_t;


#endif
