#include<unistd.h>
#include<stdio.h>
#include<wait.h>

int main(char *argv) {
	char *filename[] = {"/bin/touch"};
	char *argvs[] = {"touch", argv, NULL};
	char *envp[] = {NULL};
	pid_t pid;
	int status;
	pid_t pid_child;

	if((pid= fork()) == 0) {
		execve(*filename, argvs, envp);
	}else {
		pid_child = wait(&status);
		if( status == 0){
			printf("완료\n");
		}
	}
	return 0;
}

