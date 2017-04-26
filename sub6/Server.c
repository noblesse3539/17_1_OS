#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <time.h>

#define FIFO_FILE1 "./fifo1_temp"
#define FIFO_FILE2 "./fifo2_temp"
#define BUFF_SIZE 100

int main(void) {
	int counter = 0;
	int status;
	int pipe_child[2];
	int randomNumber;
	int fd;
	int fd2;
	char buff[BUFF_SIZE];
	int answer;
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
			answer = atoi(buff);
//			printf("랜덤숫자 출력 : %d\n", atoi(buff));
		} 	// git commit 1

		if ( mkfifo (FIFO_FILE1, 0666) == -1 ) {
			perror( "mkfifo() 실행에러 FIFO_FILE1");
			exit(1);
		}
		if ( mkfifo (FIFO_FILE2, 0666) == -1 ) {
			perror( "mkfifo() 실행에러 FIFO_FILE2");
			exit(1);
		}
		
		if ( -1 == ( fd = open(FIFO_FILE1, O_RDONLY) ) ) {

			perror ( " open() 실행에러 FIFO_FILE1");
			exit(1);
		}
		if ( -1 == ( fd2 = open(FIFO_FILE2, O_WRONLY) ) ) {

			perror ( " open() 실행에러 FIFO_FILE2");
			exit(1);
		}
		while (1) {
			sleep(1);
			memset(buff, 0x00, BUFF_SIZE);
			read(fd, buff, BUFF_SIZE);
			printf("answer : %s", buff);
			if ( answer  > atoi(buff) ) {
				sprintf(buff,"result : UP(%d/10)",++counter);
				printf("%s\n",buff);
				write(fd2, buff, strlen(buff));
			}else if ( answer < atoi(buff) ) {
				sprintf(buff,"result : DOWN(%d/10)",++counter);
				printf("%s\n",buff);
				write(fd2, buff, strlen(buff));
			}else {
				sprintf(buff,"result : Corect(%d/10)",++counter);
				printf("%s\n",buff);
				write(fd2, buff, strlen(buff));
				exit(0);
			}
			if ( counter >= 10) {
				printf ("Failure\n");
				sprintf(buff,"Failure");
				write(fd2, buff, strlen(buff));
				exit(0);
			}
		}
	close(fd);
	close(fd2);
	}

	return 0;
}
