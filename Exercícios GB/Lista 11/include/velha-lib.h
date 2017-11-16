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
    union { // CONEXÃO
        char *nome;
    };
    union { // JOGADA
        int x;
        int y;
        int identificador;
    };
} mensagem_t;

typedef struct resposta_t
{
    tipo_resposta tipo;
    union { // CONEXÃO
        int identificador;
        char *caminho;
    };
    union { // JOGADA
        char tabela[3][3];
    };
    union { // FINALIZAÇÂO
        int is_ganhador;
        char *ganhador;
    };
} resposta_t;

#endif