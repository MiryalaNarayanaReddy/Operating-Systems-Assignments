#include "pipe.h"
#include <wait.h>

void strip_spaces(char *str)
{
    char temp[MAX_ARGS];
    int i = 0;
    while (str[i] == ' ' && str[i] != '\0')
    {
        i++;
    }
    int j = 0;
    while (str[i] != '\0')
    {
        temp[j++] = str[i];
        i++;
    }
    j--;
    while (temp[j] == ' ')
    {
        j--;
    }
    temp[j + 1] = '\0';
    strcpy(str, temp);
}

void pipe_all(char **cmd)
{
    int fd[2];
    pid_t pid;
    int save_fd = 0;

    while (*cmd != NULL)
    {
        if (pipe(fd) < 0)
        {
            perror("piping failed\n");
            return;
        }
        pid = fork();
        if (pid < -1)
        {
            perror("forking in pipe failed\n");
            return;
        }
        else if (pid == 0)
        {
            dup2(save_fd, STDIN_FILENO);
            if (*(cmd + 1) != NULL) // if next command is exits
            {
                dup2(fd[WRITE_END], STDOUT_FILENO);
            }
            close(fd[READ_END]);
            // execvp(cmd[0], cmd);
            // printf("%s\n", cmd[0]);
            process_command(cmd[0]);
            // system(cmd[0]);
            exit(EXIT_SUCCESS);
        }
        else
        {
            wait(NULL); // wait for child
            close(fd[WRITE_END]);
            save_fd = fd[READ_END];
            cmd++;
        }
    }
}

void check_for_pipes(char *args)
{
    char list[10][MAX_PATH_LEN];
    char parsed_comnd[10][MAX_PATH_LEN];
    char *token, *strptr;
    token = strtok_r(args, "|", &strptr);
    int n = 0;
    while (token != NULL)
    {
        strcpy(list[n++], token);
        token = strtok_r(NULL, "|", &strptr);
    }
    if (n == 1) // only one command and no pipes
    {
        // printf("pipe\n");
        process_command(list[0]);
        // printf("pipe\n");
        return;
    }

    // piping part =============================
    char *cmd[10];
    for (int i = 0; i < n; i++)
    {
        strip_spaces(list[i]); // remove extra spaces at ends
        cmd[i] = list[i];
        // printf("- %s\n", cmd[i]);
    }
    cmd[n] = NULL;
    pipe_all(cmd);
}
