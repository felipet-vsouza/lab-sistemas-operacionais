#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define MAXLINE 4096

int main(){
	int n, fd[2];
	char line[MAXLINE];

	if (pipe(fd) != 0){
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	switch (fork()){
	case -1:
		perror("fork");
		exit(EXIT_FAILURE);
		break;
	case 0:
		close(fd[0]);
		printf("Filho escrevendo...");
		write(fd[1],"Hello World\n",12);
		break;
	default:
		close(fd[1]);
		printf("Pai lendo...");
		n=read(fd[0],line,MAXLINE);
		write(STDOUT_FILENO, line, n);
		break;
	}
	exit(EXIT_SUCCESS);
}
