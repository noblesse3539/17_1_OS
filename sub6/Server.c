#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_FILE "./fifo1_temp_"
#define FIFO_FILE "./fifo2_temp_"
#define BUFF_SIZE 100

int main(void) {

	
