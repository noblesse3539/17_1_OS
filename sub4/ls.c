/*201100964 고병석 */

#include<unistd.h>
#include<stdio.h>

int main() {
	char *filename[] = {"/bin/ls"};
	char *argv[] = {"ls", "-al", NULL};
	char *envp[] = {NULL};

	execve(*filename, argv, envp);
	printf("error!!!\n");
}
