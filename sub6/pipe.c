#include <stdio.h>		// printf, sprintf, perror
#include <stdlib.h> 	// exit
#include <unistd.h>		// pipe, write, read, fork
#include <string.h> 	// strlen, memset
#include <sys/wait.h>	// wait

#define BUFF_SIZE		100

int main(void) {

	int		pipe_parent[2];
	int		pipe_child[2];
	char	buff[BUFF_SIZE];
	pid_t	pid;
	int 	status;

	if(-1 == pipe(pipe_parent)) {
		perror("error parent pipe");
		exit(1);
	}
	if(-1 == pipe (pipe_child)) {
		perror("error child pipe");
		exit(1);
	}
	//child
	if( (pid = fork()) ==0) {
		sprintf( buff, "(child) test_pipe" );
		write( pipe_child[1], buff, strlen(buff) ); // buff value -> stdout
		memset( buff, 0x00, BUFF_SIZE );

		read(pipe_parent[0], buff, BUFF_SIZE );	// stdin -> buff
		printf( "child: %s\n",buff );
	}
	//parent
	else {
			sprintf( buff, "(parent) test_pipe");
			write(pipe_parent[1], buff, strlen(buff));
			wait(&status);
			memset(buff,0x00,BUFF_SIZE);

			read( pipe_child[0], buff, BUFF_SIZE );
			printf( "parent: %s\n", buff );
	}
	return 0;
}
