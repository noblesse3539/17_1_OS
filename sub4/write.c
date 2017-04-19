#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

int main( char *argv) {
	int fd;
	char *buf ="아메아메";
	fd = open(argv, O_RDWR);
	read(fd, buf, 10);
	write(fd, buf, 10);
	return 0;
}
