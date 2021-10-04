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

void pipeline(char **cmd)
{
    int fd[2], st;
    pid_t pid;
    int fdd = 0; /* Backup */
    while (*cmd != NULL)
    {
        pipe(fd); /* Sharing bidiflow */
        pid = fork();
        if (pid < -1)
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
            // execvp(cmd[0], cmd);
            // printf("%s\n", cmd[0]);

            process_command(cmd[0]);
            // system(cmd[0]);
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
        // printf("%s\n",list[0]);
        process_command(list[0]);
        return;
    }

    // piping part =============================
    char *cmd[10];
    for (int i = 0; i < n; i++)
    {
        strip_spaces(list[i]);
        cmd[i] = list[i];
        // printf("- %s\n", cmd[i]);
    }
    cmd[n] = NULL;
    pipeline(cmd);
}
