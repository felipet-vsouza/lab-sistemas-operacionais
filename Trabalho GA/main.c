#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void inicializa_jobs(void);
char exibe_menu_e_aceita_opcao(void);
void executa_acao(char opcao);
char read_something(void);

struct job_data
{
    char *_status_;
};

struct job_data browser_job;
struct job_data text_editor_job;
struct job_data terminal_job;
struct job_data process_mgmt_job;

int main(void)
{
    inicializa_jobs();

    char option;
    while ((option = exibe_menu_e_aceita_opcao()) != '5')
    {
        executa_acao(option);
    }

    system("clear");
    printf("Adeus!\n\n");
    return 0;
}

void inicializa_jobs(void)
{
    browser_job._status_ = "parado";
    text_editor_job._status_ = "parado";
    terminal_job._status_ = "parado";
    process_mgmt_job._status_ = "parado";
}

char exibe_menu_e_aceita_opcao(void)
{
    system("clear");

    printf("<<<< Applications Menu >>>>\n");
    printf("\t1) Web Browser\t\t(%s)\n", browser_job._status_);
    printf("\t2) Text Editor\t\t(%s)\n", text_editor_job._status_);
    printf("\t3) Terminal\t\t(%s)\n", terminal_job._status_);
    printf("\t4) Finalizar processo\t(%s)\n", process_mgmt_job._status_);
    printf("\t5) Quit\n");
    printf("Opção: ");

    return read_something();
}

void executa_acao(char opcao)
{
    system("clear");
    printf("Tarefa escolhida: ");

    printf("\n\n\n ORRA MEU %c\n\n\n", opcao);

    switch (opcao)
    {
    case '1':
        printf("Web Browser");
        break;
    case '2':
        printf("Text Editor");
        break;
    case '3':
        printf("Terminal");
        break;
    case '4':
        printf("Finalizar processo");
        break;
    case '\n':
        break;
    default:
        printf("inválida!");
        break;
    }

    if (c != '\n')
    {
        // TODO corrigir problema de manter caracter \n no stdin :(
        fflush(stdout);
        printf("\nPressione qualquer tecla para prosseguir.");
        read_something();

        sleep(2);
    }
}

char read_something()
{
    char something;
    something = fgetc(stdin);
    return something;
}