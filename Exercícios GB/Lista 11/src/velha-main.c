#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <mqueue.h>
#include "../include/velha-lib.h"

#define clear_screen() printf("\033[H\033[J")

void gerencia_conexao(void);
void aguarda_conexao(mqd_t queue);
void processa_conexao(ssize_t nbytes, char *buffer, mqd_t queue);
int finalizou_conexao(void);
int jogo_finalizou(void);
void gerencia_jogo(void);
int finalizou(char c);

typedef struct jogador_t
{
	int identificador;
	char *nome;
} jogador_t;

char *QUEUE_NAMES[2] = {"/velha-queue-0", "/velha-queue-1"};

static mqd_t queues[2];
static jogador_t jogadores[2];
static int identificador = 0;
static char tabela[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
static int ganhador = -1;

/**
 * Jogador 0: O
 * Jogador 1: X
*/
int main(void)
{
	printf("Iniciando conexão\n");
	gerencia_conexao();
	return 0;
}

void gerencia_conexao(void)
{
	mqd_t queue;
	char *buffer = NULL;
	ssize_t tam_buffer;
	ssize_t nbytes;

	queue = mq_open(QUEUE_NAME, O_RDWR | O_CREAT, 0660, NULL);
	if (queue == (mqd_t)-1)
	{
		perror("mq_open");
		exit(2);
	}
	aguarda_conexao(queue);

	return;
}

void gerencia_jogo(void)
{
	int i;
	for (i = 0; !jogo_finalizou(); i = (i + 1) % 2)
	{
	}
}

void aguarda_conexao(mqd_t queue)
{
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

	while (!finalizou_conexao())
	{
		printf("Aguardando conexão...\n");
		nbytes = mq_receive(queue, buffer, tam_buffer, NULL);
		processa_conexao(nbytes, buffer, queue);
	}
	mq_close(queue);
	printf("Conexão finalizada.\n");
}

int finalizou_conexao(void)
{
	int i;
	if (identificador >= 2)
		return 1;
	for (i = 0; i < 2; i++)
	{
		if (jogadores[i].identificador == 0)
			return 0;
	}
	return 1;
}

void processa_conexao(ssize_t nbytes, char *buffer, mqd_t queue)
{
	if (nbytes < 0)
	{
		printf("Problema na leitura (conexão)\n");
		return;
	}
	mensagem_t *mensagem = (mensagem_t *)buffer;
	if (mensagem->tipo != CONEXAO)
	{
		printf("Não é mensagem de conexão.\n");
		return;
	}
	jogadores[identificador].identificador = identificador;
	jogadores[identificador].nome = mensagem->nome;

	queues[identificador] = mq_open(QUEUE_NAMES[identificador], O_RDWR | O_CREAT, 0660, NULL);
	if (queues[identificador] == (mqd_t)-1)
	{
		perror("mq_open");
		exit(2);
	}

	resposta_t resposta;
	resposta.tipo = CONECTADO;
	resposta.identificador = identificador;
	resposta.caminho = QUEUE_NAMES[identificador];
	int res = mq_send(queue, (const char *)&resposta, sizeof(resposta_t), 20);
	if (res < 0)
	{
		printf("Problema no envio da resposta de conexão.\n");
		exit(1);
	}

	identificador++;
}

int jogo_finalizou(void)
{
	// jogador 0
	if (finalizou('O'))
	{
		ganhador = 0;
		return 1;
	}
	if (finalizou('X'))
	{
		ganhador = 1;
		return 1;
	}
	return 0;
}

int finalizou(char c)
{
	int x, y;
	int linhas, colunas, diagonal1, diagonal2;
	for (x = 0; x < 3; x++)
	{
		linhas = tabela[x][0] == c &&
				 tabela[x][1] == c &&
				 tabela[x][2] == c;
	}
	for (y = 0; x < 3; x++)
	{
		colunas = tabela[0][y] == c &&
				  tabela[1][y] == c &&
				  tabela[2][y] == c;
	}
	diagonal1 = tabela[0][0] == c &&
				tabela[1][1] == c &&
				tabela[2][2] == c;
	diagonal2 = tabela[0][2] == c &&
				tabela[1][1] == c &&
				tabela[2][0] == c;
	return linhas || colunas || diagonal1 || diagonal2;
}