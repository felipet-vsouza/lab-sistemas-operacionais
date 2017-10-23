#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

#define NUM_THREADS 4
#define ROUNDS 10000000;

struct WorkUnit
{
	int n1;
	int n2;
	char *operacao;
	float result;
};

void *Soma(void *param)
{
	struct WorkUnit *wu = param;

	int n1 = wu->n1;
	int n2 = wu->n2;
	wu->result = n1 + n2;
	wu->operacao = "soma";

	pthread_exit((void *)wu);
}

void *Subtracao(void *param)
{
	struct WorkUnit *wu = param;

	int n1 = wu->n1;
	int n2 = wu->n2;
	wu->result = n1 - n2;
	wu->operacao = "subtração";

	pthread_exit((void *)wu);
}

void *Multiplicacao(void *param)
{
	struct WorkUnit *wu = param;

	int n1 = wu->n1;
	int n2 = wu->n2;
	wu->result = n1 * n2;
	wu->operacao = "multiplicação";

	pthread_exit((void *)wu);
}

void *Divisao(void *param)
{
	struct WorkUnit *wu = param;

	int n1 = wu->n1;
	int n2 = wu->n2;
	wu->result = (float)n1 / (float)n2;
	wu->operacao = "divisão";

	pthread_exit((void *)wu);
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		perror("É necessário informar 2 argumentos!\n");
		return 1;
	}

	pthread_t thread[NUM_THREADS];
	struct WorkUnit wunits[NUM_THREADS];
	void *(*functions[NUM_THREADS])(void *) = {Soma, Subtracao, Multiplicacao, Divisao};
	struct WorkUnit *w;
	struct WorkUnit *status;
	pthread_attr_t attr;
	int rc, t;

	int n1 = atoi(argv[1]);
	int n2 = atoi(argv[2]);

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for (t = 0; t < NUM_THREADS; t++)
	{
		w = &wunits[t];
		w->n1 = n1;
		w->n2 = n2;

		rc = pthread_create(&thread[t], &attr, functions[t], w);
		if (rc)
		{
			errno = rc;
			perror("pthread_create()");
			exit(EXIT_FAILURE);
		}
	}

	pthread_attr_destroy(&attr);

	for (t = 0; t < NUM_THREADS; t++)
	{
		rc = pthread_join(thread[t], (void *)&status);
		if (rc)
		{
			errno = rc;
			perror("pthread_join()");
			exit(EXIT_FAILURE);
		}

		printf("Resultado da operação de %s: %f\n", status->operacao, status->result);
	}

	pthread_exit(NULL);
}