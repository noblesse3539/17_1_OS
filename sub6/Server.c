#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <time.h>

#define FIFO_FILE "./fifo1_temp_"
#define FIFO_FILE "./fifo2_temp_"
#define BUFF_SIZE 100

int main(void) {
	int status;
	int pipe_child[2];
	int randomNumber;
	char buff[BUFF_SIZE];
	pid_t pid;
	pid_t pid_child;

	if ( -1 == pipe(pipe_child)) {
			perror (" 파이프 생성 실패" );
			exit(1);
	}

	if ( (pid=fork()) == 0) {
		srand(time(NULL));
		while((randomNumber = rand()%101) == 0) {
			continue;
		}
		sprintf(buff, "%d", randomNumber);
		write ( pipe_child[1], buff, strlen(buff));
		
		exit(0);
	}else {
		pid_child = wait( &status);
		if ((status & 0xff) != 0) {
			perror (" 자식프로세스가 비정상 종료됨 " );
			exit(1);
		}else {
			memset ( buff, 0x00, BUFF_SIZE);
			read( pipe_child[0], buff, BUFF_SIZE);
			printf("랜덤숫자 출력 : %s\n", buff);
		}
	}
}
