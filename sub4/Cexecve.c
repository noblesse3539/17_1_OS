#include<stdio.h>
#include<unistd.h>

int main(){
 	char *filename[] ={"/bin/ls"};
//	char *argv[] = {"-al", NULL};
	char *argv[] = {"ls", "-al", NULL};
	char *envp[] = {NULL};
	execve(*filename, argv, envp);
	printf("error!!!\n");
}
