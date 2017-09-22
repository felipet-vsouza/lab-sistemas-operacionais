#include<stdio.h>

int main(int argc, char *argv[])
{
	if (argc != 4) {
		printf("\nDevem ser especificadas 3 operações!\n");
		return -1;
	}

	int i;
	for (i = 3; i > 0; i--)
	{
		system(argv[i]);
		sleep(5);
	}
	return 0;
}
