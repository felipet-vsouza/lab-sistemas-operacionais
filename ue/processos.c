#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char *url;
	printf("\nDigite a URL: ");
	scanf("%s", url);
	pid_t filho;
	if ((filho = fork()) < 0)
	{
		perror("\nProblema na criação do processo filho!\n");
		return 1;
	}
	else if (filho == 0) abre(url);
	else
	{
		int status;
		wait(&status);
		if (status != 0) perror("\nProblema na execução do processo filho!\n");
		printf("\nExecução finalizada.\n");
	}
}

void abre(char *url)
{
	printf("\nAbrindo URL %s\n", url);

	char argString[300];
	sprintf(argString, "%s", "firefox --new-window");
	strcat(argString, " ");
	strcat(argString, url);
	system(argString);

	printf("\nPID do pai: %d", getppid());
	printf("\nPID do filho: %d", getpid());
	exit(0);
}
