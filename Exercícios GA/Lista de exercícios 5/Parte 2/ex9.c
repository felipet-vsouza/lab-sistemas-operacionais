#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void load_firefox(char *url)
{
    char argString[500];
    sprintf(argString, "%s", "firefox --new-window");
    strcat(argString, " ");
    strcat(argString, url);
    system(argString);
}

void start_browser(char *url)
{
    pid_t pid;
    if ((pid = fork()) < 0)
    {
        perror("\nProblema na criação do processo filho.\n");
        return;
    }
    else if (pid == 0)
    {
        load_firefox(url);
    }
}

int main(int argc, char *argv[])
{
    start_browser(argv[1]);
    printf("Não bloqueou\n");
    return 0;
}
