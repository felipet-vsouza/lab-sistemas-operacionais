#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

#define NUM_THREADS 3
#define NUM_MSG 5
#define SLEEP_TIME 1

typedef struct
{
	char *who;
	pthread_t caller;
} PrintHelloArg;

void *PrintHello(void *param)
{
	int i;
	PrintHelloArg *arg;
	arg = (PrintHelloArg *)param;
	for (i = 0; i < NUM_MSG; i++)
	{
		sleep(SLEEP_TIME);
		printf("\nHello World! It's me, %s!\nThread atual:%lu\tThread chamadora: %lu\n",
			   arg->who, pthread_self(), arg->caller);
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t tids[NUM_THREADS];
	int n;
	int te;
	char *names[NUM_THREADS] = {"moe", "larry", "curly"};
	for (n = 0; n < NUM_THREADS; n++)
	{
		PrintHelloArg *arg = malloc(sizeof(PrintHelloArg));
		arg->who = names[n];
		arg->caller = pthread_self();
		te = pthread_create(&tids[n], NULL, &PrintHello, (void *)arg);
		if (te)
		{
			errno = te;
			perror("Falha na criação da thread");
			exit(EXIT_FAILURE);
		}
	}
	pthread_exit(NULL);
}
