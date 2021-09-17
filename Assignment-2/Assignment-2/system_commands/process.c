#include "process.h"
#include <wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void process(char *command, char *args)
{
    char *argv[MAX_ARGS];
    int num_args = parse_cmd(command, args, argv);
    if (AreSame(argv[num_args - 1], "&"))
    {
        argv[num_args - 1] = NULL;
        background_process(argv);
    }
    else
    {
        forground_process(argv);
    }
}

int parse_cmd(char *command, char *args, char *argv[10])
{
    // printf("%s\n%s\n", command, args);
    argv[0] = &command[0];
    char *token;
    char *strptr;
    int i = 1;
    token = strtok_r(args, " ", &strptr);
    while (token != NULL)
    {
        argv[i] = &token[0];
        i++;
        token = strtok_r(NULL, " ", &strptr);
    }
    argv[i] = NULL;
    return i;
}

void forground_process(char **argv)
{
    pid_t child_pid = fork();
    if (child_pid == 0)
    {
        signal(SIGINT, SIG_DFL);// ctrl - c
        signal(SIGTSTP,SIG_DFL);//ctrl - z
        execvp(argv[0], argv);
        printf("Command invalid :(\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        signal(SIGCHLD, SIG_DFL); // child exit

        // printf("%s with pid %d exited %s\n", argv[0], child_pid, id == child_pid ? "normally" : "abnormally");
    }
}

void background_process(char **argv)
{
    pid_t child_pid = fork();
    if (child_pid == 0)
    {
        printf("%d\n", getpid());
        execvp(argv[0], argv);
        printf("Command invalid :(\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        // int stat;
        // pid_t id = wait(&stat);
        // printf("%s with pid %d exited %s\n", argv[0], child_pid, id == child_pid ? "normally" : "abnormally");
    }
}
