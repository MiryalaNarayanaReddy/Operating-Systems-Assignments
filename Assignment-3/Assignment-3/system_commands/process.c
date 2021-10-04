#include "process.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void process(char *command, char *args)
{
    char *argv[MAX_ARGS];

    sprintf(temp_process_name, "%s %s", command, args);

    int num_args = parse_cmd(command, args, argv);

    if (AreSame(argv[num_args - 1], "&"))
    {
        argv[num_args - 1] = NULL;
        temp_process_name[strlen(temp_process_name) - 2] = '\0';
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
        current_fg.pid = child_pid;
        strcpy(current_fg.name, temp_process_name);
        strcpy(current_fg.name, argv[0]);
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
        push_into_jobs(temp_process_name, child_pid);
        printf("[%d] pid = %d\n", num_jobs, child_pid);
        setpgid(child_pid, 0);
        tcsetpgrp(0, getpgrp());
    }
}

void Handel_background_process_exit()
{
    signal(SIGCHLD, background_process_exit_message);
}

void background_process_exit_message()
{
    int p_stat;
    int p_id = waitpid(-1, &p_stat, WNOHANG);
    if (p_id <= 0)
        return;
    if (WIFEXITED(p_stat) && WEXITSTATUS(p_stat) == EXIT_SUCCESS)
    {
        printf("\n%s with pid %d exited normally\n", jobs[get_id_of_bg_process(p_id)].name, p_id);
    }
    else
    {
        printf("\n%s with pid %d exited with error code %d\n", jobs[get_id_of_bg_process(p_id)].name, p_id, WEXITSTATUS(p_stat));
    }
    fflush(stdout);
}

int get_id_of_bg_process(int pid)
{
    for (int i = 0; i < num_jobs; i++)
    {
        if (jobs[i].pid == pid)
        {
            return i;
        }
    }
    return -1; // never happens :)
}