#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <mqueue.h>
#include "../include/velha-lib.h"

#define clear_screen() printf("\033[H\033[J")

void init_game(mqd_t queue, char *nomeJogador);
mqd_t init_queue();
void processa_resposta(ssize_t nbytes, const char *buffer, mqd_t queue);

int identificador;

/**
 * Jogador 0: O
 * Jogador 1: X
*/
int main()
{
    printf("Iniciando conexão Client\n");
    mqd_t queue = init_queue();
    char nome[20];
    printf("Digite seu nome: ");
    scanf("%s", nome);
    printf("Bem vindo: %s", nome);
    init_game(queue, nome);
	return 0;
}

void init_game(mqd_t queue, char *nomeJogador)
{
    mensagem_t connectionMessage;
    connectionMessage.tipo = CONEXAO;
    connectionMessage.nome = nomeJogador;
    if (mq_send(queue, (const char*) &connectionMessage, sizeof(mensagem_t), 20) != 0)
    {
		perror("Erro");
    }
    ssize_t nbytes;
    ssize_t tam_buffer;
    char *buffer;
    struct mq_attr attr;
    if (mq_getattr(queue, &attr) != -1)
    {
        tam_buffer = attr.mq_msgsize;
    }
    else
    {
        printf("getattr");
        exit(2);
    }
    buffer = calloc(tam_buffer, 1);
    nbytes = mq_receive(queue, buffer, tam_buffer);
    processa_resposta(nbytes, buffer, queue);
    mq_close(queue);
}

mqd_t init_queue()
{
    mqd_t queue = mq_open(QUEUE_NAME, O_RDWR | O_CREAT, 0660, NULL);
	if (queue == (mqd_t)-1)
	{
		perror("mq_open");
		exit(2);
	}
	return queue;
}

void processa_resposta(ssize_t nbytes, const char *buffer, mqd_t queue)
{
    resposta_t *resposta = (resposta_t *)buffer;
    if (resposta.tipo == CONECTADO)
    {
        identificador = resposta.identificador;
    }
}
