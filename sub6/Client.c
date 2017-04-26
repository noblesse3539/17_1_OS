#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_FILE1 "./fifo1_temp"
#define FIFO_FILE2 "./fifo2_temp"
#define BUFF_SIZE 100

int main(void) {

	int cnt = 0;
	int fd2;
	int fd ;
	char buff[BUFF_SIZE];

	if ( -1 == ( fd = open(FIFO_FILE1, O_WRONLY) ) ) {
		perror("open error!!!\n");
		exit(1);
	}
	if ( -1 == ( fd2 = open(FIFO_FILE2, O_RDONLY) ) ) {
		perror("open error!!!\n");
		exit(1);
	}

	while(1) {
		memset(buff, 0x00, BUFF_SIZE);
		printf("answer : ");
		fgets(buff, BUFF_SIZE, stdin);
		if( atoi(buff) <1 || atoi(buff) > 100 ) {
			printf("1~100 사이 숫자를 입력하세요\n");
			continue;
		}
		write(fd, buff, strlen(buff));
		sleep(1);
		memset(buff, 0x00, BUFF_SIZE);
		read(fd2, buff, BUFF_SIZE);
		printf("%s\n", buff);
		if (++cnt == 10) {
			printf("Failure\n");
			exit(0);
		}
		if (buff[9] == 'C') {
			exit(0);
		}
	}
	close(fd);
	close(fd2);

	return 0;
	}
