#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	if (valida_entrada(argc, argv) == 0)
		return 1;
	int n = le_repeticoes();
	pid_t filho;
	if ((filho = fork()) < 0)
	{
		perror("\nProblema na criação do processo filho.\n");
		return 1;
	}
	else if (filho == 0) repete(n, argv[1]);
	else
	{
		printf("\n\nPai terminou.\tPID: %d\tPPID: %d\n", getpid(), getppid());
	}
	return 0;
}

int valida_entrada(int argc, char *argv[])
{
	int valido = 1;
	if (argc != 2)
	{
		valido = 0;
		perror("\nDeve ser informada apenas uma palavra como parâmetro!\n");
	}
	return valido;
}

int le_repeticoes()
{
	int n;
	printf("\nRepetições: ");
	scanf("%d", &n);
	return n;
}

void repete(int n, char *w)
{
	int i;
	for (i = 1; i <= n; i++)
	{
		printf("#%d\t'%s'\tPID: %d\tPPID: %d\n", i, w, getpid(), getppid());
		sleep(1);
	}
}
