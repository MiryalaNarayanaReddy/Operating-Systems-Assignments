#include "process.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
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
    printf("\r"); // just to remove the first prompt being printed by the signal interrupt.
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
        if (execvp(argv[0], argv) == -1)
        {
            Color_On(__RED, BOLD);
            printf("Command invalid :(\n");
            Color_Off();
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    else if (child_pid < 0)
    {
        Color_On(__YELLOW, BOLD);
        printf("Forking failed\n");
        Color_Off();
    }
    else
    {
        // push_into_jobs(argv[0], child_pid);
        current_fg = child_pid;
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
        setpgid(child_pid, 0);
        tcsetpgrp(0, __getpgid(child_pid));

        int status;
        waitpid(child_pid, &status, WUNTRACED);

        // exit_code = status;
        tcsetpgrp(0, getpgrp());
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
    }
}

void background_process(char **argv)
{
    pid_t child_pid = fork();
    if (child_pid == 0)
    {
        if (execvp(argv[0], argv) == -1)
        {
            Color_On(__RED, BOLD);
            printf("Command invalid :(\n");
            Color_Off();
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    else if (child_pid < 0)
    {
        Color_On(__YELLOW, BOLD);
        printf("Forking failed \n");
        Color_Off();
    }
    else
    {
        push_into_jobs(argv[0], child_pid);
        printf("[%d] pid = %d\n", num_jobs, child_pid);
        setpgid(child_pid, 0);
        tcsetpgrp(0, getpgrp());
    }
}

void setup_exit()
{
    signal(SIGCHLD, exit_status);
}

void exit_status()
{
    int proc_stat, proc_id = waitpid(-1, &proc_stat, WNOHANG);
    if (proc_id <= 0)
        return;
    WIFEXITED(proc_stat) && WEXITSTATUS(proc_stat) == EXIT_SUCCESS
        ? printf("\n%s with pid %d exited normally ", jobs[process_no].name, proc_id)
        : printf("\n%s with pid %d exited with error code %d ", jobs[process_no].name, proc_id, WEXITSTATUS(proc_stat));
    fflush(stdout);
}