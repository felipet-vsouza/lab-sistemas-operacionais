#include<stdio.h>

int main(void)
{
	int operacao = le_operacao();
	while (operacao != 5) {
		int n1 = le_numero();
		int n2 = le_numero();
		apresenta_resultado(n1, n2, operacao);
		operacao = le_operacao();
	}
	return 0;
}

int le_operacao()
{
	int n = 0;
	while (n < 1 || n > 5) {
		printf("\nQual operação você deseja realizar?\n");
		printf("1 - Soma\n");
		printf("2 - Subtração\n");
		printf("3 - Produto\n");
		printf("4 - Divisão\n");
		printf("5 - Sair\n");
		printf("\nEscolha: ");
		scanf("%d", &n);
		if (n < 1 || n > 5) printf("\nOpção inválida! Tente novamente.\n");
	}
	return n;
}

int le_numero ()
{
	int n;
	printf("\nEscolha o número: ");
	scanf("%d", &n);
	return n;
}

void apresenta_resultado (int n1, int n2, int operacao) {
	int resultado;
	switch(operacao) {
		case 1:
			resultado = n1 + n2;
			break;
		case 2:
			resultado = n1 - n2;
			break;
		case 3:
			resultado = n1 * n2;
			break;
		case 4:
		default:
			resultado = n1 / n2;
			break;
	}
	printf("\n\nResultado: %d", resultado);
}
