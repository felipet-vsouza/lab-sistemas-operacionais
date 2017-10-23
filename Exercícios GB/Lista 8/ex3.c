#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define READ_LENGTH 32

void le_arquivo(int fd);
void flush(void);

int main()
{
    char nome[256];

    printf("\nArquivo: ");
    fgets(nome, sizeof(nome), stdin);
    flush();

    int fd;
    fd = open(nome, O_RDONLY);
    if (fd == -1)
    {
        char *texto;
        printf("\nO arquivo não existe.\nDigite o texto a inserir em sua criação: ");
        fgets(texto, sizeof(texto), stdin);
        flush();
    }
    else
    {
        printf("\nO arquivo existe!\n");
        le_arquivo(fd);
    }
    return 0;
}

void le_arquivo(int fd)
{
    int total_read = 1;
    char c[READ_LENGTH];
    while (total_read > 0)
    {
        total_read = read(fd, c, READ_LENGTH);
        if (total_read > 0)
        {
            printf("%s", c);
        }
    }
}

void flush(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}