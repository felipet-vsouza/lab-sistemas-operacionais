#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *_status_;
    int _is_running_;
    pid_t pid;
} job_data;

void inicializa_jobs(void);
char exibe_menu_e_aceita_opcao(void);
void verifica_atualizacao_de_jobs(void);
void executa_acao(char opcao);
void run_browser_job(void);
char read_something(void);
void read_string(char *buffer, int bsize);
job_data* initialize_job();
void failed_job(job_data *job);
void start_job(job_data *job, pid_t pid);
void update_job(job_data *job);
void end_job(job_data *job, int status);
void abre_navegador(char *url);

job_data *browser_job;
job_data *text_editor_job;
job_data *terminal_job;
job_data *process_mgmt_job;

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
    browser_job = initialize_job();
    text_editor_job = initialize_job();
    terminal_job = initialize_job();
    process_mgmt_job = initialize_job();
}

char exibe_menu_e_aceita_opcao(void)
{
    // TODO fix segmentation fault on struct data access

    verifica_atualizacao_de_jobs();

    system("clear");

    printf("<<<< Applications Menu >>>>\tPID:%d\tPPID:%d\n", getpid(), getppid());
    printf("\t1) Web Browser\t\t(%s)\n", browser_job->_status_);
    printf("\t2) Text Editor\t\t(%s)\n", text_editor_job->_status_);
    printf("\t3) Terminal\t\t(%s)\n", terminal_job->_status_);
    printf("\t4) Finalizar processo\t(%s)\n", process_mgmt_job->_status_);
    printf("\t5) Quit\n");
    printf("Opção: ");

    return read_something();
}

void verifica_atualizacao_de_jobs(void)
{
    update_job(browser_job);
    update_job(text_editor_job);
    update_job(terminal_job);
    update_job(process_mgmt_job);
}

void executa_acao(char opcao)
{
    if (opcao == '\n')
        return;

    system("clear");
    printf("Tarefa escolhida: ");

    switch (opcao)
    {
    case '1':
        printf("Web Browser");
        run_browser_job();
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
    default:
        printf("inválida!");
        break;
    }

    fflush(stdout);
    printf("\nPressione qualquer tecla para prosseguir.");
    read_something();
}

void run_browser_job(void)
{
    char *url = (char *)malloc(300 * sizeof(char));
    printf("\n\nDigite a URL desejada: ");
    read_string(url, 300);
    printf("\n\nAbrindo navegador...");
    pid_t job_pid = fork();
    if (job_pid < 0)
    {
        failed_job(browser_job);
    }
    else if (job_pid == 0)
    {
        abre_navegador(url);
        exit(0);
    }
    else
    {
        start_job(browser_job, job_pid);
    }
}

char read_something()
{
    char c = fgetc(stdin);

    int ch;
    if (c != '\n')
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;

    return c;
}

void read_string(char *buffer, int bsize)
{
    int ch, len;
    fgets(buffer, bsize, stdin);

    buffer[strcspn(buffer, "\r\n")] = '\0';
    len = strlen(buffer);

    if (len == bsize - 1)
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
}

/*  GENERAL JOB FUNCTIONS   */
job_data* initialize_job()
{
    job_data *job = (job_data *)malloc(sizeof(job_data));
    job->pid = 0;
    job->_status_ = "parado";
    job->_is_running_ = 0;
    return job;
}

void failed_job(job_data *job)
{
    job->pid = 0;
    job->_is_running_ = 0;
    job->_status_ = "falhou";
}

void start_job(job_data *job, pid_t pid)
{
    char *status = (char *)malloc(30 * sizeof(char));
    sprintf(status, "executando, pid=%d", pid);
    job->_status_ = status;
    job->pid = pid;
    job->_is_running_ = 1;
}

void update_job(job_data *job)
{
    int status;
    if (waitpid(job->pid, &status, WNOHANG) != 0)
    {
        end_job(job, status);
    }
}

void end_job(job_data *job, int status)
{
    job->pid = 0;
    job->_is_running_ = 0;
    if (status == 0)
        job->_status_ = "concluído";
    else
        job->_status_ = "abortado";
}

/*  JOB SPECIFIC FUNCTIONS  */
void abre_navegador(char *url)
{
    char argString[340];
    sprintf(argString, "firefox --new-window %s", url);
    system(argString);
}
