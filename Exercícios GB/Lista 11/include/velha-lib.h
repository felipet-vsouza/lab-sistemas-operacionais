#ifndef _VELHA_LIB_H
#define _VELHA_LIB_H

const char *QUEUE_NAME = "/velha-queue";

typedef enum tipo_resposta {
    CONECTADO = 3,
    JOGADA_EXECUTADA = 4,
    LIBERACAO = 5,
    FINALIZACAO = 6
} tipo_resposta;

typedef enum tipo_mensagem {
    CONEXAO = 1,
    JOGADA = 2
} tipo_mensagem;

typedef struct mensagem_t
{
    tipo_mensagem tipo;
    char *nome;
    int x;
    int y;
    int identificador;
} mensagem_t;

typedef struct resposta_t
{
    tipo_resposta tipo;
    int identificador;
    char *caminho;
    char tabela[3][3];
    int is_ganhador;
    char *ganhador;
} resposta_t;

#endif