#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define READ_LENGTH 128

int escreve_novo_arquivo(char *nome);
void le_arquivo(int fd);
void flush(void);

int main()
{
    char nome[256];

    printf("\nArquivo: ");
    scanf("%s", nome);

    printf("\nArquivo a abrir: %s", nome);

    int fd, status = 0;
    fd = open(nome, O_RDONLY);
    if (fd == -1)
    {
        printf("\nO arquivo não existe.\n");
        fd = escreve_novo_arquivo(nome);
    }
    else
    {
        printf("\nO arquivo existe!\n");
        le_arquivo(fd);
        printf("\n\n");
    }

    if (fd > 0)
    {
        close(fd);
    }
    return fd;
}

int escreve_novo_arquivo(char *nome)
{
    printf("Digite o texto a inserir em sua criação: ");
    char *texto;

    flush();
    fgets(texto, 512, stdin);
    flush();

    int fd;
    fd = open(nome, O_RDWR | O_CREAT, S_IRGRP | S_IWGRP | S_IWUSR | S_IRUSR | S_IROTH | S_IWOTH);
    if (fd < 0)
    {
        perror("\nNão foi possível abrir o arquivo para escrita.\n");
        return -1;
    }

    int length = strlen(texto);
    printf("\nTamanho: %d\n", length);
    int status = write(fd, texto, length);

    if (status < 0)
    {
        perror("\nProblema na escrita do arquivo.\n");
        return -1;
    }

    return fd;
}

void le_arquivo(int fd)
{
    int tamanho = lseek(fd, 0, SEEK_END);
    printf("\nTamanho do arquivo: %d B\n", tamanho);
    lseek(fd, 0, SEEK_SET);

    printf("\nConteúdo:\n");
    int total_read = READ_LENGTH;
    char c[READ_LENGTH];
    while (READ_LENGTH == total_read)
    {
        total_read = read(fd, c, READ_LENGTH);

        if (READ_LENGTH > total_read)
        {
            c[total_read] = '\0';
            printf("%s", c);
            break;
        }
        else
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