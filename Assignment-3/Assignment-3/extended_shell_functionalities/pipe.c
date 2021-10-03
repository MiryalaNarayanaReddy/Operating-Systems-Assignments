#include "pipe.h"
#include <wait.h>

static void
pipeline(char **cmd)
{
    int fd[2];
    pid_t pid;
    int fdd = 0; /* Backup */
    while (*cmd != NULL)
    {
        pipe(fd); /* Sharing bidiflow */
        if ((pid = fork()) == -1)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            dup2(fdd, 0);
            if (*(cmd + 1) != NULL)
            {
                dup2(fd[1], 1);
            }
            close(fd[0]);
            // execvp((*cmd)[0], *cmd);
            // process_command(cmd[0]);
            system(cmd[0]);
            exit(1);
        }
        else
        {
            wait(NULL); /* Collect childs */
            close(fd[1]);
            fdd = fd[0];
            cmd++;
        }
    }
}

void check_for_pipes(char *args)
{
    char list[10][100];
    char parsed_comnd[10][100];
    char *token, *strptr;
    token = strtok_r(args, "|", &strptr);
    int n = 0;
    while (token != NULL)
    {
        strcpy(list[n++], token);
        token = strtok_r(NULL, "|", &strptr);
    }
    // printf("n = %d\n", n);

    // char *ls[] = {"ls", "-al", NULL};
    // char *rev[] = {"rev", NULL};
    // char *nl[] = {"nl", NULL};
    // char *cat[] = {"cat", "-e", NULL};
    // char *cmd[] = {"ls", "sort", "uniq", NULL};
    if (n == 1)
    {
        process_command(list[0]);
        return;
    }

    // piping part =============================
    char *cmd[10];
    for (int i = 0; i < n; i++)
    {
        cmd[i] = list[i];
    }
    cmd[n] = NULL;
    pipeline(cmd);
}
