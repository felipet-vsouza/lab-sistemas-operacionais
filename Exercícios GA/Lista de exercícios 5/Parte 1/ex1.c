
#include<stdio.h>

int main(int argc, char *argv[])
{
	if (valida_entrada(argc, argv) == 0)
		return 1;
	int n = le_repeticoes();
	repete(n, argv[1]);
	return 0;
}

int valida_entrada(int argc, char *argv[])
{
	int valido = 1;
	if (argc != 2)
	{
		valido = 0;
		printf("\nDeve ser informada apenas uma palavra como parâmetro!\n");
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
		printf("#%d\t '%s'\n", i, w);
	}
}
