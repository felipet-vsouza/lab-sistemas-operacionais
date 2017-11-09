#include <stdio.h>

typedef enum tipo_mensagem {
    CONEXAO = 1,
    JOGADA = 2,
    DESCONEXAO = 3
} tipo_mensagem;

typedef struct mensagem_t
{
    tipo_mensagem tipo;
    union {
        char *nome;
    };
    union {
        int x;
        int y;
        int identificador;
    };
} mensagem_t;