#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define MAXLINE 8192

int main(int argc, char *argv[]){

	int fd[2];

	if (argc < 2) {
		perror("É necessário informar o programa a ser executado.");
		exit(EXIT_FAILURE);
	} else if (argc > 2) {
		perror("É possível informar apenas um programa por execução.");
		exit(EXIT_FAILURE);
	}

	char *programa = argv[1];

	if (pipe(fd) != 0) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	switch (fork()) {
	case -1:
		perror("fork");
		exit(EXIT_FAILURE);
		break;
	case 0:
		close(fd[1]);
		char buf[MAXLINE];
		int n=read(fd[0],buf,MAXLINE);
		if (n < 0) {
			perror("read");
			exit(EXIT_FAILURE);
		}
		printf("%s", buf);
		break;
	default:
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execlp(programa, programa, NULL);
		perror("exec programa");
		break;
	}
	exit(EXIT_SUCCESS);
}
