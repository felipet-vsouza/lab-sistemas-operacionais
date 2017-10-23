#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int load_firefox(char *url)
{
    char argString[500];
    sprintf(argString, "%s", "firefox --new-window");
    strcat(argString, " ");
    strcat(argString, url);
    return system(argString);
}

void start_browser(char *url)
{
    pid_t pid;
    if ((pid = fork()) < 0)
    {
        perror("\nProblema na criação do processo filho.\n");
        exit(1);
    }
    else if (pid == 0)
    {
        int status = load_firefox(url);
        exit(status);
    }
}

int main(int argc, char *argv[])
{
    int i;
    for (i = 1; i < argc; i++)
    {
        start_browser(argv[i]);
    }
    printf("Não bloqueou\n");
    return 0;
}
