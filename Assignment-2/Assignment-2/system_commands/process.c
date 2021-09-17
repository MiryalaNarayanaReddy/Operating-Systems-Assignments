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
        signal(SIGINT, SIG_DFL);  // ctrl - c
        signal(SIGTSTP, SIG_DFL); //ctrl - z
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
        signal(SIGCHLD, process_status); // child exit

        // printf("%s with pid %d exited %s\n", argv[0], child_pid, id == child_pid ? "normally" : "abnormally");
    }
}

void background_process(char **argv)
{
    pid_t child_pid = fork();
    if (child_pid == 0)
    {
        signal(SIGINT, SIG_DFL);  // ctrl - c
        signal(SIGTSTP, SIG_DFL); //ctrl - z
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

        signal(SIGCHLD, process_status); // child exit
        child_processes[child_pid] = child_pid;
        number_of_children ++;
        // printf("%s with pid %d exited %s\n", argv[0], child_pid, id == child_pid ? "normally" : "abnormally");
    }
}

// int status;
// pid_t result = waitpid(ChildPID, &status, WNOHANG);
// if (result == 0) {
//   // Child still alive
// } else if (result == -1) {
//   // Error
// } else {
//   // Child exited
// }

void process_status()
{
    pid_t process_pid;
    int status;
    process_pid = waitpid(-1, &status, WNOHANG);
    if (process_pid == 0)
    {
        // still alive
    }
    else if (process_pid = -1)
    {

        //error
        printf("[%d]+ [%d] exited abnormally", process_pid, status);
    }
    else
    {

        printf("[%d]+ [%d] exited normally", process_pid, status);
    }
}