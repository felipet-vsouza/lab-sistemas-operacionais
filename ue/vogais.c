#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("\nNão foi informada nenhuma palavra. :(");
		return -1;
	}
	int length = strlen(argv[1]);
	char *word = argv[1];
	int it = 0;
	char c =  word[it];
	int count = 0;
	while (c != '\0')
	{
		if (c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' || c == 'u' || c == 'U') count++;
		c = word[++it];
	}
	int n;
	printf("\nDigite um número: ");
	scanf("%d", &n);
	printf("\n\nTotal de vogais: %d\tNúmero digitado: %d", count, n);
	printf("\n\nResultado: %d\n\n", n * count);
	return 0;
}
