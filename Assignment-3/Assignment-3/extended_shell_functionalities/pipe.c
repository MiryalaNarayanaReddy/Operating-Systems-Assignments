#include "pipe.h"
#include <wait.h>

void mypipe(char *args)
{
    int buffer_pipe[2];
    if (pipe(buffer_pipe))
    {
        perror("Could not pipe. :(\n");
        return;
    }
    // buffer_pipe[0]  for reading end;
    // buffer_pipe[1]  for writing end;

    pid_t chd1 = fork();
    pid_t chd2;
    if (chd1 == 0)
    {
        // dup2(buffer_pipe[READ], STDIN_FILENO);
        close(buffer_pipe[READ]);
        dup2(buffer_pipe[WRITE], STDOUT_FILENO);
        execlp("ls", "ls", NULL);
    }
    else
    {
        chd2 = fork();
        if (chd2 == 0)
        {
            close(buffer_pipe[WRITE]);
            dup2(buffer_pipe[READ], STDIN_FILENO);

            execlp("sort", "sort", NULL);
        }
    }
    waitpid(chd1, NULL, 0);
    close(buffer_pipe[WRITE]);
    // close(buffer_pipe[READ]);
    waitpid(chd2, NULL, 0);
}

void parse_cmd_for_execvp(char *args, char dest[0][100])
{
    char *token, *strptr;
    token = strtok_r(args, " ", &strptr);
    int i = 0;
    while (token != NULL)
    {
        strcpy(dest[i], token);
        token = strtok_r(NULL, "| ", &strptr);
    }
    dest[i][0] = '\0';
}

void check_for_pipes(char *args)
{
    char list[10][100];
    char parsed_comnd[10][100];
    char *token, *strptr;
    token = strtok_r(args, "| ", &strptr);
    int i = 0;
    while (token != NULL)
    {
        strcpy(list[i++], token);
        token = strtok_r(NULL, "| ", &strptr);
    }

    for (int j = 0; j < i; j++)
    {
        printf("%s\n", list[j]);
        parse_cmd_for_execvp(list[j], parsed_comnd);
        int k = 0;
        printf("----\n");
        while (parsed_comnd[k][0] != '\0')
        {
            // do work here
            printf("%s\n",parsed_comnd[k]);
            k++;
        }

    }
}